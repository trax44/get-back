#ifndef TX_MODULEMANAGER_HPP_
#define TX_MODULEMANAGER_HPP_

#include <string>
#include <memory>
#include <unordered_map>

#include "modules/Module.hpp"
#include "Configuration.hpp"
#include "Save2DB.hpp"

namespace TX {


class ModuleManager {
private:
  Save2DB &mongodb;
  std::unordered_multimap <std::string, 
			   std::shared_ptr<const module::Module> > modules;

  // std::unordered_multimap <const std::string, 
  // 			   std::shared_ptr<const module::Module *> > modules;
  
public:
  ModuleManager(Save2DB &mongodb);

  bool registerModule (const std::string &modulePath,
		 const boost::property_tree::ptree &pt);

  bool processFilePath (const std::string &path,
			const std::string &fileName,
			const std::string &extension);

  virtual ~ModuleManager();
};


} //TX

#endif /* TX */
