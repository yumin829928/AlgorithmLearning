// sort.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <stack>
#include "MergeSort.h"

using namespace std;

stack<int> revertStack(stack<int> &s) {
	stack<int> rs;
	while (!s.empty()) {
		rs.push(s.top());
		s.pop();
	}

	return rs;
}

stack<int> stackSort(stack<int> &s) {
	if (s.size() <= 1) {
		return s;
	}

	stack<int> greater;
	stack<int> less;
	int cur;
	int pivot = s.top();
	s.pop();
	while (!s.empty()) {
		cur = s.top();
		s.pop();
		if (cur > pivot) {
			greater.push(cur);
		}
		else {
			less.push(cur);
		}
	}

	greater = stackSort(greater);
	// Need revert the stack to keep the ascending order
	greater = revertStack(greater);

	less = stackSort(less);
	less.push(pivot);
	while (!greater.empty()) {
		less.push(greater.top());
		greater.pop();
	}

	return less;
}

void stackSortTest() {
	stack<int> s;
	s.push(4);
	s.push(2);
	s.push(6);
	s.push(8);
	s.push(3);
	s.push(5);
	s.push(7);

	s = stackSort(s);
	s = revertStack(s);
	cout << "After stack sort, the sequence is: ";
	while (!s.empty()) {
		cout << s.top() << " ";
		s.pop();
	}
	cout << endl;
}

void swapInArray(int *a, int i, int j) {
	int tmp = a[i];
	a[i] = a[j];
	a[j] = tmp;
}

void duplicateNumbers(int *a, int size, int max_val) {
	if (a == NULL || size <= 0 || size < max_val) {
		return;
	}

	for (int i = 0; i < size; ++i) {
		while (a[i] != i+1 && a[i] != a[a[i]-1]) {
			swapInArray(a, i, a[i]-1);
		}
	}

	cout << "The duplicate values in array are: ";
	for (int i = max_val; i < size; ++i) {
		cout << a[i] << " ";
	}
	cout << endl;
}

void duplicateNumbersTest() {
	int a[] = {7, 1, 2, 3, 3, 1, 3, 6, 7, 6};
	duplicateNumbers(a, sizeof(a)/sizeof(int), 7);
}

int _tmain(int argc, _TCHAR* argv[])
{
	stackSortTest();

	duplicateNumbersTest();

	MergeSort merge_sort;
	merge_sort.test();

	return 0;
}

