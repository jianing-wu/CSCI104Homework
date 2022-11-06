#include <fstream>
#include <iostream>
#include <sstream>
#include <vector>
#include <cstring>
#include "avlbst.h"
#include <map>

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



void printSolution(std::ostream& os, InputMapType& input, OutputMapType& output)
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
void flip(int x1, int y1, const Rectangle& r, vector<vector<bool> >& grid)
{
    for (int x = x1; x < x1+r.length; x++)
    {
        for (int y = y1; y < y1+r.height; y++) grid[x][y] = !grid[x][y];
    }
}



// TODO: Write your backtracking search function here
bool isOverlapped(int x1, int y1,  const Rectangle& r, vector<vector<bool> >& grid) {
    for (int x = x1; x < x1+r.length; x++)
    {
        for (int y = y1; y < y1+r.height; y++) {
            if (grid[x][y]) {
                return true;
            }
        }
    }
    return false;
}


void rotateRec(Rectangle& r) {
    int temp = r.length;
    r.length = r.height;
    r.height = temp;
}

bool findFloorPlanHelper(vector<vector<bool> >& grid, InputMapType::iterator it, OutputMapType& output) {
    if (it == InputMapType.end()) {
        return true;
    }

    Rectangle rec = it->second;
    for (int x = 0; x < grid.size(); x++) {
        for (int y = 0; y < grid[x].size(); y++) {
            if(!isOverlapped(x, y, rec, grid)) {
                flip(x, y, rec, grid);
                if (findFloorPlanHelper(grid, ++it, output)) {
                    output.insert(make_pair(rec.ID, make_pair(x, y)));
                    return true;
                }
                flip(x, y, rec, grid);
                rotateRec(rec);
                flip(x, y, rec, grid);
                if (findFloorPlanHelper(grid, ++it, output)) {
                    output.insert(make_pair(rec.ID, make_pair(x, y)));
                    return true;
                }
                flip(x, y, rec, grid);
                rotateRec(rec);
            }
        }
    }
    return false;
}

bool findFloorPlan(vector<vector<bool> >& grid, InputMapType& input, OutputMapType& output) {
    InputMapType::iterator it = input.begin();
    return findFloorPlanHelper(grid, it, output);
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
    ss >> n;
    ss >> m;
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

    // TODO:  Call your backtracking search function here
    solution_exists = findFloorPlan(grid, input, output);


    if (!solution_exists) {
        ofile << "No solution found.";
    }
    else {
        printSolution(ofile, input, output);
    }
    ofile.close();
    return 0;
}