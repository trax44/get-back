#include <iostream>
#include <vector>
#include <memory>
#include <thread>
#include <utility>
#include <functional>
#include <unistd.h>

#include "ThreadSafeQueue.hpp"
#include "Return.hpp"

namespace TX {

template <class T, class R>
class ThreadPool {
private:


  TX::tools::ThreadSafeQueue<T> workQueue;
  TX::tools::ThreadSafeQueue<R> resultQueue;
  std::vector <std::unique_ptr<std::thread> > threads;
  bool run;

  void doWork (int i) {
    while (run) {
      auto work = workQueue.pop();
      if (!work.success) {
	usleep(1);
      } else {
	R res = (*(work.data))();
	resultQueue.push (res);
      }
    }
  }

public:
  ThreadPool(int nbThread = 0) : run (true) {
    if (nbThread == 0){
      nbThread = std::thread::hardware_concurrency();
    }
    
    for (int i = 0 ; i < nbThread ; i++) {

      threads.push_back (std::unique_ptr<std::thread>
			 (new std::thread(&ThreadPool::doWork, this, i)));
    }
  }


  void joinAll () {
    for (std::vector <std::unique_ptr<std::thread> >::iterator 
	   it = threads.begin () , end = threads.end() ;
	 it != end ; ++it){
      it->get()->join ();
    }
  }

  void push (T t) {

    workQueue.push (t);
  }

  Return<R> getJob() {
    return resultQueue.pop();
  }

  void stop (){
    run = false;
    joinAll();
  }
  
  ~ThreadPool () {
    run = false;
    std::cout << "quitting pool" << std::endl;
    // for (auto it : threads) {
    //   (it.get())->join ();
    // }
  }
};


} //TX
