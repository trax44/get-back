#ifndef TX_MODULES_MODULE_HPP_
#define TX_MODULES_MODULE_HPP_

extern "C" void* init(void *configuration);


namespace TX {
namespace modules {

class Module {
public:

  virtual bool processFilePath(const std::string directoryPath, 
			       const std::string filename,
			       const std::string extension) = 0;


  virtual ~Module() {}
};



} //modules
} //TX


#endif /* TX_MODULES */
