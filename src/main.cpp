#include <iostream>
#include <algorithm>
#include <iterator>

#include "sorting.h"

using namespace std;

// Driver program to test sorting functions
int main(){
	int arr[] = {64, 25, 12, 22, 11, 37, 543, 345, 190, 142, 191, 54, 123, 43, 234145};
	int n = sizeof(arr)/sizeof(arr[0]);

	int* vec = arr;

	cout << get_max(vec, vec + n) << endl;

	cout << "Unsorted array: \n";
	printArray(vec, vec + n);

	selection(vec, vec + n);

	cout << "Sorted array: \n";
	printArray(vec, vec + n);
    
	return 0;
}
