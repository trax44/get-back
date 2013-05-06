#ifndef TX_THREADSAFEQUEUE_HPP_
#define TX_THREADSAFEQUEUE_HPP_

#include <queue>

#include "SpinLock.hpp"
#include "../tools/Return.hpp"

namespace TX {
namespace tools {

template <class T>
class ThreadSafeQueue {
private:
  std::queue<T>   queue;
  tools::SpinLock  spinLock;
  
  
public:

  bool push (T data) {
    spinLock.lock ();
    queue.push (data);
    spinLock.unlock ();
    
    return true;
  }
  
  Return<T> pop () {
    spinLock.lock ();
    if (!queue.empty()) {
      T ret = queue.front ();
      queue.pop();
      spinLock.unlock ();
      return ret;
    } else {
      spinLock.unlock ();
      return false;
    }
  }

  // T popBlocking () {
  //   bool  ret = false;
  //   spinLock.lock ();
    
  //   while (ret == false) {
  //     std::cout << "popBlocking" << std::endl;
  //     if (queue.empty()) {
  // 	spinLock.unlock();
	

  //       std::unique_lock<std::mutex> lock(m);
  // 	cond_var.wait(lock);


  // 	ret = true;
  //     }
	
  // 	return result;
  //     }
  //   }
  //   return ret;
  // }

  // ~ThreadSafeQueue() {
  //   for (auto it: queue) {
  //     delete (it);
  //   }
  // }
};

}
} //TX

#endif /* TX */
