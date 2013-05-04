#ifndef TX_SPINLOCK_HPP_
#define TX_SPINLOCK_HPP_

#include <atomic>

namespace TX {

namespace tools {

class SpinLock {
private:
  std::atomic_char padLock;
public:
  SpinLock();
  void lock();
  void unlock();
};

} //tools

} //TX

#endif /* TX */
