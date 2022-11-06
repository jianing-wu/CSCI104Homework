#include <iostream>
using namespace std;
struct Node {
    int value;
    Node *next;
    Node() : value(0), next(nullptr) {}
    Node(int x) : value(x), next(nullptr) {}
    Node(int x, Node *next) : value(x), next(next) {}
};

// void split (Node*& in, Node*& odds, Node*& evens) {
// 	if (in == nullptr) {
// 		return;
// 	}
// 	Node* nextNode = in->next;
// 	if (in->value % 2 == 1) {
// 		in->next = odds;
// 		odds = in;
// 	} else {
// 		in->next = evens;
// 		evens = in;
// 	}
// 	in = nextNode;
// 	split(in, odds, evens);
// }

void split(Node*& in, Node*& odds, Node*& evens)
{
    //base case
 	if (in == nullptr) return;
 	//recursion
    split(in->next, odds, evens);
    //split
    if (in->value % 2 == 0) {
        in->next = evens;
        evens = in;
    } else {
        in->next = odds;
        odds = in;
    }
    //set in to NULL
    in = nullptr;
}


void printList(Node* node) {
	while (node != nullptr) {
		cout << node->value << " ";
		Node* next = node->next;
		delete node;
		node = next;
	}
	cout << endl;
}

int main () {
	int arr[] = {-2, -1, 0, 1,2,3};
	int len = sizeof(arr)/sizeof(arr[0]);
	cout << len << endl;
	Node* head = nullptr;
	Node* prev = nullptr; 
	
	for (int i = 0; i < len; i++) {
		Node* cur = new Node(arr[i]);
		cur->next = nullptr;
		cout << "cur: " << cur->value << endl;
		if (i == 0) {
			head = cur;
		} else {
			prev->next = cur;	
		}
		prev = cur;
	}
	// cout << "head: " << head->value << endl;
	// printList(head);

	Node* odds = nullptr;
	Node* evens = nullptr;
	split(head, odds, evens);

	printList(odds);
	printList(evens);
	printList(head);

	return 0;
}