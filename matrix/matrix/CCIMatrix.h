// Cracking Code Interview Matrix problems.

#include <vector>
using namespace std;

struct Square {
	int x;
	int y;
	int size;

	Square() : x(0), y(0), size(0) { }
	Square(int row, int col, int sz) : x(row), y(col), size(sz) { }
};

struct Cell {
	int zeros_right;
	int zeros_below;

	Cell() : zeros_right(0), zeros_below(0) { }
	Cell(int rzeros, int bzeros) : zeros_right(rzeros), zeros_below(bzeros) { }
};

class CCIMatrix {
public:
	Square getMaxSubSquare(const vector<vector<int>> &matrix);
	static void getMaxSubSquareTest();
	
private:
	vector<vector<Cell>> processMaxSubSquare(const vector<vector<int>> &matrix);
	Square getSubSquareWithSize(const vector<vector<Cell>> &processed, int size);
	bool isSquare(const vector<vector<Cell>> &processed, int row, int col, int size);
};