#include "ModuleManager.hpp"

#include <iostream>
#include <dlfcn.h>

ModuleManager::ModuleManager() {}

bool ModuleManager::registerModule (const std::string modulePath, 
				    const boost::property_tree::ptree pt) {
  
  std::cout << "Opening hello.so..." << std::endl;
  
  void* handle = dlopen(modulePath.c_str(), RTLD_LAZY);
    
  if (!handle) {
    std::cerr << "Cannot open library: " << dlerror() << std::endl;
    return false;
  }
    
  // load the symbol
  std::cout << "Loading symbol hello..." << std::endl;
  typedef void (*init_t)();

  // reset errors
  dlerror();
  init_t hello = (init_t) dlsym(handle, "init");
  const char *dlsym_error = dlerror();
  if (dlsym_error) {
    std::cerr << "Cannot load symbol 'hello': " << dlsym_error << std::endl;

    dlclose(handle);
    return true;
  }
    
  // use it to do the calculation
  std::cout << "Calling hello..." << std::endl;
  hello();
    
  // close the library
  std::cout << "Closing library..." << std::endl;
  dlclose(handle);

  return true;
}

ModuleManager::~ModuleManager() {}
