
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
			 mongo::BSONObjBuilder &request) {
  
  
  mongo::BSONObj p = request.obj();

  mongo::BSONObjBuilder finaleRequest;
  finaleRequest.append ("$set", p);

  mongo::BSONObj pp = finaleRequest.obj();

  std::string collection (dbName + extenstion);
  
  c.update(collection,
	   BSON("fullPath" << fullPath),
	   pp, 
	   true);

  return true;
}


}
