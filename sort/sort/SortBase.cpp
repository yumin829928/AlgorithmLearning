// SortBase.cpp

#include "stdafx.h"
#include "SortBase.h"

void SortBase::print(int *a, int n) {
	for (int i = 0; i < n; ++i) {
		cout << a[i] << " ";
	}
	cout << endl;
}