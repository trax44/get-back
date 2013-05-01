#include "SkelModule.hpp"


namespace TX {
namespace module {

SkelModule::SkelModule(boost::property_tree::ptree *_configuration) :
  configuration(_configuration) {

  if (configuration == NULL){
    throw std::runtime_error ("test");
  }

  std::cout << "Skel Module constructor" << std::endl;

}



bool
SkelModule::processFilePath(const std::string directoryPath, 
			    const std::string filename,
			    const std::string extension,
			    mongo::BSONObjBuilder *requestBuilder) {

  // std::cout << "REQ0 " << configuration->get<std::string>("db_prefix") << std::endl;
  // std::cout << "REQ1 " << configuration->get<std::string>("db_prefix") << std::endl;
  std::cout << "REQ " << this << std::endl;
  requestBuilder->append ("skelModule_prefix", "plop");
  std::cout << "REQ " << this << std::endl;
  // requestBuilder->append ("skelModule_prefix", 
  // 			  configuration->get<std::string>("db_prefix"));

  // std::cout << "REQ2 " << configuration->get<std::string>("db_prefix") << std::endl;

  return true;
}


SkelModule::~SkelModule(){}

} //MODULE
} //TX



extern "C" {

  TX::module::Module* init(boost::property_tree::ptree *configuration) {
    try {
      TX::module::Module*skelModule = new TX::module::SkelModule (configuration);

      std::cout << "skel module address " << skelModule << std::endl;
      
      return skelModule;
    } catch (std::runtime_error &e){
      std::cout << "Could not load module " << e.what() << std::endl;
      return NULL;
    }

    return NULL;
  }


  void destroy(TX::module::Module *module) {
    std::cout << "deleting " << module << std::endl;
    delete (module);
  }

}
