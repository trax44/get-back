#ifndef TX_MODULE_SKELMODULE_HPP_
#define TX_MODULE_SKELMODULE_HPP_

#include <stdexcept>
#include <boost/property_tree/ptree.hpp>
#include "../Return.hpp"



namespace TX {
namespace modules {

class SkelModule {
public:
  SkelModule(void *);
  virtual ~SkelModule();
};

} //MODULE

} //TX



#endif /* TX_MODULE */
