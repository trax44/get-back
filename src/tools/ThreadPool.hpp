#include <iostream>
#include <vector>
#include <memory>
#include <thread>
#include <utility>
#include <functional>

#include "tools/ThreadSafeQueue.hpp"


template <class T, class R>
class ThreadPool {
private:


  TX::tools::ThreadSafeQueue<std::function<T> > workQueue;
  TX::tools::ThreadSafeQueue<R> resultQueue;
  std::vector <std::unique_ptr<std::thread> > threads;
  bool run;

  void doWork () {
    while (run) {
      auto work = workQueue.pop();
      std::cout << "getting work " << work << std::endl;

      if (work != NULL) {
	R res = (*work)(10, 11);
	std::cout << res << std::endl;
      }
    }
  }

public:
  ThreadPool(int nbThread) : run (true) {

    for (int i = 0 ; i < nbThread ; i++) {

      threads.push_back (std::unique_ptr<std::thread>
			 (new std::thread(&ThreadPool::doWork, this)));
    }

  }


  void joinAll () {
    for (std::vector <std::unique_ptr<std::thread> >::iterator 
	   it = threads.begin () , end = threads.end() ;
	 it != end ; ++it){
      it->get()->join ();
    }
  }

  // void push (T &t, A &a) {
    
  // }
  
  
  virtual ~ThreadPool(){}
};


// struct Bounds{
//   int begin, end;
// };

// int main(int argc, char *argv[]) {
//   int sum = 0;

//   typedef int (*Calculate)(int , int);

//   ThreadPool<int(int,int), int> pool  (4);

//   // for (int i = 0 ; i < 10000 ; i++) {
//   //   calculate(i*1000,(i+1)*1000);
//   // }

//   pool.joinAll();

//   std::cout << sum << std::endl;  

//   return 0;
// }
