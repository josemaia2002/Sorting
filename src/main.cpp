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

void desordem_condicionada(int * first, int * last, int porcentagem){
    //deixa arranjos com 75%, 50% ou 25% de seus elementos em sua posição definitiva

    if(porcentagem == 125)
        porcentagem = 100;

    int n = last- first;
    int I[n];
    int p= std::ceil(n*((100-porcentagem)/100));
    for(int i=0; i< n; i++){
      I[i]=i;
    }
    std::random_shuffle(I, I+n);
    for(int i=0; i<p; i+=2){
      std::iter_swap(first+I[i], first+I[i+1]);
    }
  }

void timing(int * first, int * last, void (*func)(int*, int*), ofstream& arquivo){    
    std::chrono::time_point<std::chrono::system_clock> start, end;

    start = std::chrono::system_clock::now();
    func(first, last);
    end = std::chrono::system_clock::now();

    std::chrono::duration<double> elapsed_seconds = end - start;
    std::time_t end_time = std::chrono::system_clock::to_time_t(end);

    arquivo << "finished computation at " << std::ctime(&end_time)
            << "elapsed time: " << elapsed_seconds.count() << "s\n";

    arquivo.close();
}

// Driver program to test sorting functions
int main(){   
    std::ofstream arquivo;
    
	int sz = 100000;    // Generate an array with 100000 elements
    int arr[sz];
    // srand(time(NULL));

    // Fill the array
    for(int i = 0; i < sz; i++){
        // arr[i] = rand()%100;  // Generate number between 0 to 900
        arr[i] = sz - i;
    }

    int n = sizeof(arr)/sizeof(arr[0]);
    int* vec = arr;

    void (*functptr[])(int*, int*) = {selection<int>, bubble<int>, quicksort<int>, merge<int>, insertion<int>, shell<int>, radixsort<int>};
    std::string func_names[7] = { "selection", "bubble", "quicksort", "merge", "insertion", "shell", "radixsort"};

    for(int i = 0; i < 7; i++){
        arquivo.open("../data/log_data.txt", ios::app);
        arquivo << func_names[i] << "\n";
        arquivo.close();

        for(int j = 10; j < 100; j+=10){
            for(int sample = non_ascending; sample >= all_random; sample -= quarter){
                arquivo.open("../data/log_data.txt", ios::app);
                arquivo << sample << " array " << "s\n";
                desordem_condicionada(vec, vec + j, sample);
                timing(vec, vec + j, (functptr[i]), arquivo);
                arquivo.close();
            }
        }
        arquivo.open("../data/log_data.txt", ios::app);
        arquivo << "\n=================================\n\n\n";
        arquivo.close();
    }

	return 0;
}