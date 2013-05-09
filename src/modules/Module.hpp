#ifndef TX_MODULES_MODULE_HPP_
#define TX_MODULES_MODULE_HPP_

#include <string>
#include <mongo/client/dbclient.h>
#include <boost/property_tree/ptree.hpp>
#include <boost/any.hpp>
#include "../tools/Return.hpp"


namespace TX {
namespace module {

class Module {
private:



public:
  const std::string moduleName;
  typedef struct ModuleResult {
    std::string path;
    std::string fileName;
    std::string extension;

    std::vector<std::pair<const std::string, boost::any> > file;
    std::vector<std::pair<const std::string, boost::any> > data;

    void print_boost_any(const boost::any & operand) {

      if (operand.type () == typeid(int)){
	std::cout << boost::any_cast<int>(operand);
      } else if (operand.type () == typeid(char)) {
	std::cout << boost::any_cast<char>(operand);
      } else if (operand.type () == typeid(std::string)) {
	std::cout << boost::any_cast<std::string>(operand);
      }

    }

    void printHeader(){
      std::cout << "path      " << path      << std::endl;
      std::cout << "fileName  " << fileName  << std::endl;
      std::cout << "extension " << extension << std::endl;
    }

    void printFile (){
      std::cout << "file" << std::endl;
      for (auto it: file){
	std::cout << "    " << it.first << ":";
	print_boost_any(it.second);
	std::cout << std::endl;
      }
    }

    void printData (){
      std::cout << "data" << std::endl;
      for (auto it: data){
	std::cout << "    " << it.first << ":";
	print_boost_any(it.second);
	std::cout << std::endl;
      }
    }

    void printAll(){
      printHeader();
      printFile();
      printData();
    }
    

  }RequestResult;

  virtual RequestResult 
  processFilePath(const std::string directoryPath, 
		  const std::string filename,
		  const std::string extension) {
    std::cout << "BITCHE PLEASE ?" << std::endl;
    return RequestResult{};
  };


  virtual const std::string &getName () = 0;
  //   return moduleName;
  // };
  

  virtual ~Module() {}
};



} //module
} //TX


extern "C" TX::module::Module* init_t(boost::property_tree::ptree *configuration);
extern "C" void destroy_t(TX::module::Module*);


#endif /* TX_MODULES */
