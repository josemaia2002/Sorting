#ifndef SORTING_H
#define SORTING_H

#include <iostream>
#include <algorithm>
#include <iterator>

using namespace std;

/**
 * \brief Prints the elements of an array.
 * 
 * This function prints the elements of an array
 * specified by the range defined by the pointers
 * 'first' and 'last'. The elements are printed
 * in the order they appear in the array.
 * 
 * \tparam T The type of elements in the array.
 * \param first Pointer to the first element in the array.
 * \param last Pointer to the last element in the array (exclusive).
 */
template <typename T> 
void printArray(T *first, T *last){
    int i;
    int n = distance(first, last); 
    for(i = 0; i < n; i++){
        cout << *(first+i) << " ";
        cout << endl;
    }
}

/**
 * \brief Sorts the elements of an array in ascending order using the selection sort algorithm.
 * 
 * This function sorts the elements of an array specified by the range defined by the pointers
 * 'first' and 'last' in ascending order. The elements are sorted in-place, meaning the original
 * array will be modified.
 * 
 * \tparam T The type of elements in the array.
 * \param first Pointer to the first element in the array.
 * \param last Pointer to the last element in the array (exclusive).
 */
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

/**
 * \brief Sorts the elements of an array in ascending order using the bubble sort algorithm.
 * 
 * This function sorts the elements of an array specified by the range defined by the pointers
 * 'first' and 'last' in ascending order. The elements are sorted in-place, meaning the original
 * array will be modified.
 * 
 * \tparam T The type of elements in the array.
 * \param first Pointer to the first element in the array.
 * \param last Pointer to the last element in the array (exclusive).
 */
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

/**
 * \brief Partitions the elements of an array based on a pivot value.
 * 
 * This function partitions the elements of an array specified by the range defined by the pointers
 * 'first' and 'last' based on a pivot value. The elements smaller than the pivot are moved to the
 * left side of the pivot, and the elements greater than or equal to the pivot are moved to the right side.
 * The pivot element itself is also moved to its final sorted position. The function returns a pointer
 t o the pivot element's final position in the array.

 * \tparam T The type of elements in the array.
 * \param first Pointer to the first element in the array.
 * \param last Pointer to the last element in the array (exclusive).
 * \param pivot Pointer to the pivot element.
 * 
 * \return A pointer to the pivot element's final position in the array.
 */
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

/**
 * \brief Sorts the elements of an array in ascending order using the quicksort algorithm.
 * 
 * This function sorts the elements of an array specified by the range defined by the pointers
 * 'first' and 'last' in ascending order. The elements are sorted in-place, meaning the original
 * array will be modified. The quicksort algorithm is used for sorting.
 * 
 * \tparam T The type of elements in the array.
 * \param first Pointer to the first element in the array.
 * \param last Pointer to the last element in the array (exclusive).
 */
template <typename T> 
void quicksort(T *first, T *last)
{  
  if (std::distance(first, last) >= 2) {
    auto* q = partition(first, last, last - 1);
    quicksort(first, q);
    quicksort(q + 1, last);
  }
}

/**
 * \brief Merges two sorted arrays into a single sorted array.
 * 
 * This function merges two sorted arrays specified by the ranges defined by the pointers
 * 'l_first' and 'l_last' (representing the left array) and 'r_first' and 'r_last' (representing the right array)
 * into a single sorted array specified by the range defined by the pointer 'a_first' (representing the output array).
 * The merged array is sorted in ascending order. The function assumes that both input arrays are already sorted.
 * 
 * \tparam T The type of elements in the arrays.
 * \param l_first Pointer to the first element in the left array.
 * \param l_last Pointer to the last element in the left array (exclusive).
 * \param r_first Pointer to the first element in the right array.
 * \param r_last Pointer to the last element in the right array (exclusive).
 * \param a_first Pointer to the first element in the output array.
 */
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

/**
 * \brief Sorts the elements of an array in ascending order using the merge sort algorithm.
 * 
 * This function sorts the elements of an array specified by the range defined by the pointers
 * 'first' and 'last' in ascending order. The elements are sorted in-place, meaning the original
 * array will be modified. The merge sort algorithm is used for sorting.
 * 
 * \tparam T The type of elements in the array.
 * \param first Pointer to the first element in the array.
 * \param last Pointer to the last element in the array (exclusive).
 */
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

/**
 * \brief Sorts the elements of an array in ascending order using the insertion sort algorithm.
 * 
 * This function sorts the elements of an array specified by the range defined by the pointers
 * 'first' and 'last' in ascending order. The elements are sorted in-place, meaning the original
 * array will be modified. The insertion sort algorithm is used for sorting.
 * 
 * \tparam T The type of elements in the array.
 * \param first Pointer to the first element in the array.
 * \param last Pointer to the last element in the array (exclusive).
*/
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

/**
 * \brief Sorts the elements of an array in ascending order using the shell sort algorithm.
 * 
 * This function sorts the elements of an array specified by the range defined by the pointers
 * 'first' and 'last' in ascending order. The elements are sorted in-place, meaning the original
 * array will be modified. The shell sort algorithm is used for sorting.
 * 
 * \tparam T The type of elements in the array.
 * \param first Pointer to the first element in the array.
 * \param last Pointer to the last element in the array (exclusive).
 */
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

/**
 * \brief Finds the maximum element in an array.
 * 
 * This function finds the maximum element in an array specified by the range defined by the pointers
 * 'first' and 'last'. The maximum element is determined based on the comparison using the '<' operator.
 * 
 * \tparam T The type of elements in the array.
 * \param first Pointer to the first element in the array.
 * \param last Pointer to the last element in the array (exclusive).
 * 
 * \return The maximum element in the array.
 */
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

/**
 * \brief Sorts the elements of an array in ascending order using the counting sort algorithm.
 * 
 * This function sorts the elements of an array specified by the range defined by the pointers
 * 'first' and 'last' in ascending order. The elements are sorted in-place, meaning the original
 * array will be modified. The counting sort algorithm is used for sorting.
 * 
 * \tparam T The type of elements in the array.
 * \param first Pointer to the first element in the array.
 * \param last Pointer to the last element in the array (exclusive).
 * \param place The place value used for sorting (e.g., ones, tens, hundreds place).
 */
template <typename T> 
void countSort(T *first, T *last, T place) {
    const int max = 100000;
    T output[max];
    T count[max];

    int n = distance(first, last);

    for(int i = 0; i < max; i++)
        count[i] = 0;

    for(int i = 0; i < n; i++) 
        count[(*(first+i) / place) % 10]++;


    for(int i = 1; i < max; i++) 
        count[i] += count[i - 1];

    for(int i = n - 1; i >= 0; i--) {
        output[count[(*(first+i) / place) % 10] - 1] = *(first+i);
        count[(*(first+i) / place) % 10]--;
    }

    for(int i = 0; i < n; i++)
        *(first+i) = output[i];
}

/**
 * \brief Sorts the elements of an array in ascending order using the radix sort algorithm.
 * 
 * This function sorts the elements of an array specified by the range defined by the pointers
 * 'first' and 'last' in ascending order. The elements are sorted in-place, meaning the original
 * array will be modified. The radix sort algorithm is used for sorting.
 * 
 * \tparam T The type of elements in the array.
 * \param first Pointer to the first element in the array.
 * \param last Pointer to the last element in the array (exclusive).
 */
template <typename T> 
void radixsort(T *first, T *last) {
  T max = get_max<int>(first, last);

  for(int place = 1; max / place > 0; place *= 10)
    countSort<int>(first, last, place);
}

#endif