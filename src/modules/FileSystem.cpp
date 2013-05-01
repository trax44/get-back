#include "SkelModule.hpp"

#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>


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

  std::string fullPath (directoryPath + "/" + filename);
  
  struct stat statsInfo;

  
  
  if (lstat(fullPath.c_str(), &statsInfo) == 0) {
    requestBuilder->append ("size",              static_cast<uint32_t>(statsInfo.st_size));
    requestBuilder->append ("last_access",       static_cast<uint32_t>(statsInfo.st_atime));
    requestBuilder->append ("last_modification", static_cast<uint32_t>(statsInfo.st_mtime));
    
    return true;
  } else {
    return false;
  }
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
