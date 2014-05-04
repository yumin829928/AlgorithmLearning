// matrix.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <iostream>
#include <vector>
#include "CCIMatrix.h"
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

void zeroSegmentTest() {
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
}

bool findInMatrix(vector<vector<int>> &mat, int target, int rl, int ru, int cl, int cu) {
	if (rl > ru || cl > cu) {
		return false;
	}

	if (target < mat[rl][cl] || target > mat[ru][cu]) {
		return false;
	}

	int rmid = (rl + ru) / 2;
	int cmid = (cl + cu) / 2;
	if (mat[rmid][cmid] == target) {
		return true;
	}
	else if (mat[rmid][cmid] < target) {
		return findInMatrix(mat, target, rmid + 1, ru, cl, cmid)
			|| findInMatrix(mat, target, rl, ru, cmid + 1, cu);
	}
	else {
		return findInMatrix(mat, target, rl, rmid - 1, cmid, cu)
			|| findInMatrix(mat, target, rl, ru, cl, cmid - 1);
	}
}

void findInMatrixTest() {
	int rows = 4, cols = 5;
	int array2d[][5] = {
		{1,  8,  12, 20, 30},
		{4,  9,  13, 25, 32},
		{10, 11, 27, 28, 40},
		{12, 18, 36, 41, 56}
	};

	vector<vector<int>> matrix(rows, vector<int>(cols));
	for (int i = 0; i < rows; ++i) {
		matrix[i] = vector<int>(array2d[i], array2d[i] + cols);
	}
	
	cout << "Number 0  " << (findInMatrix(matrix,  0, 0, rows - 1, 0, cols - 1) ? "found" : "not found") << endl;
	cout << "Number 1  " << (findInMatrix(matrix,  1, 0, rows - 1, 0, cols - 1) ? "found" : "not found") << endl;
	cout << "Number 12 " << (findInMatrix(matrix, 12, 0, rows - 1, 0, cols - 1) ? "found" : "not found") << endl;
	cout << "Number 33 " << (findInMatrix(matrix, 33, 0, rows - 1, 0, cols - 1) ? "found" : "not found") << endl;
	cout << "Number 56 " << (findInMatrix(matrix, 56, 0, rows - 1, 0, cols - 1) ? "found" : "not found") << endl;
}

int countNegativeInMatrix(vector<vector<int>> &mat, int rl, int ru, int cl, int cu) {
	if (rl > ru || cl > cu) {
		return 0;
	}

	if (mat[rl][cl] >= 0) {
		return 0;
	}
	if (mat[ru][cu] < 0) {
		return (ru - rl + 1) * (cu - cl + 1);
	}

	int rmid = (rl + ru) / 2;
	int cmid = (cl + cu) / 2;
	if (mat[rmid][cmid] < 0) {
		return countNegativeInMatrix(mat, rmid + 1, ru, cl, cmid) +
			countNegativeInMatrix(mat, rl, ru, cmid + 1, cu) +
			(rmid - rl + 1) * (cmid - cl + 1);
	}
	else {
		return countNegativeInMatrix(mat, rl, rmid - 1, cmid, cu) +
			countNegativeInMatrix(mat, rl, ru, cl, cmid - 1);
	}
}

void countNegativeInMatrixTest() {
	int rows = 4, cols = 5;
	int array2d[][5] = {
		{-10, -8, -7, 20, 30},
		{-6,  -1, 13, 25, 32},
		{-2,  11, 27, 28, 40},
		{-1,  18, 36, 41, 56}
	};

	vector<vector<int>> matrix(rows, vector<int>(cols));
	for (int i = 0; i < rows; ++i) {
		matrix[i] = vector<int>(array2d[i], array2d[i] + cols);
	}

	cout << "The negative number is: " << countNegativeInMatrix(matrix, 0, rows - 1, 0, cols - 1) << endl;
}

int _tmain(int argc, _TCHAR* argv[])
{
	zeroSegmentTest();

	findInMatrixTest();

	countNegativeInMatrixTest();

	CCIMatrix::getMaxSubSquareTest();

	return 0;
}

