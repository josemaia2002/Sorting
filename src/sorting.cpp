#include <iostream>
#include <string>
#include "sorting.h"

using namespace std;

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