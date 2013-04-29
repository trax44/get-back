CC = gcc
CXX = g++

SUBDIRS = modules

CXXFLAGS = -Wall -g3 -std=gnu++11 --coverage -O0 -Werror
LDFLAGS = -lm -lboost_filesystem -lboost_system -lboost_thread -lpthread  -L/home/trax/root/lib/ -lmongoclient -ldl

SRC_CPP = ./Browse.cpp \
./Configuration.cpp \
./ModuleManager.cpp \
./Save2DB.cpp \
./main.cpp 




OBJS=$(SRC_CPP:.cpp=.o)



EXEC = super-locate

COMPILE := $(CXX) $(CXXFLAGS)  $(OBJS) $(LDFLAGS)  -o $(EXEC)

debug : CFLAGS += -DDEBUG -g


all:Makefile $(EXEC) subdirs

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



.PHONY: subdirs $(SUBDIRS)

subdirs: $(SUBDIRS)

$(SUBDIRS):
	$(MAKE) -C $@
