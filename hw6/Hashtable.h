#include <string>
#include <vector>
#include <iostream>
#include <utility>

using namespace std;

#define MAX_SIZE 1685759167

static const int tableSizes[] = {11, 23, 47, 97, 197, 
		397, 797, 1597, 3203, 6421, 12853, 25717, 51437, 
		102877, 205759, 411527, 823117, 1646237, 3292489, 
		6584983, 13169977, 26339969, 52679969, 105359969, 
		210719881, 421439783, 842879579, 1685759167};

static const int hashPrimes[] = {7, 19, 43, 89, 193, 389, 
	787, 1583, 3191, 6397, 12841, 25703, 51431, 102871, 
	205721, 411503, 823051, 1646221, 3292463, 6584957, 
	13169963, 26339921, 52679927, 105359939, 210719881, 
	421439749, 842879563, 1685759113};

static const int randoms[] = {983132572, 62337998, 
	552714139, 984953261, 261934300};

class HashNode {
public:
	string key_;
	int value_;
	HashNode(string key, int value) {
		key_ = key;
		value_ = value;
	}
};

class Hashtable {
public:
	Hashtable (bool debug = false, unsigned int probing = 0);
	~Hashtable();
	void add (string k);
	int count (string k);
	void reportAll (ostream & os) const;

private:
	void resize();
	int hash (string k) const;
	int hash2 (string k) const;
	void setWeights(string k, int w[]) const;
	void setRandoms(int r[]) const;
	// int find(string k) const;
	int nextHash(string k, int h, int i);

	int probing_; // 0 linear probing, 1 quadratic probing, 2 double hashing
	bool debug_;
	HashNode** table_;
	int size_;
	int sizeIdx_;
	int load_;
};

