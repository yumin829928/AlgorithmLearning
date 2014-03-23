// dp.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <iostream>
using namespace std;

int lis1(int a[], int n) {
	if (n <= 1) {
		return n;
	}

	int *lis = new int[n];
	lis[0] = 1;
	for (int i = 1; i < n; ++i) {
		lis[i] = 1;
		for (int j = 0; j < i; ++j) {
			if (a[j] < a[i] && lis[i] < lis[j] + 1) {
				lis[i] = lis[j] + 1;
			}
		}
	}

	int maxis = lis[0];
	for (int i = 1; i < n; ++i) {
		if (lis[i] > maxis) {
			maxis = lis[i];
		}
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

int _tmain(int argc, _TCHAR* argv[])
{
	int a[] = {2, -4, 3, -6, 6, 0, 12, 6, -2, 9};
	cout << "The longest increasing subsequence using lis1 is: " << lis1(a, sizeof(a)/sizeof(int)) << endl;
	cout << "The longest increasing subsequence using lis2 is: " << lis2(a, sizeof(a)/sizeof(int)) << endl;

	return 0;
}

