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
				    const Configuration::ModuleConfiguration &pt) {
  
  
  void* handle = dlopen(modulePath.c_str(), RTLD_LAZY);
    
  if (!handle) {
    std::cerr << "Cannot open library: (" << modulePath << ")"  << dlerror() << std::endl;
    return false;
  }
    
  dlerror();

  typedef void* (*init_t)(void*);

  init_t initFunction =  (init_t)dlsym(handle, "init");
  const char *dlsym_error = dlerror();

  if (dlsym_error) {
    std::cerr << "Cannot load symbol: " << "init"  << " " << dlsym_error << std::endl;

    dlclose(handle);
    return true;
  }
    
  const module::Module *module = (const module::Module *)initFunction((void *)&pt);

  boost::char_separator<char> sep(", ");
  boost::tokenizer<boost::char_separator<char> > tokens(pt.get<std::string>("extensions"), sep);

  for (auto it : tokens) {
    std::shared_ptr<const module::Module> t(module);
    // std::pair<std::string, std::shared_ptr<const module::Module> > pair (it, t);
    // modules.insert(std::make_pair<std::string, std::shared_ptr<const module::Module> >(it, t);
    std::cout << "--" << it << "++" << std::endl;
    modules.insert (std::make_pair<std::string, std::shared_ptr<const module::Module>> 
		    (std::move(it), std::move(t)));
  }



    
  return true;
}

bool ModuleManager::processFilePath (const std::string &path,
				     const std::string &fileName,
				     const std::string &extension) {
  
  std::cout << "processing by module manager " << fileName << std::endl;
  auto range = modules.equal_range (extension);
  for (auto it = range.first , end = range.second ; it != end ; ++it) {
    std::cout << "send " << fileName << " to module " << it->first << std::endl;
  }

  return true;
}


ModuleManager::~ModuleManager() {}


} //TX
