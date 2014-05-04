// dp.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <iostream>
#include <vector>
#include <string>
using namespace std;

int lis1(int a[], int n) {
	if (n <= 1) {
		return n;
	}

	int *lis = new int[n];
	lis[0] = 1;
	int maxis = lis[0];
	int max_index = -1;
	vector<int> prev_index(n, -1);
	for (int i = 1; i < n; ++i) {
		lis[i] = 1;
		for (int j = 0; j < i; ++j) {
			if (a[j] < a[i] && lis[i] < lis[j] + 1) {
				lis[i] = lis[j] + 1;
				prev_index[i] = j;
			}
		}

		if (lis[i] > maxis) {
			maxis = lis[i];
			max_index = i;
		}
	}

	int prev = max_index;
	while (prev != -1) {
		cout << a[prev] << " ";
		prev = prev_index[prev];
	}

	delete []lis;
	return maxis;
}

int lis2(int a[], int n) {
	if (n <= 1) {
		return n;
	}

	int *lis = new int[n];
	int maxis = 0;
	lis[maxis++] = a[0];
	for (int i = 1; i < n; ++i) {
		if (a[i] > lis[maxis-1]) {
			lis[maxis++] = a[i];
		}
		else {
			// binary search to find the position
			int up = maxis - 1;
			int low = 0;
			int mid;
			while (low < up) {
				mid = low + (up - low) / 2;
				if (a[i] <= lis[mid]) {
					up = mid;
				}
				else {
					low = mid + 1;
				}
			}

			if (a[i] < lis[low]) {
				lis[low] = a[i];
			}
		}
	}

	delete []lis;
	return maxis;
}

string lc_subsequence(const string &str1, const string &str2) {
	int size1 = str1.size();
	int size2 = str2.size();
	vector<vector<int>> lcs(size1+1, vector<int>(size2+1, 0));
	for (int i = 1; i <= size1; ++i) {
		for (int j = 1; j <= size2; ++j) {
			if (str1[i-1] == str2[j-1]) {
				lcs[i][j] = lcs[i-1][j-1] + 1;
			}
			else {
				lcs[i][j] = max(lcs[i-1][j], lcs[i][j-1]);
			}
		}
	}

	string result;
	int xx = size1;
	int yy = size2;
	while (xx > 0 && yy > 0) {
		if (str1[xx-1] == str2[yy-1]) {
			result = str1[xx-1] + result;
			--xx;
			--yy;
		}
		else if (lcs[xx-1][yy] > lcs[xx][yy-1]) {
			--xx;
		}
		else {
			--yy;
		}
	}

	return result;
}

string lc_substring(const string &str1, const string &str2) {
	int max_len = 0;
	int max_index = 0;
	int size1 = str1.size();
	int size2 = str2.size();
	vector<int> lcs(size2+1, 0);
	for (int i = 1; i <= size1; ++i) {
		for (int j = size2; j > 0; --j) {
			if (str1[i-1] == str2[j-1]) {
				lcs[j] = lcs[j-1] + 1;
			}
			else {
				lcs[j] = 0;
			}

			if (lcs[j] > max_len) {
				max_len = lcs[j];
				max_index = j;
			}
		}
	}

	return str2.substr(max_index - max_len, max_len);
}

int _tmain(int argc, _TCHAR* argv[])
{
	int a[] = {2, -4, 3, -6, 6, 0, 12, 6, -2, 9};
	cout << "The longest increasing subsequence using lis1 is: " << lis1(a, sizeof(a)/sizeof(int)) << endl;
	cout << "The longest increasing subsequence using lis2 is: " << lis2(a, sizeof(a)/sizeof(int)) << endl;

	string s1 = "abcdefghab";
	string s2 = "aieghacb";
	cout << "The longest common subsequence is: " << lc_subsequence(s1, s2) << endl;
	cout << "The longest common substring is: " << lc_substring(s1, s2) << endl;

	return 0;
}

