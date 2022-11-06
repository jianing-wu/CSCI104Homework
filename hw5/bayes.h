#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <unordered_map>

using namespace std;

// Bayes Rule example:
// P(fruit | a b c) = 
// P(a | fruit) * P(b | fruit) * P(fruit) / 
// (P(a | fruit) * P(b | fruit) * P(fruit) + P(a | ~fruit) * P(b | ~fruit) * P(~fruit))

class Bayes {
public:
	Bayes() {
		objCounts = new unordered_map<string, int>;
		objAdjCounts = new unordered_map<string, unordered_map<string, int>*>;
		adjCounts = new unordered_map<string, int>;
		totalObjCount = 0;
	}

	~Bayes() {
		delete objCounts;
		delete adjCounts;
		unordered_map<string, unordered_map<string, int>*>::iterator it;
		for (it = objAdjCounts->begin(); it != objAdjCounts->end(); it++) {
			delete it->second;
		}
		delete objAdjCounts;
	}

	// Calculate Pr(adjective | not object)
	double getCondProbNotObj(string adjective, string object) {
		int objCount = objCounts->at(object);
		int adjTotalCount = 0;
		if (adjCounts->find(adjective) != adjCounts->end())
			adjTotalCount += adjCounts->at(adjective);

		unordered_map<string, int>* adjFreq = objAdjCounts->at(object);
		int adjObjCount = 0;
		if (adjFreq->find(adjective) != adjFreq->end())
			adjObjCount += adjFreq->at(adjective);

		int occNotObj = totalObjCount - objCount;
		int occAdjNotObj = adjTotalCount - adjObjCount;
		// cout << "\nCond Prob Not Object for " << object << ": ";
		// cout << adjective << ": " << 1 + occAdjNotObj << "/" << 1 + occNotObj << " ";
		// cout << (1.0 + occAdjNotObj) / (1.0 + occNotObj) << endl;
		return (1.0 + occAdjNotObj) / (1.0 + occNotObj);
	}

	// Calculate Pr(adjective | object)
	double getCondProbObj(string adjective, string object) {
		int occObject = objCounts->at(object);
		unordered_map<string, int>* adjFreq = objAdjCounts->at(object);
		int occObjAdj = 0;
		if (adjFreq->find(adjective) != adjFreq->end()){
			occObjAdj += adjFreq->at(adjective);
		}
		// cout << "\nCond Prob for " << object << ": ";
		// cout << adjective << ": " << 1 + occObjAdj << "/" << 1 + occObject << " ";
		// cout << (1.0 + occObjAdj) / (1.0 + occObject) << endl;
		return (1.0 + occObjAdj) / (1.0 + occObject);
	}


	// use Bayes rule to calculate Pr(objective | adjectives)
	double getObjProb(vector<string>& adjs, string object) {
		double adjObjProb = 1.0;
		double adjNotObjProb = 1.0;
		for (unsigned int i = 0; i < adjs.size(); i++) {
			adjObjProb *= getCondProbObj(adjs[i], object);
			adjNotObjProb *= getCondProbNotObj(adjs[i], object);
		}
		double objProb = 1.0 * objCounts->at(object) / totalObjCount;
		double notObjProb = 1.0 - objProb;

		// cout << object << "prob: " << objProb << endl;
		// cout << "not " << object << "prob: " << notObjProb << endl;
		// cout << object << ": " << adjObjProb * objProb / (adjObjProb * objProb + adjNotObjProb * notObjProb) << endl;
		return adjObjProb * objProb / (adjObjProb * objProb + adjNotObjProb * notObjProb);
	}

	// Classify method to classify a list of adjectives to an object
	string getMaxProbObj(vector<string>& adjs) {
		double maxProb = 0;
		string maxProbObj = "";
		unordered_map<string, int>::iterator it = objCounts->begin();
		for (; it != objCounts->end(); it++) {
			double prob = getObjProb(adjs, it->first);
			if (prob > maxProb) {
				maxProb = prob;
				maxProbObj = it->first;
			}
		}
		// cout <<  maxProbObj << ": " << maxProb << endl;
		return maxProbObj;
	}


	// Train an object with a list of adjectives
	void trainObj(string object, vector<string>& adjs) {
		unordered_map<string, int>::iterator it1 = objCounts->find(object);
		if (it1 != objCounts->end()) {
			it1->second ++;
		} else {
			objCounts->insert(make_pair(object, 1));
		}
		// update objAdjCounts map
		unordered_map<string, unordered_map<string, int>*>::iterator it2;
		it2 = objAdjCounts->find(object);
		if (it2 == objAdjCounts->end()) {
			objAdjCounts->insert(make_pair(object, new unordered_map<string, int>));
			it2 = objAdjCounts->find(object);
		}
		unordered_map<string, int>* objAdjCounts = it2->second;
		for (unsigned int i = 0; i < adjs.size(); i++) {
			string adj = adjs[i];
			// update objAdjCounts map
			unordered_map<string, int>::iterator it3 = objAdjCounts->find(adj);
			if (it3 != objAdjCounts->end()) {
				it3->second ++;
			} else {
				objAdjCounts->insert(make_pair(adj, 1));
			}
			
			// update adjCounts map
			it3 = adjCounts->find(adj);
			if (it3 != adjCounts->end()) {
				it3->second ++;
			} else {
				adjCounts->insert(make_pair(adj, 1));
			}
		}
		totalObjCount++;
	}
	

	void printMap(unordered_map<string, int>* map) {
		for(unordered_map<string, int>::iterator it = map->begin(); it != map->end(); ++it)
		{
			cout << it->first << " " << it->second << "\n";
		}
	}

	void printTrain() {
		cout << "\nTotal objects: " << totalObjCount << endl;
		cout << "\nObject Counts: " << endl;
		printMap(objCounts);

		cout << "\nAdjective Counts: " << endl;
		printMap(adjCounts);

		cout << "\nObj Adj Counts: " << endl;
		for(auto it = objAdjCounts->cbegin(); it != objAdjCounts->cend(); ++it)
		{
			cout << it->first << ":\n";
			printMap(it->second);
			cout << endl;
		}
		cout << endl;
	}
private:
	// key: object, value: total frequency of the object
	unordered_map<string, int>* objCounts; 
	// Two layer map, first key: object, second key: adjective, 
	// value: the frequency of adjective and object that occurs together
	unordered_map<string, unordered_map<string, int>*>* objAdjCounts;
	// key: adjective, value: total frequency of the adjective
	unordered_map<string, int>* adjCounts;
	// how many objects total
	int totalObjCount;
};