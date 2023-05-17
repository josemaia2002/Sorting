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
void countSort(int *first, int *last, int place);
void radixsort(int *first, int *last);

#endif