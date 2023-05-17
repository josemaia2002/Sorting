#include <iostream>
#include <algorithm>
#include <iterator>

using namespace std;

void printArray(int *first, int *last){
	int i;
	int n = distance(first, last); 
	for(i = 0; i < n; i++){
		cout << *(first+i) << " ";
		cout << endl;
	}
}

void selection(int *first, int *last) {	
    int min_idx;
    int n = distance(first, last);       

    for(int i = 0; i < n-1; i++){
        min_idx = i;
        for(int j = i + 1; j < n; j++){
            if(*(first+j) < *(first+min_idx))
                min_idx = j;
        }
        if(min_idx != i)
            iter_swap(first+min_idx, first+i);
    }
}

void bubble(int *first, int *last){
    int n = distance(first, last);
    for(int i = 0; i < n - 1; i++){
        for(int j = 0; j < n; j++){
            if(*(first+j) > *(first+(j+1)))
                iter_swap(first+j, first+(j+1));
        }
    }
}  

int get_max(int *first, int *last){
    int maior = 0;
    int n = distance(first, last); 
    for(int i = 0; i < n; i++){
        if(*(first+i) > maior){
            maior = *(first+i);
        }
    }
    return maior;
}

void countSort(int *first, int *last, int place) {
    const int max = 10;
    int output[max];
    int count[max];

    int n = distance(first, last);

    // Initialize count array with all zeros.
    for(int i = 0; i < max; i++)
        count[i] = 0;

    // This function increments the element of the count array 
    // whose index is equal to the i-th element of the original array
    // e.g.: arr[0] == 4 count[4]++
    for(int i = 0; i < n; i++) 
        count[(*(first+i) / place) % 10]++;


    // Cumulative sum
    for(int i = 1; i < max; i++) 
        count[i] += count[i - 1];

    for(int i = n - 1; i >= 0; i--) {
        output[count[(*(first+i) / place) % 10] - 1] = *(first+i);
        count[(*(first+i) / place) % 10]--;
    }

    for(int i = 0; i < n; i++)
        *(first+i) = output[i];
}

void radixsort(int *first, int *last) {
  int max = get_max(first, last);

  // Apply counting sort to sort elements based on place value.
  for(int place = 1; max / place > 0; place *= 10)
    countSort(first, last, place);
}


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
