#include <iostream>
#include <fstream>
#include <algorithm>
#include <iterator>
#include <chrono>
#include <ctime>
#include <functional>
#include <cmath>
#include <string>

#include "sorting.h"

enum organization {
    all_random = 0,
    quarter = 25,
    half = 50,
    three_quarter = 75,
    non_descending = 100,
    non_ascending = 125
} list_sample;

/**
 * \brief Applies conditioned disorder to an array.
 *  
 * This function applies conditioned disorder to the elements of an array specified by the range
 * defined by the pointers 'first' and 'last'. The conditioned disorder is applied by swapping pairs
 * of elements in the array. The number of pairs to be swapped is determined by the 'porcent' parameter.
 * 
 * \param first Pointer to the first element in the array.
 * \param last Pointer to the last element in the array (exclusive).
 * \param porcent The percentage of pairs to be swapped. If the value is 125, it will be adjusted to 100.
 */
void conditioned_disorder(int * first, int * last, int porcent){
    if(porcent == 125)
        porcent = 100;

    int n = last- first;
    int I[n];
    int p= std::ceil(n*((100-porcent)/100));
    for(int i=0; i< n; i++){
        I[i]=i;
    }
    std::random_shuffle(I, I+n);
    for(int i=0; i<p; i+=2){
        std::iter_swap(first+I[i], first+I[i+1]);
    }
}

/**
 * \brief Measures the execution time of a function on an array and writes it to a file.
 * 
 * This function measures the execution time of a given function 'func' applied 
 * to the elements of an array
 * specified by the range defined by the pointers 'first' and 'last'. The execution 
 * time is measured using
 * the std::chrono library. The measured time is written to the provided ofstream 'arquivo'.
 * 
 * \param first Pointer to the first element in the array.
 * \param last Pointer to the last element in the array (exclusive).
 * \param func Pointer to the function to be timed.
 * \param arquivo The ofstream to which the execution time will be written.
 */
void timing(int * first, int * last, void (*func)(int*, int*), ofstream& arquivo){    
    std::chrono::time_point<std::chrono::system_clock> start, end;

    start = std::chrono::system_clock::now();
    func(first, last);
    end = std::chrono::system_clock::now();

    std::chrono::duration<double> elapsed_seconds = end - start;
    std::time_t end_time = std::chrono::system_clock::to_time_t(end);

    arquivo << elapsed_seconds.count() << "\n";

    arquivo.close();
}


// Driver program to test sorting functions
int main(){   
    std::ofstream arquivo;

    std::string paths[7] = {"../data/selection_data.txt", "../data/bubble_data.txt", "../data/quicksort_data.txt", "../data/merge_data.txt", "../data/insertion_data.txt", "../data/shell_data.txt", "../data/radix_data.txt"};
    
	int sz = 100000;    // Generate an array with 100000 elements
    int arr[sz];

    // Fill the array
    for(int i = 0; i < sz; i++){
        arr[i] = sz - i;
    }

    int n = sizeof(arr)/sizeof(arr[0]);
    int* vec = arr;

    void (*functptr[])(int*, int*) = {selection<int>, bubble<int>, quicksort<int>, merge<int>, insertion<int>, shell<int>, radixsort<int>};
    std::string func_names[7] = { "selection", "bubble", "quicksort", "merge", "insertion", "shell", "radixsort"};

    for(int i = 0; i < 7 ; i++){
        for(int sample = non_ascending; sample >= all_random; sample -= quarter){
            for(int j = 100; j < 100000; j+=4000){
                arquivo.open(paths[i], ios::app);
                conditioned_disorder(vec, vec + j, sample);
                arquivo << j << " ";
                timing(vec, vec + j, (functptr[i]), arquivo);
                arquivo.close();
            }
            arquivo.open(paths[i], ios::app);
            arquivo << "\n";
            arquivo.close();
        }
    }

	return 0;
}