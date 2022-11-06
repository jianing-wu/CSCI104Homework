CXX=g++
CXXFLAGS=-g -Wall -std=c++11
# Uncomment for parser DEBUG
#DEFS=-DDEBUG

OBJS=counting.o hashtable.o

all: counting

counting: $(OBJS)
	$(CXX) $(CXXFLAGS) $(DEFS) -o $@ $(OBJS)

counting.o: counting.cpp avlbst.h bst.h
	$(CXX) $(CXXFLAGS) $(DEFS) -o $@ -c counting.cpp

hashtable.o: Hashtable.cpp Hashtable.h
	$(CXX) $(CXXFLAGS) $(DEFS) -o $@ -c Hashtable.cpp

clean:
	rm -f *.o counting