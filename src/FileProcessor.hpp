#ifndef TX_FILEPROCESSOR_HPP_
#define TX_FILEPROCESSOR_HPP_

#include <string>

namespace TX {

class FileProcessor {
public:
  
  virtual bool processFilePath(const std::string directoryPath, 
			       const std::string filename,
			       const std::string extension) = 0;

  virtual ~FileProcessor(){};
};

}

#endif /* TX */
