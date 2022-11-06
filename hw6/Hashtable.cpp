#include <iostream>
#include <time.h>
#include "Hashtable.h"

using namespace std;

Hashtable::Hashtable(bool debug, unsigned int probing)
{
	debug_ = debug;
	// cout << "HB debug" << debug << endl;
	probing_ = probing;
	// cout << "HB probing" << probing << endl;
	table_ = new HashNode*[tableSizes[0]];
	size_ = tableSizes[0];
	sizeIdx_ = 0;
	load_ = 0;
	for (int i = 0; i < size_; i ++) {
		table_[i] = NULL;
	}
}

Hashtable::~Hashtable() {
	for (unsigned int i = 0; i < size_; i++) {
		if (table_[i] != NULL) {
			delete table_[i];
		}
	}
	delete table_;
}

void Hashtable::setWeights(string k, int w[]) const {
	int len = k.length();
	int j = 4;
	int base = 1;
	int baseMax = 26 * 26 * 26 * 26 * 26;
	for (int i = len - 1; i >= 0 && j >= 0; i --) {
		int val = k[i] - 'a';
		w[j] += (val * base);
		if(base == baseMax) {
			base = 1;
			j--;
		} else {
			base *= 26;
		}
	}
}

void Hashtable::setRandoms(int r[]) const {
	if (debug_) {
		for (int i = 0; i < 5; i++) {
			r[i] = randoms[i];
		}
	} else {
		srand(time(NULL));
		for (int i = 0; i < 5; i++) {
			r[i] = rand() % size_;
		}
	}
}

void printArray(int arr[]) {
	for (int i = 0; i < 5; i++) {
		cout << arr[i] << " ";
	}
	cout << endl;
}

int Hashtable::hash (string k) const {
	int w[5] = {0};
	setWeights(k, w);
	// printArray(w);
	int r[5] = {0};
	setRandoms(r);
	// printArray(r);
	long long sum = 0;
	for (int i = 0; i < 5; i++) {
		sum = (sum + (long long)r[i] * w[i]) % size_;
	}
	// cout << k << ": " << sum << endl;
	return (int)sum;
}

int Hashtable::hash2 (string k) const {
	int w[5] = {0};
	setWeights(k, w);
	int p = hashPrimes[sizeIdx_];
	int sum = 0;
	for (int i = 0; i < 5; i ++) {
		sum = (sum + w[i]) % p;
	}
	// cout << "hashing 2 " << k << endl;
	// cout << "h2: " << p - sum << endl;
	return p - sum;
}


void Hashtable::add (string k) {
	// cout << "adding " << k << "..." << endl;
	if (load_ * 2 >= size_) {
		resize();
	}
	int i = 0;
	int h = hash(k);
	int idx = h;
	while(table_[idx] != NULL 
		&& table_[idx]->key_ != k) {
		idx = nextHash(k, h, ++i);
	}
	// cout << "hash: " << h << endl;

	HashNode* cur = table_[idx];
	if (cur == NULL) {
		cur = new HashNode(k, 1);
		table_[idx] = cur;
		load_ ++;
	} else {
		cur->value_ ++;
	}
	// cout << "idx: " << idx << endl;
}

void Hashtable::resize() {
	// cout << "resizing..." << endl;
	if (size_ >= MAX_SIZE) {
		return;
	}
	int oldSize = size_;
	size_ = tableSizes[++ sizeIdx_];
	HashNode** newTable = new HashNode*[size_];
	for (int i = 0; i < size_; i ++) {
		newTable[i] = NULL;
	}
	// cout << "created new table..." << endl;
	// Rehashing
	for (int i = 0; i < oldSize; i ++) {
		if (table_[i] != NULL) {
			HashNode* cur = table_[i];
			string k = cur->key_;
			int step = 0;
			int h = hash(k);
			int newIdx = h;
			while(newTable[newIdx] != NULL) {
				newIdx = nextHash(k, h, ++step);
			}
			newTable[newIdx] = cur;
		}
	}
	// cout << "new size0: " << size_ << endl;
	delete table_;
	table_ = newTable;
	// cout << "new size: " << size_ << endl;
	// cout << endl;
}

int Hashtable::count(string k) {
	int h = hash(k);
	int i = 0;
	int idx = nextHash(k, h, i);
	while (table_[idx] != NULL && i < size_) {
		HashNode* cur = table_[idx];
		if (cur->key_ == k) {
			return cur->value_;
		}
		idx = nextHash(k, h, i);
	}
	return 0;
}

int Hashtable::nextHash(string k, int h, int i) {
	if (probing_ == 0) {
		return (h + i) % size_;
	} else if (probing_ == 1) {
		return (h + i * i) % size_;
	} else if (probing_ == 2) {
		return (h + i * hash2(k)) % size_;
	} else {
		return (h + i) % size_;
	}
}

void Hashtable::reportAll (ostream & os) const {
	for (int i = 0; i < size_; i++) {
		HashNode* node = table_[i];
		if (node != NULL)
			os << node->key_ << " " << node->value_ << "\n";
	}
}