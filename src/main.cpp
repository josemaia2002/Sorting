#include <iostream>
#include <algorithm>
#include <iterator>
#include <chrono>
#include <ctime>
#include <functional>
#include <cmath>

#include "sorting.h"

void desordem_condicionada(int * first, int * last, double porcentagem){
    //deixa arranjos com 75%, 50% ou 25% de seus elementos em sua posição definitiva
    int n = last- first;
    int I[n];
    int p= std::ceil(n*(1-porcentagem));
    for(int i=0; i< n; i++){
      I[i]=i;
    }
    std::random_shuffle(I, I+n);
    for(int i=0; i<p; i+=2){
      std::iter_swap(first+I[i], first+I[i+1]);
    }
  }

void timing(int * first, int * last){
    std::chrono::time_point<std::chrono::system_clock> start, end;

    start = std::chrono::system_clock::now();
    insertion(first, last);
    end = std::chrono::system_clock::now();

    std::chrono::duration<double> elapsed_seconds = end - start;
    std::time_t end_time = std::chrono::system_clock::to_time_t(end);

    std::cout << "finished computation at " << std::ctime(&end_time)
            << "elapsed time: " << elapsed_seconds.count() << "s\n";
}

// Driver program to test sorting functions
int main(){
	int sz = 100000;    // Generate an array with 100000 elements
    int arr[sz];
    srand(time(NULL));

    // Fill the array
    for(int i = 0; i < sz; i++)
        arr[i] = rand()%100;  // Generate number between 0 to 900

    int n = sizeof(arr)/sizeof(arr[0]);
    int* vec = arr;

    std::cout << "25 array " << "s\n";
    desordem_condicionada(vec, vec + n, 0.25);
    timing(vec, vec + n);

    std::cout << "50 array " << "s\n";
    desordem_condicionada(vec, vec + n, 0.50);
    timing(vec, vec + n);

    std::cout << "75 array " << "s\n";
    desordem_condicionada(vec, vec + n, 0.75);
    timing(vec, vec + n);

/*
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

*/
  
	return 0;
}
