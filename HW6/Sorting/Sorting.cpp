#include <algorithm>
#include <iostream>

using std::cout;
using std::endl;
using std::swap;
using std::copy;

template <class T>
void MergePass(T *a, T *b, const int n, const int s);
template <class T>
void Merge(T *a, T *b, const int k, const int m, const int n);
template <class T>
int rMergeSort(T *a, int *Link, const int left, const int right);
template <class T>
int ListMerge(T *a, int *Link, const int start1, const int start2);
template <class T>
void Adjust(T *a, const int root, const int n);

// Insertion Sort ----------------------------------
template <class T>
void InsertionSort(T *a, const int n)
{
	int i;
	for (int j = 2; j <= n; j++) {
		a[0] = a[j];
		for (i = j - 1; a[i] > a[0]; i--)
			a[i + 1] = a[i];
		a[i + 1] = a[0];
	}
}

// Quick Sort --------------------------------------
template <class T>
void QuickSort(T *a, const int left, const int right)
{
	if (left < right) {
		T &pivot = a[left];
		int i = left;
		int j = right + 1;
		do {
			do j--; while (a[j] > pivot);
			do i++; while (a[i] < pivot);
			if (i < j)
				swap(a[i], a[j]);
		} while (i < j);
		swap(pivot, a[j]);
		QuickSort(a, left, j - 1);
		QuickSort(a, j + 1, right);
	}
}

// Iterative Merge Sort ----------------------------
template <class T>
void MergeSort_iter(T *a, const int n)
{
	T *templist = new T[n + 1];
	for (int s = 1; s < n; s *= 2) {
		MergePass(a, templist, n, s);
		s *= 2;
		MergePass(templist, a, n, s);
	}
	delete [] templist; 
}

template <class T>
void MergePass(T *a, T *b, const int n, const int s)
{
	int i;
	for (i = 1; i <= n-(2*s)+1; i += 2*s)
		Merge(a, b, i, i + s - 1, i + (2 * s) -1);
	if ((i + s - 1) < n)
		Merge(a, b, i, i + s - 1, n);
	else 
		copy(a + i, a + n + 1, b + i);
}

template <class T>
void Merge(T *a, T *b, const int k, const int m, const int n)
{
	int i1, i2, i3;
	for (i1 = k, i2 = m+1, i3 = k;
		 i1 <= m && i2 <= n;
		 i3++) {
		if (a[i1] <= a[i2]) {
			b[i3] = a[i1];
			i1++;
		} else {
			b[i3] = a[i2];
			i2++;
		}
	}
	if (i2 > n) copy(a + i1, a + m + 1, b + i3);
	if (i1 > m) copy(a + i2, a + n + 1, b + i3);
}

// Recursive Merge Sort ----------------------------
template <class T>
void MergeSort_rec(T *a, const int n)
{
	int *link = new int [n + 1];
	int cur;
	
	for (int i = 0; i <= n; i++)
		link[i] = 0;
	cur = rMergeSort(a, link, 1, n);
	
	T *tempList = new T [n + 1];
	// tempList[0] = 0;
	for (int i = 1; i <= n; i++) {
		tempList[i] = a[cur];
		cur = link[cur];
	}
	copy(tempList, tempList + n + 1, a);
	delete [] link;
	delete [] tempList;
}

// return the head of a list containing the indexes of the sorted list.
// link[i] gives the record index that follows record i in the sorted sublist
template <class T>
int rMergeSort(T *a, int *Link, const int left, const int right)
{
	if (left >= right) return left;	// Base case
	int mid = (left + right) / 2;
	return ListMerge(a, Link, 
					rMergeSort(a, Link, left, mid),
					rMergeSort(a, Link, mid + 1, right));
}

// Combine two sorted lists
template <class T>
int ListMerge(T *a, int *Link, const int start1, const int start2)
{
	int i1, i2;
	int iResult = 0;
	for (i1 = start1, i2 = start2; i1 && i2; )
		if (a[i1] <= a[i2]) {
			Link[iResult] = i1;
			iResult = i1; i1 = Link[i1];
		} else {
			Link[iResult] = i2;
			iResult = i2; i2 = Link[i2];
		}
	if (i1 == 0) Link[iResult] = i2;
	else Link[iResult] = i1;
	return Link[0];
}

// Heap Sort ---------------------------------------
template <class T>
void HeapSort(T *a, const int n)
{
	for (int i = n/2; i >= 1; i--)	// Buttom-up heapification, Initialization
		Adjust(a, i, n);		// heapify
	
	for (int i = n-1; i >= 1; i--) {
		swap(a[1], a[i+1]);
		Adjust(a, 1, i);
	}
}

template <class T>
void Adjust(T *a, const int root, const int n)
{
	T e = a[root];
	int j;
	for (j = 2*root; j <= n; j *= 2) {
		if (j < n && a[j] < a[j + 1])	j++;
		if (e >= a[j])	break;
		a[j / 2] = a[j];
	}
	a[j / 2] = e;
}

