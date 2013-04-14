#ifndef TX_FILE_BROWSE_HPP_
#define TX_FILE_BROWSE_HPP_

#include <list>
#include <boost/filesystem.hpp>

#include <unordered_set>

#include "Return.hpp"

namespace TX {

class Browse {
public:
  typedef boost::filesystem::path DirectoryEntry;
  typedef boost::filesystem::directory_iterator Container;

  struct PathLevel{
    boost::filesystem::path absoluteCurrentPath;
    Container visitedDirectories;
  };



private:
  const std::string originPath;
  std::stack<PathLevel> currentPath;


public:
  Browse(const std::string &path);

  void stateMachin ();
  bool isVisited (const std::string &path);
  void getDown ();
  bool getUp ();
  Return <DirectoryEntry> getNextDirectory ();
  Return <Browse::DirectoryEntry> browseFiles ();  

  void printCurrentPath ();
  
  ~Browse();
};

} //TX


#endif /* TX_FILE_BROWSE_HPP_ */
