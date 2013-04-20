#include <iostream>
#include <unordered_map>


#include "Return.hpp"
#include "Browse.hpp"
#include "Save2DB.hpp"
#include "Configuration.hpp"


int main(int argc, char *argv[]) {
  
  if (argc != 3) {
    std::cout << argv[0] << "confFile dir" << std::endl;
    return -1;
  }

  TX::Configuration configuration(argv[1]);
  TX::Save2DB  mongodb(configuration.getServerHostName(), 
		       configuration.getDataBaseName());

  TX::Browse browser(argv[2], mongodb);

    
  browser.printCurrentPath();
  return 0;
}


