#include <iostream>
#include <unordered_map>


#include "Return.hpp"
#include "Browse.hpp"
#include "Save2DB.hpp"



int main(int argc, char *argv[]) {
  
  if (argc != 2) {
    std::cout << argv[0] << " dir" << std::endl;
    return -1;
  }

  TX::Save2DB  mongodb("localhost", "test");

  TX::Browse browser(argv[1], mongodb);

    
  browser.printCurrentPath();
  return 0;
}


