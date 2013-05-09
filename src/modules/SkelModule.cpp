#include "SkelModule.hpp"


namespace TX {
namespace module {

SkelModule::SkelModule(boost::property_tree::ptree *_configuration) :
  moduleName("SkelModule"),
  configuration(_configuration) {

  if (configuration == NULL){
    throw std::runtime_error ("test");
  }
  std::cout << "SkelModule " << __DATE__ << " " << __TIME__ << std::endl;
}



SkelModule::RequestResult
SkelModule::processFilePath(const std::string directoryPath, 
			    const std::string fileName,
			    const std::string extension) {

  Module::RequestResult result;

  result.path 	 = directoryPath; 
  result.fileName  = fileName;
  result.extension = extension;

  result.file.push_back(std::make_pair("skelModule_life", 42));
  result.file.push_back(std::make_pair("skelModule_foo", "bar"));
  std::cout << "pushing data" << std::endl;

  return std::move(result);
}

const std::string &SkelModule::getName () {
  std::cout << "my name is SkelModule" << std::endl;
  return moduleName;
}


SkelModule::~SkelModule(){}

} //MODULE
} //TX



extern "C" {

  TX::module::Module* init(boost::property_tree::ptree *configuration) {
    try {
      TX::module::Module*skelModule = new TX::module::SkelModule (configuration);
      std::cout << "module address "  << skelModule << std::endl;
      
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
