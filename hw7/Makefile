CXX = g++ --std=c++11
CXXFLAGS = -g -Wall

all: sat_solver

sat_solver: sat_solver.cpp bst.h avlbst.h
	$(CXX) $(CXXFLAGS) $< -o $@


.PHONY: sat_solver clean

clean:
	rm -f sat_solver