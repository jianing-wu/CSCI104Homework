/* Write your test code for the ULListStr in this file */

#include <iostream>
#include "ulliststr.h"
using namespace std;

void printSize(ULListStr* list) {
	cout << "size: " << list->size() << endl;
}

void printFront(ULListStr* list) {
	cout << "front: " << list->front() << endl;
}

void printBack(ULListStr* list) {
	cout << "back: " << list->back() << endl;
}

void printGetI(ULListStr* list, int i) {
	cout << "get(" << i << "): " << list->get(i) << endl;
}

void printList(ULListStr* list) {
	printSize(list);
	if (list->size() > 0) {
		printFront(list);
		printBack(list);
	}
	cout << "list: ["; 
	for (size_t i = 0; i < list->size(); i++) {
		if (i > 0) {
			cout << ",";
		} 
		cout << list->get(i);
	}
	cout << "]" << endl;
}


void printBefore(ULListStr* list) {
	cout << "Before:" << endl;
	printList(list);
}

void printAfter(ULListStr* list) {
	cout << "After:" << endl;
	printList(list);
}

int main(int argc, char* argv[])
{
	ULListStr listA;

	cout << "\nPop back empty list" << endl;
	printBefore(&listA);
	listA.pop_back();
	printAfter(&listA);

	cout << "\nPop front empty list" << endl;
	printBefore(&listA);
	listA.pop_front();
	printAfter(&listA);

	cout << "\nPush back an empty list with strings \"University\", \"of\", \"Southern\", \"California\"" << endl;
	printBefore(&listA);
	listA.push_back("University");
	listA.push_back("of");
	listA.push_back("Southern");
	listA.push_back("California");
	printAfter(&listA);
	printGetI(&listA, 0);
	
	cout << "\nPop back list: [University,of,Southern,California]" << endl;
	printBefore(&listA);
	listA.pop_back();
	printAfter(&listA);

	cout << "\nPush front an empty list with strings \"University\", \"of\", \"Southern\", \"California\"" << endl;
	ULListStr listB;
	printBefore(&listB);
	listB.push_front("University");
	listB.push_front("of");
	listB.push_front("Southern");
	listB.push_front("California");
	printAfter(&listB);
	printGetI(&listB, 0);

	cout << "\nPop front list: [University,of,Southern,California]" << endl;
	printBefore(&listB);
	listB.pop_front();
	printAfter(&listB);

	cout << "\nConstructing A Relatively Big List" << endl;
	ULListStr dat;
	cout << "Push back 11 elements: 0, 1, 2, 3, ... ... , 10" << endl;
	for (int i = 0; i < 11; i++) {
		dat.push_back(to_string(i));
	}
	printList(&dat);

	cout << "\nPush front 11 elements: -11, -10, -9, ... ... , -1" << endl;
	for (int i = -1; i >= -11; i--) {
		dat.push_front(to_string(i));
	}
	printList(&dat);

	cout << "\nPop back 5 elements" << endl;
	for (size_t i = 0; i < 5; i++) {
		dat.pop_back();
	}
	printList(&dat);
	
	cout << "\nPop front 5 elements" << endl;
	for (size_t i = 0; i < 5; i++) {
		dat.pop_front();
	}
	printList(&dat);


	try {
		ULListStr listC;
		for (int i = 0; i < 5; i++) {
			listC.push_back(to_string(i));
		}
      	cout << "\nTest Bad location access, get(6) of list [1,2,3,4,5]" << endl;
      	listC.get(6);
  	}
  	catch (invalid_argument& ia) {
  		cout << "Catched invalid_argument: " << ia.what() << endl;
  	}


  	try {
		ULListStr listD;
		for (int i = 0; i < 5; i++) {
			listD.push_back(to_string(i));
		}
      	cout << "\nTest bad location access: get(-1) of list [1,2,3,4,5]" << endl;
      	listD.get(-1);
  	}
  	catch (invalid_argument& ia) {
  		cout << "Catched invalid_argument: " << ia.what() << endl;
  	}

	return 0;
}
