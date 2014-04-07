// MergeSort class

#include "SortBase.h"

class MergeSort : public SortBase {
public:
	void sort(int *a, int n);
	void test();

private:
	int mergeSort1(int *a, int left, int right, int *tmp);
	int mergeSort2(int *a, int left, int right, int *tmp);
};