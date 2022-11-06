#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <vector>
#include <unordered_set>
#include "bayes.h"

using namespace std;

int main(int argc, char* argv[]) {
	if (argc < 4) {
		cout << "please specify train file, input file and output file";
		return 0;
	}
	ifstream ifileTrain(argv[1]);
	ifstream ifileClassify(argv[2]);
    ofstream ofileOutput(argv[3]);
    stringstream ss;
    string line;
    int totalObjCount;
    getline(ifileTrain, line);
    ss << line;
    ss >> totalObjCount;
    Bayes bayes;

    // Parse training data and train the bayes classifier
    while (totalObjCount-- > 0 && getline(ifileTrain, line)) {
    	stringstream ss2(line);
    	string object;
    	string adj;
    	vector<string> adjVec;
    	unordered_set<string> dedupSet;
    	ss2 >> object;
    	while (ss2 >> adj) {
    		if (dedupSet.find(adj) == dedupSet.end()) {
    			dedupSet.insert(adj);
    			adjVec.push_back(adj);
    		}
    	}
    	bayes.trainObj(object, adjVec);
    }
    ifileTrain.close();

    // bayes.printTrain();
    ss.str(string());
	ss.clear();
	getline(ifileClassify, line);
	ss << line;
	ss >> totalObjCount;
	
	// Parse classify data and classify them using the bayes classifier
  	while(totalObjCount-- > 0 && getline(ifileClassify, line)) {
  		stringstream ss2(line);
  		string adj;
    	vector<string> adjVec;
    	unordered_set<string> dedupSet;
    	while (ss2 >> adj) {
    		if (dedupSet.find(adj) == dedupSet.end()) {
    			dedupSet.insert(adj);
    			adjVec.push_back(adj);
    		}
    	}
    	ofileOutput << bayes.getMaxProbObj(adjVec) << "\n";
  	}
  	ifileClassify.close();
  	ofileOutput.close();
	return 0;
}