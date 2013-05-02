#include "FileSystem.hpp"

#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>


namespace TX {
namespace module {

FileSystem::FileSystem(boost::property_tree::ptree *_configuration) :
  configuration(_configuration) {

  if (configuration == NULL){
    throw std::runtime_error ("test");
  }

  std::cout << "Skel Module constructor" << std::endl;

}



bool
FileSystem::processFilePath(const std::string directoryPath, 
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


FileSystem::~FileSystem(){}

} //MODULE
} //TX



extern "C" {

  TX::module::Module* init(boost::property_tree::ptree *configuration) {
    try {
      TX::module::Module*fileSystem = new TX::module::FileSystem (configuration);
      
      return fileSystem;
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
