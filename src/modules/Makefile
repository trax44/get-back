CC = gcc
CXX = g++

CXXFLAGS = -Wall -g3 -std=gnu++11 --coverage -O0 -Werror
LDFLAGS = -lm -lboost_filesystem -lboost_system -lboost_thread -lpthread  -L/home/trax/root/lib/ -lmongoclient


libskelmodule.so:SkelModule.o
	$(CXX)  $(CXXFLAGS) -shared -Wl,-soname,libskelmodule.so -o libskelmodule.so $(<)


%.o:%.cpp
	$(CXX)  $(CXXFLAGS) -fPIC -MT $@ -MD -MP -MF `basename $(<) .cpp`.d   -c $(<) -o $@


clean:
	-rm *.o
	-rm *.so
