#ifndef TX_MODULE_SKELMODULE_HPP_
#define TX_MODULE_SKELMODULE_HPP_

#include <stdexcept>
#include <boost/property_tree/ptree.hpp>

#include "../tools/Return.hpp"
#include "Module.hpp"



namespace TX {
namespace module {

class SkelModule : public Module {
private:
  boost::property_tree::ptree *configuration;

public:
  SkelModule(boost::property_tree::ptree  *);

  bool
  processFilePath(const std::string directoryPath, 
		  const std::string filename,
		  const std::string extension,
		  mongo::BSONObjBuilder *requestBuilder);
  
  virtual ~SkelModule();
};

} //module
} //TX



#endif /* TX_MODULE */
