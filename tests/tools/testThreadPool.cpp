#include <cmath>
#include <functional>
#include "Return.hpp"
#include "tools/ThreadPool.hpp"
#include "../time.hpp"

int isPrime (int n) {
  if ((n & 1) == 0) {
    return 0;
  }

  int root = (int)(sqrt (n)+1);
  for (int i = 3 ; i < root ; i+= 2) {
    if ((n % i) == 0){
      return 0;
    }
  }
  
  return 1;
}

int calculate (int begin, int end){
  int ret = 0;
  for (int i = begin ; i < end ; i++) {
    ret += isPrime (i);
  }
  
  return ret;
}


int main(int argc, char *argv[]) {
  
  int sum0 = 0;
  int sum1 = 0;

  int size   = 3000;
  int factor = 5000;
  
  struct rusage temps0;
  struct rusage temps1;

  TX::ThreadPool <std::function<int()>*, int> pool  (6);

#define MONO 1
#ifdef MONO
  getrusage(RUSAGE_SELF, &temps0); 
  
  for (int i = 0 ; i < size ; i++) {
    sum0 += calculate(i*factor, (i+1)*factor);
  }  
  getrusage(RUSAGE_SELF, &temps1); 
  TX::mesureTime(&temps0, &temps1);

#else
  std::cout << "--------------------------------------------------" << std::endl;
  
  getrusage(RUSAGE_SELF, &temps0); 
  for (int i = 0 ; i < size ; i++) {
    //std::function<int()> q = std::bind (calculate, i*1000, (i+1)*1000);
    auto q =  new std::function<int()>(std::bind(calculate, i*factor, (i+1)*factor));
    pool.push (q);
  }

  getrusage(RUSAGE_SELF, &temps1); 
  TX::mesureTime(&temps0, &temps1);
  getrusage(RUSAGE_SELF, &temps0); 

  {
    int i = 0;
    while (i < size){
      TX::Return<int> res = pool.getJob();
      if (res.success) {
  	sum1 += res.data;
  	i++;
      }
    }
  }

  getrusage(RUSAGE_SELF, &temps1); 
  TX::mesureTime(&temps0, &temps1);

  pool.stop();

#endif  
  std::cout << "RESULT " << sum0 << " == " << sum1 << std::endl;
  

  return 0;
}

