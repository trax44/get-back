#ifndef TX_MODULES_MODULE_HPP_
#define TX_MODULES_MODULE_HPP_

#include <string>
#include <mongo/client/dbclient.h>
#include <boost/property_tree/ptree.hpp>

#include "../tools/Return.hpp"


namespace TX {
namespace module {

class Module {
public:

  virtual bool
  processFilePath(const std::string directoryPath, 
		  const std::string filename,
		  const std::string extension,
		  mongo::BSONObjBuilder *requestBuilder) = 0;
  

  virtual ~Module() {}
};



} //module
} //TX


extern "C" TX::module::Module* init_t(boost::property_tree::ptree *configuration);
extern "C" void destroy_t(TX::module::Module*);


#endif /* TX_MODULES */
