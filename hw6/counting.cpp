#include <sstream>
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <ctime>
#include "Hashtable.h"
#include "avlbst.h"

using namespace std;

void printArray(vector<string> vec) {
	for (string s : vec) {
		cout << s << " ";
	}
	cout << endl;
}

int main(int argc, char* argv[]) {
	if (argc < 6) {
		cout << "please specify input, output files, and x, d, r values";
		return 0;
	}
	vector<string> words;
	ifstream ifile(argv[1]);
	ofstream ofile(argv[2]);
	int x, d, r;
	stringstream ss;
	string line;
	ss << argv[3] << ' ' << argv[4] << ' ' << argv[5];
	ss >> x >> d >> r;

	// cout << x << " " << d << " " << r << endl;
	while(getline(ifile, line)) {
		// cout << "line: " << line << endl;
		stringstream ss2(line);
		string word = "";
		while (ss2 >> word) {
			string lcWord = "";
			for (unsigned int i = 0; i < word.length(); i++) {
				if (word[i] >= 'A' && word[i] <= 'Z') {
					lcWord += tolower(word[i]);
				} else if (word[i] >= 'a' && word[i] <= 'z') {
					lcWord += word[i];
				}
			}
			if (!lcWord.empty())
				words.push_back(lcWord);
		}
	}
	ifile.close();
	
	bool debug = (d == 1);
	clock_t start;
    double duration;
    start = clock();
    for (int i = 0; i < r; i++) {
    	// cout << "i: " << i << endl;
		if (x == 0 || x == 1 || x == 2) {
			Hashtable hb(debug, (unsigned int)x);
			for (unsigned int j = 0; j < words.size(); j++) {
				hb.add(words[j]);
			}
		} else if (x == 3) {
			AVLTree<string, int> avlTree;
			for (unsigned int j = 0; j < words.size(); j++) {
				AVLTree<string, int>::iterator it = avlTree.find(words[j]);
				int count = 1;
				if (it != avlTree.end()) {
					count = it->second + 1;
				}
				avlTree.insert(make_pair(words[j], count));
			}			
		}
	}
	duration = ( clock() - start ) / (double) CLOCKS_PER_SEC;
	cout << "Average Runtime: " <<  duration/r << " seconds" << endl;
	cout << "Total Runtime: " <<  duration << " seconds" << endl;
	ofile << "Average Runtime: " << duration/r << " seconds" << "\n";
	ofile << "Total Runtime: " << duration << " seconds" << "\n";
	ofile << "Occurrences:\n";
	if (x == 0 || x == 1 || x == 2) {
		Hashtable hb(debug, x);
		for (unsigned int j = 0; j < words.size(); j++) {
			hb.add(words[j]);
		}
		hb.reportAll(ofile);
	} else if (x == 3) {
		AVLTree<string, int> avlTree;
		for (unsigned int j = 0; j < words.size(); j++) {
			AVLTree<string, int>::iterator it = avlTree.find(words[j]);
			int count = 1;
			if (it != avlTree.end()) {
				count = it->second + 1;
			}
			avlTree.insert(make_pair(words[j], count));
		}
		AVLTree<string, int>::iterator it = avlTree.begin();
		for (; it != avlTree.end(); ++it) {
			ofile << it->first << " " << it->second << "\n";
		}
 	}
	ofile.close();
	return 0;
}