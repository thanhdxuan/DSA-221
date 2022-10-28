#include <iostream>
#include <list>

#include "SortAlgorithms.h"
// #include "DLinkedList.cpp"
#include <math.h>

#include "BinarySearchTree.h"
#include "BinaryTree.h"
#include "DataLog.h"
#include "SLinkedList.h"
using namespace std;

int main() {
   int arr1[] = {9, 3, 8, 2, 1, 6, 7, 4, 5};
   int n = sizeof(arr1) / sizeof(arr1[0]);
   SLinkedList<int>* l1 = new SLinkedList<int>(arr1, n);
   l1->printList();
   l1->bubbleSort();
   l1->printList();
   return 0;
}
/* 9
2     10
  8       11

2 8 9 10 11
 */