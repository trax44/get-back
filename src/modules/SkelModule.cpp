#include "SkelModule.hpp"


extern "C" {

  void* init(void *configuration) {
    try {
      return new TX::module::SkelModule (configuration);
    } catch (std::runtime_error &e){
      std::cout << "Could not load module " << e.what() << std::endl;
      return NULL;
    }
  }
}

namespace TX {
namespace module {

SkelModule::SkelModule(void *configuration) {

  if (configuration == NULL){
    throw std::runtime_error ("test");
  }

  std::cout << "Skel Module constructor" << std::endl;

}


SkelModule::~SkelModule(){}

} //MODULE
} //TX

