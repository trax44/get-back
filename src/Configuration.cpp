#include "Configuration.hpp"

#include <iostream>

#include <stdexcept>

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
	if (it->second.get<bool>("enabled")) {
	  enabledExtensions.push_back(it->first);
	}
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


  const std::vector<std::string> &Configuration::getEnabledExtensions() {
    return enabledExtensions;
  }

  
  
} //TX

