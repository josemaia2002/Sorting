#ifndef SORTING_H
#define SORTING_H

#include <iostream>
#include <algorithm>
#include <iterator>

using namespace std;

template <typename T> 
void printArray(T *first, T *last){
    int i;
    int n = distance(first, last); 
    for(i = 0; i < n; i++){
        cout << *(first+i) << " ";
        cout << endl;
    }
}

template <typename T> 
void selection(T *first, T *last) { 
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

template <typename T> 
void bubble(T *first, T *last){
    int n = distance(first, last);
    for(int i = 0; i < n - 1; i++){
        for(int j = 0; j < n - i - 1; j++){
            if(*(first+j) > *(first+(j+1)))
                iter_swap(first+j, first+(j+1));
        }
    }
} 

template <typename T> 
int* partition(T *first, T *last, T *pivot)
{
  auto slow = first;
  auto fast = first;
  while (fast < pivot) {
    if (*fast < *pivot) {
      std::iter_swap(slow, fast); 
      slow++;
    }
    fast++;
  }
  std::iter_swap(pivot, slow);
  return slow;
}

template <typename T> 
void quicksort(T *first, T *last)
{  
  if (std::distance(first, last) >= 2) {
    auto* q = partition(first, last, last - 1);
    quicksort(first, q);
    quicksort(q + 1, last);
  }
}

int get_max(int *first, int *last);
void radixsort(int *first, int *last);
void shell(int *first, int *last);
void insertion(int *first, int *last);
void merge(int* first, int* last);
void quicksort(int* first, int* last);

#endif





