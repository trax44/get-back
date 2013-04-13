#include <boost/filesystem.hpp>
#include <stack>

#include "Browse.hpp"



namespace TX {

Browse::Browse(const std::string &path) :
  originPath(path) {
  Container initContainer;
  initContainer.insert (path);

  PathLevel initPath {path, initContainer};

  currentPath.push (initPath);

  stateMachin();
}

void Browse::printCurrentPath () {
  std::cout << "currentPath> " << currentPath.top().absoluteCurrentPath.string() << std::endl;
}

void Browse::stateMachin () {
  do {
    std::cout << "----" << std::endl;
    printCurrentPath();
    getDown();
    printCurrentPath();
    browseFiles();
    printCurrentPath();
  } while(getUp ());
}


void Browse::getDown () {
  bool ret_;
  
  do {
    Return <Browse::DirectoryEntry> ret = 
      getNextDirectory ();

    
    ret_ = ret.success;
    std::cout << "  > " << ret.data << std::endl;

    if (ret.success) {
      PathLevel pathLevel;
      pathLevel.absoluteCurrentPath = ret.data;
      pathLevel.visitedDirectories.insert (ret.data.string());

      currentPath.push  (pathLevel);
    }

  } while (ret_);

}

bool Browse::getUp () {
  if (currentPath.size () > 1) {
    currentPath.pop();
    return true;
  } else {
    return false;
  }
}


bool Browse::isVisited (const std::string &path) {
  PathLevel current = currentPath.top();
  auto ret = current.visitedDirectories.find(path);
  return (ret != current.visitedDirectories.end());
}

Return <Browse::DirectoryEntry> Browse::getNextDirectory () {
  if (boost::filesystem::exists(currentPath.top().absoluteCurrentPath)) {
    boost::filesystem::directory_iterator end_itr;

    for (boost::filesystem::directory_iterator itr(currentPath.top().absoluteCurrentPath) ; 
	 itr != end_itr ; ++itr) {

      if (boost::filesystem::is_directory(itr->status()) && 
	  !isVisited(itr->path().string())) {

	currentPath.top().visitedDirectories.insert(itr->path().string());

      	return itr->path();
      }

    }

  }
  return false;
}

Return <Browse::DirectoryEntry> Browse::browseFiles () {
  if (boost::filesystem::exists(currentPath.top().absoluteCurrentPath)) {
    boost::filesystem::directory_iterator end_itr;

    for (boost::filesystem::directory_iterator itr(currentPath.top().absoluteCurrentPath) ; 
	 itr != end_itr ; ++itr) {

      if (!boost::filesystem::is_directory(itr->status())) {
	std::cout << "FILE> " << *itr << std::endl;
      }

    }

  }
  return false;

}



Browse::~Browse() {
  
}


} //TX
