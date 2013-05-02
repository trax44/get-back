#include "SkelModule.hpp"


namespace TX {
namespace module {

SkelModule::SkelModule(boost::property_tree::ptree *_configuration) :
  configuration(_configuration) {

  if (configuration == NULL){
    throw std::runtime_error ("test");
  }

}



bool
SkelModule::processFilePath(const std::string directoryPath, 
			    const std::string filename,
			    const std::string extension,
			    mongo::BSONObjBuilder *requestBuilder) {

  requestBuilder->append ("skelModule_prefix", "plop");

  return true;
}


SkelModule::~SkelModule(){}

} //MODULE
} //TX



extern "C" {

  TX::module::Module* init(boost::property_tree::ptree *configuration) {
    try {
      TX::module::Module*skelModule = new TX::module::SkelModule (configuration);

      
      return skelModule;
    } catch (std::runtime_error &e){
      std::cerr << "Could not load module " << e.what() << std::endl;
      return NULL;
    }

    return NULL;
  }


  void destroy(TX::module::Module *module) {
    delete (module);
  }

}
