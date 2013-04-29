#include <iostream>
#include <unordered_map>


#include "Return.hpp"
#include "Browse.hpp"
#include "Configuration.hpp"
#include "modules/Module.hpp"
#include "ModuleManager.hpp"

int main(int argc, char *argv[]) {
  
  if (argc != 3) {
    std::cout << argv[0] << " confFile dir" << std::endl;
    return -1;
  }

  TX::Configuration configuration (argv[1]);
  TX::Save2DB mongodb(configuration.getServerHostName(), configuration.getDataBaseName());
  TX::ModuleManager moduleManager (mongodb);
  
  auto modulesConfiguration = configuration.getEnabledModules();
  
  for (auto it: modulesConfiguration) {
    moduleManager.registerModule(it.second.get<std::string>("lib"), it.second);
  }

  
  //std::cout << "Skel> " << init (NULL) << std::endl;


  TX::Browse browser(argv[2], moduleManager);

    
  //browser.printCurrentPath();
  return 0;
}


