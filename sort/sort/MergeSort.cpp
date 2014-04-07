// MergeSort.cpp

#include "stdafx.h"
#include "MergeSort.h"

void MergeSort::test() {
	int a[] = {2, 1, -6, 3, -2, 8, 3, 9, 7, 6};
	//int a[] = {8, 1, 2, -2};
	cout << "Before sort the array is: ";
	print(a, sizeof(a)/sizeof(int));

	sort(a, sizeof(a)/sizeof(int));

	cout << "After sort the array is: ";
	print(a, sizeof(a)/sizeof(int));
	cout << endl;
}

void MergeSort::sort(int *data, int n) {
	int *tmp = new int[n];
	for (int i = 0; i < n; ++i) {
		tmp[i] = data[i];
	}

	int count = mergeSort1(data, 0, n - 1, tmp);
	// int count = mergeSort2(tmp, 0, n - 1, data);
	cout << "The count of inverse pairs is: " << count << endl;

	delete []tmp;
}

int MergeSort::mergeSort1(int *data, int left, int right, int *tmp) {
	int count = 0;
	if (left < right) {	
		int mid = left + (right - left) / 2;
		count += mergeSort1(data, left, mid, tmp);
		count += mergeSort1(data, mid + 1, right, tmp);

		int i = left;
		int j = mid + 1;
		int k = left;
		while (i <= mid && j <= right) {
			if (data[i] <= data[j]) {
				tmp[k++] = data[i++];
			}
			else {
				tmp[k++] = data[j++];
				count += mid - i + 1;
			}
		}

		while (i <= mid) {
			tmp[k++] = data[i++];
		}
		while (j <= right) {
			tmp[k++] = data[j++];
		}

		for (i = left; i <= right; ++i) {
			data[i] = tmp[i];
		}
	}

	return count;
}

int MergeSort::mergeSort2(int *data, int left, int right, int *tmp) {
	int count = 0;
	if (left < right) {	
		int mid = left + (right - left) / 2;
		count += mergeSort2(tmp, left, mid, data);
		count += mergeSort2(tmp, mid + 1, right, data);

		int i = left;
		int j = mid + 1;
		int k = left;
		while (i <= mid && j <= right) {
			if (data[i] <= data[j]) {
				tmp[k++] = data[i++];
			}
			else {
				tmp[k++] = data[j++];
				count += mid - i + 1;
			}
		}

		while (i <= mid) {
			tmp[k++] = data[i++];
		}
		while (j <= right) {
			tmp[k++] = data[j++];
		}
	}

	return count;
}