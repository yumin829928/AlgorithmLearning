// sort.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <iostream>
#include <stack>
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

int _tmain(int argc, _TCHAR* argv[])
{
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

	return 0;
}

