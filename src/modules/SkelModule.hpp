#ifndef TX_MODULE_SKELMODULE_HPP_
#define TX_MODULE_SKELMODULE_HPP_

#include <stdexcept>
#include <boost/property_tree/ptree.hpp>
#include "../Return.hpp"



namespace TX {
namespace module {

class SkelModule {
public:
  SkelModule(void *);
  virtual ~SkelModule();
};

} //module
} //TX



#endif /* TX_MODULE */
