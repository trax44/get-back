#ifndef TX_SAVE2DB_HPP_
#define TX_SAVE2DB_HPP_

#include <string>
#include <mongo/client/dbclient.h>

#include "Return.hpp"
#include "FileProcessor.hpp"


namespace TX {

class Save2DB : public FileProcessor{
public:

struct DBConnect: public std::exception {
const std::string who;
DBConnect (const std::string &_what) : who(_what) {}

const char* what() const noexcept {
return who.c_str();
}
};

private:
mongo::DBClientConnection c;
const std::string dbName;
std::string errorMsg;

public:
Save2DB(const std::string &serverName, const std::string &dbName);


static const char *get_filename_ext(const char *filename);
Return<std::string> convertFSPathToMongoDBPath (std::string &fsPath);
bool processFilePath(const std::string directoryPath, 
		       const std::string fileName,
		       const std::string extension);


bool addEntry(const std::string &path);

virtual ~Save2DB(){}
};

} //TX {

#endif /* _SAVE2DB_HPP_ */
