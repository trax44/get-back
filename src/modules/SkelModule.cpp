#include "SkelModule.hpp"


namespace TX {
namespace module {

SkelModule::SkelModule(boost::property_tree::ptree *configuration) {

  if (configuration == NULL){
    throw std::runtime_error ("test");
  }

  std::cout << "Skel Module constructor" << std::endl;

}



Return<mongo::BSONObj> SkelModule::processFilePath(const std::string directoryPath, 
						   const std::string filename,
						   const std::string extension) {
  mongo::BSONObjBuilder b;
  b.append ("skelModule_extension", extension);
  return std::move(Return<mongo::BSONObj>(b.obj()));
}


SkelModule::~SkelModule(){}

} //MODULE
} //TX



extern "C" {

  TX::module::Module* init(boost::property_tree::ptree *configuration) {
    try {
      return new TX::module::SkelModule (configuration);
    } catch (std::runtime_error &e){
      std::cout << "Could not load module " << e.what() << std::endl;
      return NULL;
    }

    return NULL;
  }
}
