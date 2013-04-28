#include <iostream>
#include <stdexcept>

#include "Configuration.hpp"


namespace TX {
  
Configuration::Configuration(const std::string &configPath) {
  boost::property_tree::ini_parser::read_ini(configPath, pt);


  try {
    dbConf.serverHostName = pt.get<std::string>  ("db.hostname");
    dbConf.dataBaseName   = pt.get<std::string>  ("db.dataBaseName");
  } catch (...) {
    throw std::runtime_error ("DataBase host and name should be supplied");
  }

  dbConf.port           = pt.get<std::uint16_t>("db.port", 0);


  boost::property_tree::ptree groups = pt.get_child("");
  for (auto it = groups.begin() , end = groups.end () ; 
       it != end ; ++it) {
      
    if (it->first != "db") {
      std::cout << "module>> " << it->first << " is ";
      if (it->second.get<bool>("enabled")) {
	std::cout << " enabled" << std::endl;
	modules.insert({it->first, it->second});
      } else {
	std::cout << " disabled" << std::endl;
      }
    } else {
      // only mandatory plugin is SaveDB
    }
      
  }
}

  

const std::string   &Configuration::getServerHostName() {
  return dbConf.serverHostName;
}

const std::uint16_t &Configuration::getServerPort() {
  return dbConf.port;
}

const std::string   &Configuration::getDataBaseName() {
  return dbConf.dataBaseName;
}

const Configuration::ModuleConfigurationContainer &Configuration::getEnabledModules() {
  return modules;
}


Return<Configuration::ModuleConfiguration> 
Configuration::getConfigurationForModule (const std::string moduleName) {
  std::string path (moduleName + ".enabled");
  
  const auto got = modules.find (path);
  
  if (got == modules.end()) {
    return std::move(Return<Configuration::ModuleConfiguration>(false));
  } else {
    return std::move(Return<Configuration::ModuleConfiguration> (got->second));
  }
}

  
  
} //TX

