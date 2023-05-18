#ifndef SORTING_H
#define SORTING_H

#include <iostream>
#include <algorithm>
#include <iterator>

using namespace std;

void printArray(int *first, int *last);
void selection(int *first, int *last);
void bubble(int *first, int *last);
int get_max(int *first, int *last);
void radixsort(int *first, int *last);
void shell(int *first, int *last);
void insertion(int *first, int *last);
void merge(int* first, int* last);
void quicksort(int* first, int* last);

#endif