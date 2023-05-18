#include <iostream>
#include <algorithm>
#include <iterator>
#include <chrono>
#include <ctime>

#include "sorting.h"

using namespace std;

// Driver program to test sorting functions
int main(){
	int sz = 32000;    // Generate an array with 16000 elements
    int arr[sz];
    srand(time(NULL));

    // Fill the array
    for(int i = 0; i < sz; i++)
        arr[i] = rand()%900;  // Generate number between 0 to 900

    int n = sizeof(arr)/sizeof(arr[0]);
    int* vec = arr;

    // cout << "Unsorted array: \n";
    // printArray(vec, vec + n);

    std::chrono::time_point<std::chrono::system_clock> start, end;

    start = std::chrono::system_clock::now();
    shell(vec, vec + n);
    end = std::chrono::system_clock::now();

    std::chrono::duration<double> elapsed_seconds = end - start;
    std::time_t end_time = std::chrono::system_clock::to_time_t(end);

    // cout << "Sorted array: \n";
    // printArray(vec, vec + n); 

    std::cout << "finished computation at " << std::ctime(&end_time)
            << "elapsed time: " << elapsed_seconds.count() << "s\n";

	return 0;
}
