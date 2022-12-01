#include <iostream>
#include "avlbst.h"
#include <vector>
#include <fstream>
#include <sstream>

using namespace std;

bool parse(char* filename, AVLTree<int, int>& vars, vector<vector<int>*>& clauses);
bool isValid(vector<vector<int>*>& clauses,  AVLTree<int,int>& vars);
void solver(vector<vector<int>*>& clauses, AVLTree<int,int>& vars);
bool solverHelper(vector<vector<int>*>& clauses, AVLTree<int,int>& vars, AVLTree<int,int>::iterator current);
bool verify(vector<vector<int>*>& clauses, AVLTree<int, int>& vars);
bool saveSol(char* filename, AVLTree<int, int>& vars, bool solved);

int main(int argc, char* argv[]){
	if(argc < 3){
		cout << "No input and output files given." << endl;
		return 1;
	}


	AVLTree<int, int> vars; //AVLTree<int, bool> vars;
	vector<vector<int>*> clauses;

	if(!parse(argv[1], vars, clauses)){
		cout << "Cannot parse file." << endl;
		return 1;
	}

	solver(clauses, vars);

	bool result = verify(clauses,vars);

	saveSol(argv[2],vars, result);
	
	/*AVLTree<int,int>::iterator it = vars.begin();
	for(;it != vars.end();++it){
		cout << it->first << ": " << it->second << endl;
	}*/

	vector<vector<int>*>::iterator itvec = clauses.begin();
	for(; itvec != clauses.end(); ++itvec){
		delete (*itvec);	
	}
	return 0;
}



bool parse(char* filename, AVLTree<int, int>& vars, vector<vector<int>*>& clauses){
	ifstream infile(filename);
	if(!infile.is_open()){
		return false;
	}

	string line;
	int numVars = 0;
	int numClauses = 0;

	while(getline(infile, line)){

		if(line[0] == 'c'){
			continue;
		}
		else if(line[0] == 'p'){
			stringstream ss(line);
			string garbage;
			ss >> garbage;
			ss >> garbage;
			ss >> numVars >> numClauses;
			if(numVars < 0 || numClauses < 0){
				return false;
			}

			for(int i = 1; i <= numVars; i++){
				vars.insert(make_pair(i, -1));
			}
		}
		else{
			stringstream ss(line);
			int temp;
			vector<int>* tempVec= new vector<int>();
			while(ss >> temp){
				if(temp != 0){
					tempVec->push_back(temp);
				}
			}
			clauses.push_back(tempVec);
		}
	}

	return true;
}


bool isValid( vector<vector<int>*>& clauses,  AVLTree<int,int>& vars){
	bool finalValid = true;
	vector<vector<int>*>::iterator itClause = clauses.begin();
	for(; itClause != clauses.end(); ++itClause){
		// check if a single clause is valid
		bool validClause = true;
		unsigned int falseVarCount = 0;
		vector<int>::iterator itVar= (*itClause)->begin();
		for(;itVar != (*itClause)->end(); ++itVar){
			if((*itVar) < 0){
				int temp = - *itVar;
				AVLTree<int,int>::iterator itAVL = vars.find(temp);
				if(itAVL->second == 1){
					falseVarCount++;
				}
				else if(itAVL->second == 0){
					break;
				}
			}
			else{
				AVLTree<int,int>::iterator itAVL = vars.find(*itVar);
				if(itAVL->second == 0){
					falseVarCount++;
				}
				else if(itAVL->second == 1){
					break;
				}
			}
		}

		if(falseVarCount == (*itClause)->size()){
			validClause = false;
		}
		finalValid = validClause && finalValid;
	}

	return finalValid;
}


void solver(vector<vector<int>*>& clauses, AVLTree<int,int>& vars){
	AVLTree<int, int>::iterator it = vars.begin();
	solverHelper(clauses, vars, it);
}


bool solverHelper(vector<vector<int>*>& clauses, AVLTree<int,int>& vars, AVLTree<int,int>::iterator current){
	if(current == vars.end()){
		return true;
	}

	AVLTree<int,int>::iterator currCopy = current;
	AVLTree<int,int>::iterator next = ++current;

	currCopy->second = 1;
	if(isValid(clauses, vars)){
		if(verify(clauses, vars)){
			return true;
		}
		else if(solverHelper(clauses, vars, next)){
			return true;
		}
	}

	currCopy->second = 0;
	if(isValid(clauses,vars)){
		if(verify(clauses, vars)){
			return true;
		}
		else if(solverHelper(clauses, vars, next)){
			return true;
		}
	}

	currCopy->second = -1;
	return false;
}


bool verify(vector<vector<int>*>& clauses, AVLTree<int, int>& vars){
	vector<vector<int>*>::iterator it = clauses.begin();
	bool solved = true;
	for(; it != clauses.end(); ++it){
		bool singleClauseSolved = false;
		vector<int>::iterator itval = (*it)->begin();
		for(; itval != (*it)->end(); ++itval){
			if(*itval < 0){
				int temp = - *itval;
				AVLTree<int,int>::iterator itAVL = vars.find(temp);
				if(itAVL->second == 0){
					singleClauseSolved = true;
				}
			}
			else{
				AVLTree<int,int>::iterator itAVL = vars.find(*itval);
				if(itAVL->second == 1){
					singleClauseSolved = true;
				}
			}
		}
		solved = singleClauseSolved && solved;
	}

	return solved;

}


bool saveSol(char* filename, AVLTree<int, int>& vars, bool solved){
	ofstream outfile(filename);

	if(!outfile.is_open()){
		cout << "Cannot open output file." << endl;
		return false;
	}
	if(!solved){
		outfile << "No solution" << endl;
		return true;
	}

	AVLTree<int,int>::iterator it = vars.begin();
	for(;it != vars.end();++it){
		if(it->second != -1){
			outfile << it->first << " = " << it->second << endl;
		}		
	}
	return true;
}
