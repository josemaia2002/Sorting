#include <iostream>
#include <fstream>
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

void timing(int * first, int * last, void (*func)(int*, int*)){    
    std::chrono::time_point<std::chrono::system_clock> start, end;

    start = std::chrono::system_clock::now();
    func(first, last);
    end = std::chrono::system_clock::now();

    std::chrono::duration<double> elapsed_seconds = end - start;
    std::time_t end_time = std::chrono::system_clock::to_time_t(end);

    std::fstream arquivo("../data/log_data.txt", ios::app);

    arquivo << "finished computation at " << std::ctime(&end_time)
            << "elapsed time: " << elapsed_seconds.count() << "s\n";

    arquivo.close();
}

// Driver program to test sorting functions
int main(){   
    std::fstream arquivo("../data/log_data.txt", ios::app);
	int sz = 10;    // Generate an array with 100000 elements
    int arr[sz];
    srand(time(NULL));

    // Fill the array
    for(int i = 0; i < sz; i++)
        arr[i] = rand()%100;  // Generate number between 0 to 900

    int n = sizeof(arr)/sizeof(arr[0]);
    int* vec = arr;

    void (*functptr[])(int*, int*) = {selection<int>, bubble<int>, quicksort<int>, merge<int>, insertion<int>, shell<int>, radixsort<int>};

    double percent;
    for(int i = 0; i < 7; i++){
        for(percent = 0.25; percent <= 0.75; percent+=0.25){
            arquivo << percent << " array " << "s\n";
            desordem_condicionada(vec, vec + n, percent);
            timing(vec, vec + n, (functptr[i]));
        }
        arquivo << "=================================================================\n";
    }
    arquivo.close();

	return 0;
}