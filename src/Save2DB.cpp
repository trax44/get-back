
#include <exception>
#include <stdint.h>

#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <libgen.h>

#include "Save2DB.hpp"


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

bool Save2DB::saveEntry (const std::string &extenstion,
			 const std::string &fullPath, 
			 const mongo::BSONObj &request) {

  

  c.update(extenstion,
	   BSON("fullPath" << fullPath),
	   request, 
	   true);

  return false;
}


}
