// matrix.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <iostream>
#include <vector>
using namespace std;

// Wrong solution
int getZeroSegmentsDP(vector<vector<int>> &matrix) {
	int size = matrix.size();
	if (size <= 0) {
		return -1;
	}

	int count = 0;
	vector<bool> dp(size+1, false);
	for (int i = 0; i < size; ++i) {
		for (int j = 0; j < size; ++j) {
			if (matrix[i][j] == 0) {
				if (!dp[j] && !dp[j+1]) {
					++count;
				}
				dp[j+1] = true;
			}
			else {
				dp[j+1] = false;
			}
		}
	}

	return count;
}

void fillMatrix(vector<vector<int>> &matrix, int row, int col) {
	matrix[row][col] = 2;
	if (row - 1 >= 0 && matrix[row-1][col] == 0) {
		fillMatrix(matrix, row-1, col);
	}
	if (row + 1 < matrix.size() && matrix[row+1][col] == 0) {
		fillMatrix(matrix, row+1, col);
	}
	if (col - 1 >= 0 && matrix[row][col-1] == 0) {
		fillMatrix(matrix, row, col-1);
	}
	if (col + 1 < matrix.size() && matrix[row][col+1] == 0) {
		fillMatrix(matrix, row, col+1);
	}
}

// Correct solution
int getZeroSegmentsDFS(vector<vector<int>> &matrix) {
	int size = matrix.size();
	if (size <= 0) {
		return -1;
	}

	// Change the cell with 0 to 2
	int count = 0;
	for (int i = 0; i < size; ++i) {
		for (int j = 0; j < size; ++j) {
			if (matrix[i][j] == 0) {
				fillMatrix(matrix, i, j);
				++count;
			}
		}
	}

	// Restore the matrix
	for (int i = 0; i < size; ++i) {
		for (int j = 0; j < size; ++j) {
			if (matrix[i][j] > 1) {
				matrix[i][j] = 0;
			}
		}
	}

	return count;
}

int _tmain(int argc, _TCHAR* argv[])
{
	int array2d[][5] = {
		{0, 1, 1, 1, 1},
		{0, 1, 0, 0, 0},
		{1, 0, 1, 0, 1},
		{0, 0, 0, 0, 1},
		{0, 1, 1, 1, 0}
	};
	vector<vector<int>> matrix(5, vector<int>(5));
	for (int i = 0; i < 5; ++i) {
		matrix[i] = vector<int>(array2d[i], array2d[i] + sizeof(array2d[i])/sizeof(int));
	}

	cout << "The zero segments by DP method are: " << getZeroSegmentsDP(matrix) << endl;
	cout << "The zero segments by DFS method are: " << getZeroSegmentsDFS(matrix) << endl;

	// Print the matrix
	for (int i = 0; i < matrix.size(); ++i) {
		for (int j = 0; j < matrix[i].size(); ++j) {
			cout << matrix[i][j] << " ";
		}
		cout << endl;
	}

	return 0;
}

