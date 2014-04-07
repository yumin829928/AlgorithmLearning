// Virtual base class for sort interface

class SortBase {
public:
	virtual void sort(int *a, int n) = 0;

	virtual void test() = 0;

	virtual void print(int *a, int n);
};