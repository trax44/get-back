#ifndef TX_THREADSAFEQUEUE_HPP_
#define TX_THREADSAFEQUEUE_HPP_

#include <queue>
#include "SpinLock.hpp"


namespace TX {
namespace tools {

template <class T>
class ThreadSafeQueue {
private:
  std::queue<T*>   queue;
  tools::SpinLock  spinLock;

public:

  bool push (T *data) {
    spinLock.lock ();
    queue.push (data);
    spinLock.unlock ();
    return true;
  }
  
  T* pop () {
    T* ret = NULL;
    spinLock.lock ();
    if (!queue.empty()) {
      ret = queue.front ();
      queue.pop();
    }
    spinLock.unlock ();
    return ret;
  }

  // ~ThreadSafeQueue() {
  //   for (auto it: queue) {
  //     delete (it);
  //   }
  // }
};

}
} //TX

#endif /* TX */
