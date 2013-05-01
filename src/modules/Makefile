CC = gcc
CXX = g++

CXXFLAGS = -Wall -g3 -std=gnu++11 --coverage -O0 -Werror
LDFLAGS = -lm -lboost_filesystem -lboost_system -lboost_thread -lpthread  -L/home/trax/root/lib/ -lmongoclient


all:libskelmodule.so libFileSystem.so

libskelmodule.so:SkelModule.o
	$(CXX)  $(CXXFLAGS) -shared -Wl,-soname,$@ -o $@ $(<)

libFileSystem.so:FileSystem.o
	$(CXX)  $(CXXFLAGS) -shared -Wl,-soname,$@ -o $@ $(<)


%.o:%.cpp
	$(CXX)  $(CXXFLAGS) -fPIC -MT $@ -MD -MP -MF `basename $(<) .cpp`.d   -c $(<) -o $@


clean:
	-rm *.o
	-rm *.so
