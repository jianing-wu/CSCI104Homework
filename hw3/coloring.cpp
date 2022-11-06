#include <iostream>
#include <fstream>
#include <map>
#include <set>

using namespace std;

bool colorHelper(map<char, set<char>*>& adjMap, map<char, int>& colorMap, char cur) {
	if (colorMap[cur] > 0) {
		return true;
	}
	set<char>* neighbors = adjMap[cur];
	set<char>::iterator it = neighbors->begin();

	// four colors: 1, 2, 3, 4
	// index 0, 1, 2, 3 stands for 4 colors 1, 2, 3, 4 respectively
	bool availableColors[4] = {true, true, true, true};
	
	// check neighbors to find which colors are already taken
	for (; it != neighbors->end(); it++) {
		char nei = *it;
		int neiColor = colorMap[nei];
		if (neiColor > 0) {
			// e.g. color 1 use index 0, color 2 use index 1
			availableColors[neiColor - 1] = false;
		}
	}


	for (int i = 0; i < 4; i++) {
		// when color is available, assign the color, 
		// then go explore neighbors
		if (availableColors[i]) {
			colorMap[cur] = i + 1;
			bool success = true;
			// try neighbors
			for (it = neighbors->begin(); it != neighbors->end(); it++) {
				char nei = *it;
				int neiColor = colorMap[nei];

				// when neighbor not assigned color yet (neighbor color == -1)
				// try assign color to neighbor by recusion
				if (neiColor < 0) {
					// only when all neighor assigned color correctly
					// we can say assign color success
					// so ANS "success" with all neighbors' response
					success &= colorHelper(adjMap, colorMap, nei);
				}
			}
			if (success) {
				return success;
			}
		}
	}
	// after trying all colors, they all unsuccessful
	// return false
	colorMap[cur] = -1;
	return false;
}


map<char, int>* colorMap(map<char, set<char>*> adjMap) {
	map<char, int>* colorMap = new map<char, int>;
	map<char, set<char>*>::iterator it = adjMap.begin();
	for (; it != adjMap.end(); it ++) {
		colorMap->insert(make_pair(it->first, -1));
	}

	colorHelper(adjMap, *colorMap, adjMap.begin()->first);
	return colorMap;
}


// void printAdjMap(map<char, set<char>*> adjMap) {
// 	for (auto const& x : adjMap) {
// 		cout << x.first
//               << ": ";
//         for (auto const& y : *x.second) {
//         	cout << y << " "; 
//         }
//         cout << endl;     
// 	}
// }

void printColorMap(map<char, int>& colorMap) {
	map<char, int>::iterator it = colorMap.begin();
	for (; it != colorMap.end(); it++) {
		cout << it->first << " " << it->second << endl;
	}
}

int main(int argc, char* argv[]) {
	if (argc < 2) {
		return -1;
	}
	int countries = 0;
	int rows = 0;
	int cols = 0;
	ifstream mapFile(argv[1]);
	map<char, set<char>*> adjMap; 
	if (mapFile.is_open()) {
		if (!(mapFile >> countries && mapFile >> rows && mapFile >> cols)) {
			mapFile.close();
			return -1;
		}

		// cerr << countries << " " << rows << " " << cols << endl;
		string prev;
		getline(mapFile, prev);

		int i = 0;
		string line;
		while(i < rows && getline(mapFile, line)) {
			// cerr << i << "th row: " << endl;			
			for (int j = 0; j < cols; j++) {
				char country = line[j];
				// cerr << country;

				map<char, set<char>*>::iterator it = adjMap.find(country);
				if (it == adjMap.end()) {
					set<char>* neighbors = new set<char>;
					it = adjMap.insert(make_pair(country, neighbors)).first;
				}
				// Check up neighbor
				if (i > 0 && country != prev[j]) {
					char neighbor = prev[j];
					it->second->insert(neighbor);
					map<char, set<char>*>::iterator itNei = adjMap.find(neighbor);
					itNei->second->insert(country);
				}
				// Check left neighor
				if (j > 0 && country != line[j - 1]) {
					char neighbor = line[j - 1];
					it->second->insert(neighbor);
					map<char, set<char>*>::iterator itNei = adjMap.find(neighbor);
					itNei->second->insert(country);
				}
			}
			// cout << "\n";
			prev = line;
			i++;
		}
		// printAdjMap(adjMap);
	} else {
		return -1;
	}

	if (!adjMap.empty()) {
		map<char, int>* colored = colorMap(adjMap);
		printColorMap(*colored);
		delete colored;
		for (map<char, set<char>*>::iterator it = adjMap.begin();
			it != adjMap.end(); it++) {
			delete it->second;
		}
	}
	return 0;
}