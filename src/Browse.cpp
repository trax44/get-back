#include <boost/filesystem.hpp>
#include <stack>
#include <algorithm> 

#include "FileProcessor.hpp"
#include "Browse.hpp"


namespace TX {

Browse::Browse(const std::string &path, FileProcessor &_fileProcessor) :
  originPath(path),
  fileProcessor(_fileProcessor){
  
  Container initContainer;
  initContainer = boost::filesystem::directory_iterator (path);

  PathLevel initPath {path, initContainer};

  currentPath.push (initPath);


  stateMachin();
}

void Browse::printCurrentPath () {
  std::cout << "currentPath> " << currentPath.top().absoluteCurrentPath.string() << std::endl;
}

void Browse::stateMachin () {
  bool ret;
  do {
    printCurrentPath();
    getDown();
    printCurrentPath();
    browseFiles();
    printCurrentPath();
    ret = getUp();
  } while(ret);
}


void Browse::getDown () {
  bool ret_;
  
  do {
    Return <Browse::DirectoryEntry> ret = 
      getNextDirectory ();

    
    ret_ = ret.success;

    if (ret.success) {
      PathLevel pathLevel;
      pathLevel.absoluteCurrentPath = ret.data;
      pathLevel.visitedDirectories = boost::filesystem::directory_iterator (ret.data);
      

      currentPath.push  (pathLevel);
    }

  } while (ret_);

}

bool Browse::getUp () {
  if (currentPath.size () > 1) {
    currentPath.pop();
    currentPath.top().visitedDirectories++;
    return true;
  } else {
    return false;
  }
}


bool Browse::isVisited (const std::string &path) {
  // PathLevel current = currentPath.top();
  // auto ret = current.visitedDirectories.find(path);
  // return (ret != current.visitedDirectories.end());
  return false;
}

Return <Browse::DirectoryEntry> Browse::getNextDirectory () {
  if (boost::filesystem::exists(currentPath.top().absoluteCurrentPath)) {
    boost::filesystem::directory_iterator end_itr;

    for (; 
	 currentPath.top().visitedDirectories != end_itr ; 
	 currentPath.top().visitedDirectories++) {

      if (boost::filesystem::is_directory(currentPath.top().visitedDirectories->status())) {

	//currentPath.top().visitedDirectories = itr;

      	return currentPath.top().visitedDirectories->path();
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

	fileProcessor.processFilePath(itr->path().parent_path().string(),
				      itr->path().filename().string(),
				      itr->path().extension().string());
      }

    }

  }
  return false;

}



Browse::~Browse() {
  
}


} //TX
