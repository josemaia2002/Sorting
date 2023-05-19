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

template <typename T> 
void merge_aux(T* l_first, T* l_last, T* r_first, T* r_last, T* a_first)
{
    while (l_first != l_last) {
        if (r_first == r_last) {
            std::copy(l_first, l_last, a_first);
            return;
        }
        *a_first++ = (*l_first < *r_first) ? *l_first++ : *r_first++;
    }
    std::copy(r_first, r_last, a_first);
}

template <typename T> 
void merge(T *first, T *last)
{
    auto len = std::distance(first, last);
    if (len >= 2) {
        auto* m = first + len / 2;
        merge(first, m);
        merge(m, last);

        T* temp = new T[len];
        merge_aux(first, m, m, last, temp);
        std::copy(temp, temp + len, first);
        delete[] temp;
    }
}

template <typename T> 
void insertion(T *first, T *last) {
  if (first == last)
    return;
  
  for (int *fast = first + 1; fast != last; ++fast) {
    int val = *fast;
    int *runner = fast;
    while (runner != first && val < *(runner - 1)) {
      *runner = *(runner - 1);
      --runner;
    }
    *runner = val;
  }
}

template <typename T> 
void shell(T *first, T *last) {
  int tamanho = last - first;
  // Comece com um gap grande e, em seguida, reduz o gap até que ele se torne 1
  for (int gap = tamanho / 2; gap > 0; gap /= 2) {
    // Realize a ordenação por inserção em cada sublista definida pelo gap
    for (int i = gap; i < tamanho; i++) {
      int temp = first[i];
      int j;
      for (j = i; j >= gap && temp < first[j - gap]; j -= gap) {
        first[j] = first[j - gap];
      }
      first[j] = temp;
    }
  }
}

template <typename T> 
T get_max(T *first, T *last){
    T maior = 0;
    int n = distance(first, last); 
    for(int i = 0; i < n; i++){
        if(*(first+i) > maior){
            maior = *(first+i);
        }
    }
    return maior;
}

template <typename T> 
void countSort(T *first, T *last, T place) {
    const int max = 10;
    T output[max];
    T count[max];

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

template <typename T> 
void radixsort(T *first, T *last) {
  T max = get_max(first, last);

  // Apply counting sort to sort elements based on place value.
  for(int place = 1; max / place > 0; place *= 10)
    countSort(first, last, place);
}

#endif