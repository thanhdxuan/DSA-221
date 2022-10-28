#ifndef SORT_H
#define SORT_H
#include <math.h>
#include <unistd.h>

#include <algorithm>
#include <sstream>
#include <type_traits>
static int compare_part = 0;
static int compare_sort = 0;
template <typename T>
class QuickSort {
  public:
   static void printArray(T *start, T *end) {
      int size = end - start;
      for (int i = 0; i < size - 1; i++)
         std::cout << start[i] << ", ";
      std::cout << start[size - 1];
      std::cout << std::endl;
   }
   static int partition(T *list, int left, int right) {
      if (left >= right) return left;
      int pivot = left;
      int i = left + 1;
      int j = right;
      if (i == j) return pivot;
      while (i < j) {
         while (list[i] < list[pivot]) {
            i++;
         }
         while (list[j] > list[pivot]) {
            j--;
         }
         if (i < j) {
            if (pivot == i)
               pivot = j;
            else if (pivot == j)
               pivot = i;
            std::swap(list[i], list[j]);
            i++;
            j--;
         }
      }
      std::swap(list[j], list[pivot]);
      pivot = j;
      return pivot;
   }

   static void sort(T *list, const int &length, int left = -1, int right = -1) {
      if (length < 2) return;
      if (left == -1) {
         left = 0;
         right = length - 1;
      }
      if (left < right) {
         int pivot = partition(list, left, right);
         sort(list, length, left, pivot - 1);
         sort(list, length, pivot + 1, right);
      }
   }
   // static void recursiveQuickSort(T *list, int left, int right) {
   //   if (left < right) {
   //       int pivot = partition(list, left, right);
   //       recursiveQuickSort(list, left, pivot - 1);
   //       recursiveQuickSort(list, pivot + 1, right);
   //    }
   // }
   // static void sort(T *list, const int &length) {
   //    if (length == 1 || length == 0) return;
   //    recursiveQuickSort(list, 0, length - 1);
   // }
   static T *Partition(T *start, T *end) {
      // TODO: return the pointer which points to the pivot after rearrange the array.
      printf("Before: ");
      printArray(start, end);
      int pivot = 0;
      if (start > end) return start;
      int length = end - start;
      int i = 1, j = length - 1;
      do {
         while (start[i] < start[pivot]) i++;
         while (start[j] > start[pivot]) j--;
         if (i < j) {
            if (pivot == i)
               pivot = j;
            else if (pivot == j)
               pivot = i;
            std::swap(start[i], start[j]);
         }
      } while (i < j);
      std::swap(start[j], start[pivot]);
      printf("Index: %d - value: %d\n", j, start[j]);
      printf("After: ");
      printArray(start, end);
      printf("\n");
      // sleep(2);
      return &start[j];
   }

   static void sort(T *start, T *end) {
      // TODO
      // In this question, you must print out the index of pivot in subarray after everytime calling method Partition.
      if (end - start < 1) return;
      T *pivotPtr = Partition(start, end);
      int pivotIdx = pivotPtr - start;
      // printf(" %d", pivotIdx);
      quickSort(start, pivotPtr);
      quickSort(pivotPtr + 1, end);
   }
};

template <typename T>
class StraightSelectionSort {
  public:
   static void sort(T *list, int length) {
      int current = 0;
      while (current < length - 1) {
         int smallest = current;
         int walker = current + 1;
         while (walker < length) {
            if (list[walker] < list[smallest]) {
               smallest = walker;
            }
            walker++;
         }
         std::swap(list[smallest], list[current]);
         current++;
      }
   }
   static void sort(T *list, int length, int left, int right) {
      int current = left;
      while (current < right) {
         int smallest = current;
         int walker = current + 1;
         while (walker < right + 1) {
            if (list[walker] < list[smallest]) {
               smallest = walker;
            }
            walker++;
         }
         std::swap(list[smallest], list[current]);
         current++;
      }
   }
};

template <typename T>
class StraightInsertionSort {
  public:
   static void sort(T *list, int length) {
      if (length == 1) return;
      int curr = 1;
      while (curr < length) {
         int step = curr - 1;
         T temp = list[curr];
         while (step >= 0 && temp < list[step]) {
            list[step + 1] = list[step];
            step--;
         }
         list[step + 1] = temp;
         curr++;
      }
   }
   static void sort(T *list, int length, int left, int right) {
      if (length == 1 || left >= right) return;
      int curr = left + 1;
      while (curr < right + 1) {
         int step = curr - 1;
         T temp = list[curr];
         while (step >= left && temp < list[step]) {
            list[step + 1] = list[step];
            step--;
         }
         list[step + 1] = temp;
         curr++;
      }
   }
};

template <typename T>
class BubbleSort {
  public:
   static void sort(T *list, int length) {
      int step = 0;
      bool isSwap = true;
      while (step < length && isSwap == true) {
         isSwap = false;
         int curr = length - 1;
         while (curr > step && curr >= 0) {
            if (list[curr] < list[curr - 1]) {
               std::swap(list[curr], list[curr - 1]);
               isSwap = true;
            }
            curr--;
         }
         step++;
      }
   }
   static void sort(T *list, int length, int left, int right) {
      int step = left;
      bool isSwap = true;
      while (step < right + 1 && isSwap == true) {
         int curr = right;
         isSwap = false;
         while (curr > step && curr >= 0) {
            if (list[curr] < list[curr - 1]) {
               std::swap(list[curr], list[curr - 1]);
               isSwap = true;
            }
            curr--;
         }
         step++;
      }
   }
};

template <typename T>
class MergeSort {
  public:
   static int merge(T *list, int left, int mid, int right, int length = -1) {
      if (left >= right) return -1;
      if (length == -1) {
         length = right - left + 1;
      }
      int l = left;
      int r = right;
      T *newList = new T[length];
      int count = left;
      int midP1 = mid + 1;
      while (count < length && left <= mid && midP1 <= right) {
         if (list[left] <= list[midP1]) {
            newList[count] = list[left];
            left++;
         } else {
            newList[count] = list[midP1];
            midP1++;
         }
         count++;
      }
      if (left > mid && midP1 > right) {
         list = newList;
         return 1;
      }
      int temp = (left > mid) ? midP1 : left;
      while (count < length) {
         newList[count] = list[temp];
         temp++;
         count++;
      }
      while (l < r + 1) {
         list[l] = newList[l];
         l++;
      }
      return 1;
   }
   static void recursiveMergeSort(T *list, const int length, int lo, int hi) {
      if (hi > lo) {
         int mid = lo + (hi - lo) / 2;
         recursiveMergeSort(list, length, lo, mid);
         recursiveMergeSort(list, length, mid + 1, hi);
         merge(list, lo, mid, hi, length);
      }
   }
   static void sort(T *list, int length) {
      int lo = 0;
      int hi = length - 1;
      recursiveMergeSort(list, length, lo, hi);
   }
};

template <typename T>
class ShellSort {
  public:
   int *increments;
   int length;

  public:
   ShellSort(int *incres, int l) : increments(incres), length(l) {}
   static void sortSegment(T *list, int &length, int &increment, int segment = 0) {
      int curr = segment + increment;
      while (curr < length - 1) {
         T temp = list[curr];
         int step = curr - increment;
         while (step >= 0 && temp < list[step]) {
            list[step + increment] = list[step];
            step = step - increment;
         }
         list[step + increment] = temp;
         curr = curr + increment;
      }
   }
   void sort(T *list, int &length) {
      for (int i = 0; i < this->length; i++) {
         for (int j = 0; j < increments[i]; j++) {
            sortSegment(list, length, increments[i], j);
         }
      }
   }
};

// NOTE: Sorting in lab
template <class T>
class Sorting {
  private:
   static void printArray(T *start, T *end) { /* end point to element after last */
      int size = end - start;
      for (int i = 0; i < size - 1; i++)
         std::cout << start[i] << ", ";
      std::cout << start[size - 1];
      std::cout << std::endl;
   }

  private:
   static T *Partition(T *start, T *end);

  public:
   static void QuickSort(T *start, T *end);
   static void selectionSort(T *start, T *end) {
      T *current = start;
      while (current != end - 1) {
         T *smallest = current;
         T *walker = current + 1;
         while (walker != end) {
            if (*walker < *smallest) {
               smallest = walker;
            }
            walker++;
         }
         std::swap(*smallest, *current);
         printArray(start, end);
         current++;
      }
   }
   static void sortSegment(T *start, T *end, int segment_idx, int increment) {
      // TODO
      int curr = segment_idx + increment;
      int length = end - start;
      while (curr < length) {
         T temp = start[curr];
         int step = curr - increment;
         while (step >= 0 && temp < start[step]) {
            start[step + increment] = start[step];
            step = step - increment;
         }
         start[step + increment] = temp;
         curr = curr + increment;
      }
   }

   static void ShellSort(T *start, T *end, int *num_segment_list, int num_phases) {
      // TODO
      // Note: You must print out the array after sorting segments to check whether your algorithm is true.
      int length = end - start;
      for (int i = num_phases - 1; i >= 0; i--) {
         for (int j = 0; j < num_segment_list[i]; j++) {
            sortSegment(start, end, j, num_segment_list[i]);
         }
         printf("%d segments: ", num_segment_list[i]);
         printArray(start, end);
      }
   }
   static void merge(T *left, T *middle, T *right) {
      /*TODO*/
      if (left >=  right) return;
      T *result = new T[right - left + 1];
      T *lP = left;
      T *rP = middle + 1;
      printf("left: %d, middle: %d, right: %d\n", *left, *middle, *right);
      Sorting::printArray(left, right + 1);
      int i = 0;
      while (lP < middle + 1 && rP <= right) {
         if (*lP < *rP) { 
            result[i] = *lP;
            lP++;
         }
         else {
            result[i] = *rP;
            rP++;
         }
         i++;
      }
      while (lP < middle + 1) {
         result[i] = *lP;
         lP++;
         i++;
      }
      while (rP <= right) {
         result[i] = *rP;
         rP++;
         i++;
      }
      for (int j = 0; j < right - left + 1; j++) left[j] = result[j];
      Sorting::printArray(left, right + 1);
      printf("\n");
      delete[] result;
   }
   static void mergeSort(T *start, T *end) { /* end point to last element */
      /*TODO*/
      if (start >= end) return;
      T* middle = start + (end - start) / 2;
      mergeSort(start, middle);
      mergeSort(middle + 1, end);
      merge(start, middle, end);
   }
};


#endif /* SORT_H */

/* 0, 2, 4, 3, 1, 4 */