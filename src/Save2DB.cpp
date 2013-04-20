#include "Save2DB.hpp"

#include <exception>
#include <stdint.h>

namespace TX {
  Save2DB::Save2DB(const std::string &serverName, const std::string &_dbName) :
    dbName(_dbName){
    std::string errorMsg;
  
    if (!c.connect(serverName, errorMsg)) {
      throw DBConnect(errorMsg);
    }
  }


  Return<std::string> Save2DB::convertFSPathToMongoDBPath (std::string &fsPath) {
    /// TODO  check path for double /

    for (std::string::iterator it = fsPath.begin() , end = fsPath.end() ; 
	 it != end ; ++it) {
    
      if (*it == '/') {
	*it = '.';
      }
    
    }

    fsPath.insert (0, dbName);

    return fsPath;
  }

  //http://stackoverflow.com/questions/5309471/getting-file-extension-in-c
  const char *Save2DB::get_filename_ext(const char *filename) {
    if (filename == NULL){
      return NULL;
    }
    const char *dot = strrchr(filename, '.');

    if(!dot || dot == filename) {
      return NULL;
    } else {
      return dot + 1;
    }
  }


#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <libgen.h>

  bool Save2DB::processFilePath(const std::string directoryPath, 
				const std::string filename,
				const std::string extension) {


    std::string fullpath (directoryPath + "/" + filename);

    struct stat buf;
    if (!stat(fullpath.c_str(), &buf)) {

      
      mongo::BSONObjBuilder b, set;
      b.append("name",      filename);
      b.append("directory", directoryPath);
      b.append("type",      extension);

      b.append("modifier_date", uint32_t(buf.st_mtime));
      b.append("size", uint32_t(buf.st_size));
      mongo::BSONObj p = b.obj();
    
      std::string collection (dbName);

      if (extension != "") {
	collection.append(extension);
      } else {
	collection.append(".noExtention");
      }

      set.append ("$set", p);
      mongo::BSONObj pp = set.obj();

      c.update(collection,
	       BSON("fullPath" << fullpath),
	       pp , 
	       true);


    } 
    return true;
  }
}
