#include <fstream>
#include <iostream>
#include <sstream>
#include <vector>
#include <cstring>
#include "avlbst.h"
#include <map>
#include <utility>

using namespace std;

struct Rectangle
{
    int ID;
    int length;
    int height;
};

// Typedefs for you input and output map. Start with
// std::map but once the backtracking search algorithm is working
// try to use your AVL-tree map implementation by changing these
// typedef's
typedef std::map<int, Rectangle> InputMapType;
typedef std::map<int, std::pair<int, int> > OutputMapType;

// Allowed global variables: the dimensions of the grid
int n; // X-dim size
int m; // Y-dim size

// No other global variables are allowed

// A dummy operator << for Rectangles so the BST and AVL BST will
// compile with their printRoot() implementations
std::ostream& operator<<(std::ostream& os, const Rectangle& r)
{
    os << r.ID;
    return os;
}

// A dummy operator << for pairs so the BST and AVL BST will
// compile with their printRoot() implementations
template <typename T, typename U>
std::ostream& operator<<(std::ostream& os, const std::pair<T,U>& p)
{
    os << p.first << "," << p.second;
    return os;
}


class Floorplan
{
public:
    Floorplan(vector<vector<bool> >& grid);
    ~Floorplan();
    void printSolution(std::ostream& os, InputMapType& input, OutputMapType& output);
    void flip(int x1, int y1, const Rectangle& r, vector<vector<bool> >& grid);
    bool overlap(const Rectangle r1, const Rectangle r2);
    bool isValid(InputMapType IDMap);
    void solve(InputMapType IDMap);
    bool solveHelper(InputMapType IDMap, InputMapType::iterator curr);
    
private:
    vector<vector<bool> > grid_;
    //InputMapType IDMap;
    OutputMapType floorPlan;
    //int numOfRecs;

}

Floorplan::Floorplan(vector<vector<bool> >& grid)
{
    grid_ = grid;
    //IDMap = input;
    //numOfRecs = x;
}

Floorplan::~Floorplan()
{
    
}

void Floorplan::printSolution(std::ostream& os, InputMapType& input, OutputMapType& output)
{
    for (OutputMapType::iterator it = output.begin(); it != output.end(); ++it)
    {
        InputMapType::iterator rbit = input.find(it->first);
        os << it->first << " ";
        os << it->second.first << " ";
        os << it->second.second << " ";
        os << rbit->second.length << " ";
        os << rbit->second.height << endl;
    }
}

// Changes the grid entries to their opposite values for the
// rectangle r starting at x1,y1
void Floorplan::flip(int x1, int y1, const Rectangle& r, vector<vector<bool> >& grid)
{
    for (int x = x1; x < x1+r.length; x++)
    {
        for (int y = y1; y < y1+r.height; y++) grid[x][y] = !grid[x][y];
    }
}

// Test if two tiles placed on the floor overlap
bool Floorplan::overlap(const Rectangle r1, const Rectangle r2)
{
    if (floorPlan.find(r1.ID) == floorPlan.find(r2.ID))
    {
        return true;
    }
    
    return false;
}

bool Floorplan::isValid(InputMapType IDMap)
{
    /*check if valid: 1. empty space (for every grid that this rectangle will occupy, grid[x][y]/iterator == false)
                      2. doesn't overlap with any previous placed rectangle
    */
}

void Floorplan::solve(InputMapType IDMap)
{
    InputMapType::iterator it = IDMap.begin();
    solveHelper(IDMap, it);
}

bool Floorplan::solveHelper(InputMapType IDMap, InputMapType::iterator curr)
{
    
    //iterate through each rectangle, once placed, call again for the next rectangle; once wrong, backtrack
        
    if (curr == IDMap.end()) {
        return true;
    }
    
    InputMapType::iterator rec = curr;
    InputMapType::iterator nextRec = ++curr;
    
    
    
    (rec->second).length
    (rec->second).height
        
        //if height, length both fit, true
        //if overlap any of the previous placed rectangles, false
        
}



int main(int argc, char *argv[])
{
    if (argc < 3) {
        cout << "please specify an input and output file";
        return 0;
    }
    ifstream ifile(argv[1]);
    stringstream ss;
    string line;
    ofstream ofile(argv[2]);
    int x;
    getline(ifile, line);
    ss << line;
    ss >> n; //length
    ss >> m; //height
    ss >> x;

    InputMapType input;
    OutputMapType output;
    for (int i = 0; i < x; i++) {
        getline(ifile, line);
        stringstream ss2(line);
        Rectangle r;
        ss2 >> r.ID;
        ss2 >> r.length;
        ss2 >> r.height;
        input.insert(std::make_pair(r.ID, r));
    }
    ifile.close();
    vector<vector<bool> > grid;

    for (int i = 0; i < n; i++)
    {
        grid.push_back(vector<bool>(m, false));
    }
    InputMapType::iterator it = input.begin();
    bool solution_exists = false;

    //backtracking search function call
    Floorplan fp = Floorplan(grid);
    solve(input);
    



    if (!solution_exists) {
        ofile << "No solution found.";
    }
    else {
        printSolution(ofile, input, output);
    }
    ofile.close();
    return 0;
}
