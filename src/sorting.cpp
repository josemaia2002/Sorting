#include <iostream>
#include <string>
#include "sorting.h"

using namespace std;

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

void shell(int *first, int *last) {
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

int *insert_in_sorted(int *first, int *last, const int &val) {
  int *runner = last;
  while (runner != first && val < *(runner - 1)) {
    *runner = *(runner - 1);
    --runner;
  }
  *runner = val;
  return last + 1;
}

void insertion(int *first, int *last) {
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

void merge_aux(int* l_first, int* l_last, int* r_first, int* r_last, int* a_first)
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

void merge(int* first, int* last)
{
    auto len = std::distance(first, last);
    if (len >= 2) {
        auto* m = first + len / 2;
        merge(first, m);
        merge(m, last);

        int* temp = new int[len];
        merge_aux(first, m, m, last, temp);
        std::copy(temp, temp + len, first);
        delete[] temp;
    }
}

int* partition(int* first, int* last, int* pivot)
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

void quicksort(int* first, int* last)
{  
  if (std::distance(first, last) >= 2) {
    auto* q = partition(first, last, last - 1);
    quicksort(first, q);
    quicksort(q + 1, last);
  }
}