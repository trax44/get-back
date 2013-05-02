#include <boost/circular_buffer.hpp>
#include <cstdint>
#include <unordered_map>
#include <unistd.h>
#include "Document.hpp"


namespace TX {
namespace module {

Document::Document(boost::property_tree::ptree *_configuration) :
  configuration(_configuration) {

  if (configuration == NULL){
    throw std::runtime_error ("test");
  }

}






bool
Document::processFilePath(const std::string directoryPath, 
			    const std::string filename,
			    const std::string extension,
			    mongo::BSONObjBuilder *requestBuilder) {


  std::string filePath (directoryPath + "/" + filename);


  FILE *fd;

  if ((fd = fopen (filePath.c_str(), "r")) == NULL){
    return false;
  }
  
  

  boost::char_separator<char> sep(".,!?:;[]()<>");
  std::string buffer0 (256, '\0');
  std::unordered_map<std::string, std::uint32_t> words;
  
  ssize_t readSize;  

  readSize = fread((char *)buffer0.data(), 1, 256-1, fd);

  while (readSize > 0) {
    
    boost::tokenizer<boost::char_separator<char> > tokens(buffer0, sep);

    for (auto it : tokens) {
      words[it]++;
    }

    readSize = fread((char *)buffer0.data(), 1, 256-1, fd);
  }
  
  fclose (fd);

  for(auto it : words) {
    requestBuilder->append (it.first, it.second);
  }



  return true;
}


Document::~Document(){}

} //MODULE
} //TX



extern "C" {

  TX::module::Module* init(boost::property_tree::ptree *configuration) {
    try {
      TX::module::Module*skelModule = new TX::module::Document (configuration);

      
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
