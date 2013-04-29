#ifndef TX_MODULES_MODULE_HPP_
#define TX_MODULES_MODULE_HPP_

#include <string>
#include <mongo/client/dbclient.h>

#include "../Return.hpp"


extern "C" void* init_t(void *configuration);


namespace TX {
namespace module {

class Module {
public:

  virtual Return<mongo::BSONObj> processFilePath(const std::string directoryPath, 
						 const std::string filename,
						 const std::string extension) = 0;


  virtual ~Module() {}
};



} //module
} //TX


#endif /* TX_MODULES */
