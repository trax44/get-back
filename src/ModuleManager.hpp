#ifndef TX_MODULEMANAGER_HPP_
#define TX_MODULEMANAGER_HPP_

#include <string>

#include "Configuration.hpp"

class ModuleManager {
public:
  ModuleManager();
  bool registerModule (const std::string modulePath,
		       const boost::property_tree::ptree pt);
  virtual ~ModuleManager();
};

#endif /* TX */
