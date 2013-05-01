#include <iostream>
#include <dlfcn.h>
#include <memory>
#include <boost/tokenizer.hpp>


#include "ModuleManager.hpp"
//#include "modules/Module.hpp"
namespace TX {

ModuleManager::ModuleManager(Save2DB &_mongodb):
  mongodb(_mongodb) {
  
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
  std::cout << "module address " << handle << std::endl;

  boost::char_separator<char> sep(", ");
  boost::tokenizer<boost::char_separator<char> > tokens(pt->get<std::string>("extensions"), sep);

  modulesInformation.push_back ({module, handle, destroyFunction});
  for (auto it : tokens) {
    // std::pair<std::string, std::shared_ptr<const module::Module> > pair (it, t);

    
    std::cout << "--" << it << "++" << std::endl;
    modules.insert (std::make_pair<std::string, module::Module *> 
    		    (std::move(it), std::move(module)));
    //modules.insert ({it, module});
    
  }



    
  return true;
}

bool ModuleManager::processFilePath (const std::string &path,
				     const std::string &fileName,
				     const std::string &extension) {
  
  std::cout << "processing by module manager " 
	    << fileName 
	    << " ext(" 
	    << extension
	    << ")"
	    << std::endl;
  
  auto range = modules.equal_range (extension);
  
  for (auto it = range.first , end = range.second ; it != end ; ++it) {
    std::cout << "send " << fileName 
	      << " to module " << it->first 
	      << " addr " << it->second 
	      << std::endl;

  mongo::BSONObjBuilder requestBuilder;
    const std::string fullPath (path + "/" + fileName);



    bool ret = it->second->processFilePath(path, 
					   fileName, 
					   extension, 
					   &requestBuilder);

    
    if (ret) {
      mongodb.saveEntry(extension,
			fullPath, 
			requestBuilder);
    }
  }

  return true;
}


ModuleManager::~ModuleManager() {
  std::cout << "~ModuleManager" << std::endl;
  for (auto it: modulesInformation) {
    TX::module::Module *module = it.module;
    std::cout << "destroying " << module << std::endl;
    it.destructor(module);
    dlclose(it.libHandle);
  }
}


} //TX
