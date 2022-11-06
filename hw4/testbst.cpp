#include <fstream>
#include <iostream>
#include <sstream>
#include <vector>
#include <cstring>
#include "bst.h"
#include "print_bst.h"

using namespace std;

int main(int argc, char *argv[])
{
	BinarySearchTree<int, int> bst;

	bst.insert(make_pair(1,1));
	bst.insert(make_pair(2,2));
	bst.insert(make_pair(3,3));
	bst.insert(make_pair(-1,-1));

	// bst.printRoot()
	return 0;
}