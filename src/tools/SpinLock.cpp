#include "SpinLock.hpp"


namespace TX {

namespace tools {

SpinLock::SpinLock() : padLock(1){}

void SpinLock::lock () {
  // wait for padLock to be set to 1 and atomic reset it to 0 
  while (std::atomic_fetch_and(&padLock, (char)0) == 0);
}

void SpinLock::unlock () {
  padLock = 1;
}


} //tools

} //TX


