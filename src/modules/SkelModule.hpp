#ifndef TX_MODULE_SKELMODULE_HPP_
#define TX_MODULE_SKELMODULE_HPP_

#include <stdexcept>
#include <boost/property_tree/ptree.hpp>

#include "../Return.hpp"
#include "Module.hpp"



namespace TX {
namespace module {

class SkelModule :public Module {
public:
  SkelModule(boost::property_tree::ptree  *);

  Return<mongo::BSONObj> processFilePath(const std::string directoryPath, 
					 const std::string filename,
					 const std::string extension);
  virtual ~SkelModule();
};

} //module
} //TX



#endif /* TX_MODULE */
