CC = gcc
CXX = g++

CXXFLAGS = -Wall -g3 -std=gnu++11 --coverage -O0
LDFLAGS = -lm  --coverage -lboost_filesystem -lboost_system

SRC_CPP = $(wildcard *cpp)
OBJS = $(SRC_CPP:.cpp=.o)
EXEC = super-locate

COMPILE := $(CXX) $(CXXFLAGS) $(LDFLAGS) $(OBJS) -o $(EXEC)

debug : CFLAGS += -DDEBUG -g


all:Makefile $(EXEC)

$(EXEC):$(OBJS)
	$(COMPILE)


-include *.d

%.o:%.cpp %.hpp
	$(CXX)  $(CXXFLAGS)  -MT $@ -MD -MP -MF `basename $(<) .cpp`.d   -c $(<) -o $@

%.o:%.cpp
	$(CXX)  $(CXXFLAGS)  -MT $@ -MD -MP -MF `basename $(<) .cpp`.d   -c $(<) -o $@

clean:
	-rm *.d
	-rm $(EXEC)
	-rm *.o
	-rm *gcda *gcno
	-rm *gcov
