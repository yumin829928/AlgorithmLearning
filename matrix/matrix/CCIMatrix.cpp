// Cracking Code Interview Matrix problems.

#include "stdafx.h"
#include <iostream>
#include "CCIMatrix.h"

void CCIMatrix::getMaxSubSquareTest() {
	CCIMatrix cci_matrix;
	int size = 6;
	int array2d[][6] = {
		{1, 0, 0, 0, 1, 1},
		{0, 0, 1, 1, 1, 0},
		{1, 0, 0, 0, 0, 1},
		{1, 1, 0, 0, 0, 0},
		{0, 0, 0, 0, 0, 1},
		{0, 0, 0, 0, 1, 0}
	};

	vector<vector<int>> matrix(size, vector<int>(size));
	for (int i = 0; i < size; ++i) {
		matrix[i] = vector<int>(array2d[i], array2d[i] + size);
	}

	Square subsquare = cci_matrix.getMaxSubSquare(matrix);
	cout << "The max subsquare with balck is: (" << subsquare.x << ", " << subsquare.y << ") with size " << subsquare.size;
}

Square CCIMatrix::getMaxSubSquare(const vector<vector<int>> &matrix) {
	Square max_square;
	vector<vector<Cell>> processed = processMaxSubSquare(matrix);
	for (int size = matrix.size(); size > 0; --size) {
		max_square = getSubSquareWithSize(processed, size);
		if (max_square.size > 0) {
			break;
		}
	}

	return max_square;
}

Square CCIMatrix::getSubSquareWithSize(const vector<vector<Cell>> &processed, int size) {
	int bound = processed.size();
	for (int i = 0; i <= bound - size; ++i) {
		for (int j = 0; j <= bound - size; ++j) {
			if (isSquare(processed, i, j, size)) {
				return Square(i, j, size);
			}
		}
	}

	return Square();
}

bool CCIMatrix::isSquare(const vector<vector<Cell>> &processed, int row, int col, int size) {
	if (processed[row][col].zeros_below < size || processed[row][col].zeros_right < size) {
		return false;
	}
	if (processed[row][col+size-1].zeros_below < size) {
		return false;
	}
	if (processed[row+size-1][col].zeros_right < size) {
		return false;
	}

	return true;
}

vector<vector<Cell>> CCIMatrix::processMaxSubSquare(const vector<vector<int>> &matrix) {
	int size = matrix.size();
	vector<vector<Cell>> processed(size, vector<Cell>(size));
	for (int i = size - 1; i >= 0; --i) {
		for (int j = size - 1; j >= 0; --j) {
			// Only handle the black element
			if (matrix[i][j] == 0) {
				int zeros_right = 1;
				int zeros_below = 1;
				if (j + 1 < size) {
					zeros_right += processed[i][j+1].zeros_right;
				}
				if (i + 1 < size) {
					zeros_below += processed[i+1][j].zeros_below;
				}
				processed[i][j].zeros_right = zeros_right;
				processed[i][j].zeros_below = zeros_below;
			}
		}
	}

	return processed;
}