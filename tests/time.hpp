#include <sys/time.h>
#include <sys/resource.h>
#include <unistd.h>


#define DELTA_TIME(X, Y) (((Y).tv_usec - (X).tv_usec) + 1000*1000*((Y).tv_sec - (X).tv_sec))


namespace TX {
void mesureTime (struct rusage *temps0, struct rusage *temps1);


void mesureTime (struct rusage *temps0, struct rusage *temps1){
  
  fprintf(stderr, "temps utilisateur %ld\ntemps systeme %ld\n",
	  DELTA_TIME(temps0->ru_utime, temps1->ru_utime),
	  DELTA_TIME(temps0->ru_stime, temps1->ru_stime)
	  );
 
}

};
