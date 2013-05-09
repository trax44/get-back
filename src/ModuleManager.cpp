#include <iostream>
#include <dlfcn.h>
#include <memory>
#include <boost/tokenizer.hpp>


#include "ModuleManager.hpp"
//#include "modules/Module.hpp"
namespace TX {

ModuleManager::ModuleManager(Save2DB &_mongodb):
  mongodb(_mongodb),
  polling(false),
  workInProgress(0) {
}

bool ModuleManager::registerModule (const std::string &modulePath, 
				    Configuration::ModuleConfiguration *pt) {
  
  
  void* handle = dlopen(modulePath.c_str(), RTLD_LAZY);
    
  if (!handle) {
    std::cerr << "Cannot open library: (" << modulePath << ")"  << dlerror() << std::endl;
    return false;
  }
    
  dlerror();

  typedef void* (*init_t)(void*);
  typedef void  (*destroy_t)(TX::module::Module*);

  init_t    initFunction    =  (init_t)   dlsym(handle, "init");
  destroy_t destroyFunction =  (destroy_t)dlsym(handle, "destroy");
  const char *dlsym_error = dlerror();

  if (dlsym_error) {
    std::cerr << "Cannot load symbol: " << "init"  << " " << dlsym_error << std::endl;

    dlclose(handle);
    return true;
  }
  
  module::Module *module = (module::Module *)initFunction((void *)pt);


  boost::char_separator<char> sep(", ");
  boost::tokenizer<boost::char_separator<char> > 
    tokens(pt->get<std::string>("extensions"), sep);

  modulesInformation.push_back ({module, handle, destroyFunction});
  for (auto it : tokens) {
    // std::pair<std::string, std::shared_ptr<const module::Module> > pair (it, t);

    if (it == "ALL") {
      modulesForAllEnabledFiles.push_back (module);
    } else {
      modules.insert (std::make_pair<std::string, module::Module *> 
		      (std::move(it), std::move(module)));
    }
    //modules.insert ({it, module});
    
  }
    
  return true;
}


bool ModuleManager::processFilePath (const std::string path,
				     const std::string fileName,
				     const std::string extension) {
  
  
  auto range = modules.equal_range (extension);
  
  for (auto it = range.first , end = range.second ; it != end ; ++it) {

    mongo::BSONObjBuilder requestBuilder;
    const std::string fullPath (path + "/" + fileName);

    auto q = new std::function<module::Module::RequestResult()>
      (std::bind(&module::Module::processFilePath,
		 *(it->second)/*->processFilePath*/,
		 path, fileName, extension));

    pool.push (q);
    std::cout << "pushing " << fileName << " " << std::endl;
    workInProgress++;
  }

  return true;
}

void ModuleManager::pollResults () {
  polling = true;

  while (polling) {
    Return<module::Module::ModuleResult> result = pool.getJob();
    if (!result.success) {
      usleep(1);
    } else {
      result.data.printAll();
      if ((workInProgress--) == 1){
	stop();
      }
    }
  }
}

void ModuleManager::run () {
  pollingResultsThread = std::thread (&ModuleManager::pollResults, this);
}

void ModuleManager::stop () {
  polling = false;
}


ModuleManager::~ModuleManager() {
  std::cout << "~ModuleManager" << std::endl;
  //pollingResultsThread.join ();

  for (auto it: modulesInformation) {
    TX::module::Module *module = it.module;
    it.destructor(module);
    dlclose(it.libHandle);
  }

}


} //TX
