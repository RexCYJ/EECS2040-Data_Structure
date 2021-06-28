#include "Sorting.cpp"
#include <iostream>
#include <iomanip>
#include <string>
#include <random>

#define SIZE 20

using namespace std;

ostream& operator<<(ostream& os, int *a);
ostream& operator<<(ostream& os, float *a);
ostream& operator<<(ostream& os, char *a);
ostream& operator<<(ostream& os, string *a);

int main(void)
{
	mt19937 gen(time(NULL));		// to seed a mersenne twister
	uniform_int_distribution<> dist_int(1, 9999);	// uniformly distributed over (x, y)
	int list_int[SIZE + 1], sorted_int[SIZE + 1];
	for (int i = 0; i <= SIZE; i++) list_int[i] = dist_int(gen);	

	cout << left << setw(24) << "Random Integer:" << list_int << endl;	
	copy(list_int, list_int + SIZE + 1, sorted_int);
	InsertionSort(sorted_int, SIZE);
	cout << left << setw(24) << "Insertion Sort:" << sorted_int << endl;
	copy(list_int, list_int + SIZE + 1, sorted_int);
	QuickSort(sorted_int, 1, SIZE);
	cout << left << setw(24) << "Quick Sort:" << sorted_int << endl;
	copy(list_int, list_int + SIZE + 1, sorted_int);
	MergeSort_iter(sorted_int, SIZE);
	cout << left << setw(24) << "Iterative Merge Sort:" << sorted_int << endl;
	copy(list_int, list_int + SIZE + 1, sorted_int);
	MergeSort_rec(sorted_int, SIZE);
	cout << left << setw(24) << "Recursive Merge Sort:" << sorted_int << endl;
	copy(list_int, list_int + SIZE + 1, sorted_int);
	HeapSort(sorted_int, SIZE);
	cout << left << setw(24) << "Heap Sort:" << sorted_int << endl << endl;

	uniform_real_distribution<float> dist_float(0, 1);	// uniformly distributed over (0, 1)
	float list_float[SIZE + 1], sorted_float[SIZE + 1];
	for (int i = 0; i <= SIZE; i++) list_float[i] = dist_float(gen);	
	cout << left << "Random Floats:\n  " << list_float << endl;	
	copy(list_float, list_float + SIZE + 1, sorted_float);
	InsertionSort(sorted_float, SIZE);
	cout << left << "Insertion Sort:\n  " << sorted_float << endl;
	copy(list_float, list_float + SIZE + 1, sorted_float);
	QuickSort(sorted_float, 1, SIZE);
	cout << left << "Quick Sort:\n  " << sorted_float << endl;
	copy(list_float, list_float + SIZE + 1, sorted_float);
	MergeSort_iter(sorted_float, SIZE);
	cout << left << "Iterative Merge Sort:\n  " << sorted_float << endl;
	copy(list_float, list_float + SIZE + 1, sorted_float);
	MergeSort_rec(sorted_float, SIZE);
	cout << left << "Recursive Merge Sort:\n  " << sorted_float << endl;
	copy(list_float, list_float + SIZE + 1, sorted_float);
	HeapSort(sorted_float, SIZE);
	cout << left << "Heap Sort:\n  " << sorted_float << endl << endl;

	uniform_int_distribution<> dist_char(32, 127);	// uniformly distributed over (x, y)
	char list_char[SIZE + 1], sorted_char[SIZE + 1];
	for (int i = 0; i <= SIZE; i++) list_char[i] = dist_char(gen);	
	cout << left << "Random Chars:\n  " << list_char << endl;	
	copy(list_char, list_char + SIZE + 1, sorted_char);
	InsertionSort(sorted_char, SIZE);
	cout << left << "Insertion Sort:\n  " << sorted_char << endl;
	copy(list_char, list_char + SIZE + 1, sorted_char);
	QuickSort(sorted_char, 1, SIZE);
	cout << left << "Quick Sort:\n  " << sorted_char << endl;
	copy(list_char, list_char + SIZE + 1, sorted_char);
	MergeSort_iter(sorted_char, SIZE);
	cout << left << "Iterative Merge Sort:\n  " << sorted_char << endl;
	copy(list_char, list_char + SIZE + 1, sorted_char);
	MergeSort_rec(sorted_char, SIZE);
	cout << left << "Recursive Merge Sort:\n  " << sorted_char << endl;
	copy(list_char, list_char + SIZE + 1, sorted_char);
	HeapSort(sorted_char, SIZE);
	cout << left << "Heap Sort:\n  " << sorted_char << endl << endl;


	uniform_int_distribution<> dist_letter(65, 90);	// uniformly distributed over (x, y)
	string list_string[SIZE + 1], sorted_string[SIZE + 1];
	char word[10];
	for (int i = 1; i <= SIZE; i++) {
		for (int j = 0; j < 6; j++) 
			word[j] = (char)dist_letter(gen);
		word[6] = '\0';
		list_string[i] = word;
	}
	cout << left << "Random Strings:\n  " << list_string << endl;	
	copy(list_string, list_string + SIZE + 1, sorted_string);
	InsertionSort(sorted_string, SIZE);
	cout << left << "Insertion Sort:\n  " << sorted_string << endl;
	copy(list_string, list_string + SIZE + 1, sorted_string);
	QuickSort(sorted_string, 1, SIZE);
	cout << left << "Quick Sort:\n  " << sorted_string << endl;
	copy(list_string, list_string + SIZE + 1, sorted_string);
	MergeSort_iter(sorted_string, SIZE);
	cout << left << "Iterative Merge Sort:\n  " << sorted_string << endl;
	copy(list_string, list_string + SIZE + 1, sorted_string);
	MergeSort_rec(sorted_string, SIZE);
	cout << left << "Recursive Merge Sort:\n  " << sorted_string << endl;
	copy(list_string, list_string + SIZE + 1, sorted_string);
	HeapSort(sorted_string, SIZE);
	cout << left << "Heap Sort:\n  " << sorted_string << endl;

	return 0;
}

ostream& operator<<(ostream& os, int *a)
{
	for (int i = 1; i <= SIZE; i++)
		os << right << setw(5) << a[i] << ' ';
	return os;
}

ostream& operator<<(ostream& os, float *a)
{
	for (int i = 1; i <= SIZE; i++)
		os << right << fixed << setprecision(3) << setw(5) << a[i] << ' ';
	return os;
}

ostream& operator<<(ostream& os, char *a)
{
	for (int i = 1; i <= SIZE; i++)
		os << a[i] << ' ';
	return os;
}

ostream& operator<<(ostream& os, string *a)
{
	for (int i = 1; i <= SIZE; i++)
		os << a[i] << ' ';
	return os;
}