CXX=g++
CXXFLAGS=-g -Wall -std=c++11
# Uncomment for parser DEBUG
#DEFS=-DDEBUG

OBJS=bayes.o

all: bayes

bayes: $(OBJS)
	$(CXX) $(CXXFLAGS) $(DEFS) -o $@ $(OBJS)

bayes.o: bayes.cpp bayes.h
	$(CXX) $(CXXFLAGS) $(DEFS) -o $@ -c bayes.cpp

clean:
	rm -f *.o bayes