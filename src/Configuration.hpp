
#ifndef TX_CONFIGURATION_HPP_
#define TX_CONFIGURATION_HPP_

#include <vector>
#include <cstdint>

#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/ini_parser.hpp>
#include <boost/property_tree/exceptions.hpp>

#include "Return.hpp"

namespace TX {
  
  class Configuration {
  private:
    boost::property_tree::ptree pt;
    
    struct ConfigurationDB {
      std::string serverHostName;
      std::string dataBaseName;
      std::uint16_t port;
     }dbConf;

    std::vector<std::string> enabledExtensions;
    
    
  public:
    Configuration (const std::string &path);

    const std::string   &getServerHostName();
    const std::string   &getDataBaseName();
    const std::uint16_t &getServerPort();
    const std::vector<std::string> &getEnabledExtensions();
    Return<const boost::property_tree::ptree> getConfigurationForModule ();
    
  };
  
} //TX

#endif /* TX */
