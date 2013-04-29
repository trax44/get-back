
#ifndef TX_CONFIGURATION_HPP_
#define TX_CONFIGURATION_HPP_

#include <vector>
#include <cstdint>
#include <unordered_map>

#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/ini_parser.hpp>
#include <boost/property_tree/exceptions.hpp>

#include "Return.hpp"

namespace TX {
  
class Configuration {
public:

  typedef boost::property_tree::ptree ModuleConfiguration;
  typedef std::unordered_map<std::string, ModuleConfiguration> ModuleConfigurationContainer;
  

private:
  
  struct ConfigurationDB {
    std::string serverHostName;
    std::string dataBaseName;
    std::uint16_t port;
  }dbConf;

  //std::vector<std::string> enabledExtensions;
  ModuleConfigurationContainer modules;
  boost::property_tree::ptree pt;
    
public:
  Configuration (const std::string &path);

  const std::string   &getServerHostName();
  const std::string   &getDataBaseName();
  const std::uint16_t &getServerPort();
  const ModuleConfigurationContainer &getEnabledModules();
  Return<ModuleConfiguration> getConfigurationForModule (const std::string moduleName);
  
};
  
} //TX

#endif /* TX */
