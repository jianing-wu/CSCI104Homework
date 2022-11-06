#include "MinHeap.h"
#include <string>
#include <iostream>
using namespace std;

int main() {

	// int array[13] = {10, 14, 35, 19, 28, 39, 36, 43, 16, 25, 7, 18, 9};
	string array[] = {"10", "14", "35", "19", "28", "39", "36", "43", "16", "25", "7", "18", "9"};
    
    MinHeap<string> heap(5);
    
    for (int i = 0; i < 13; i++) {
    	heap.add(array[i], 13 - i);
    }

    heap.print();
    heap.printPri();
    // heap.add("A", 4);
    // heap.add("B", 3);
    // heap.add("C", 10);
    // heap.add("D", 55);
    
    for (int i = 0; i < 16; i++) {
        try {
        	cout << heap.peek() << " ";
        	heap.remove();
    	} catch (const char* msg){
    		cout << msg << endl;
    	}
    }
    cout << endl;
    return 0;
}
