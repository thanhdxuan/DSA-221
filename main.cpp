#include <iostream>
#include <list>

#include "SortAlgorithms.h"
// #include "DLinkedList.cpp"
#include <bits/stdc++.h>
#include <math.h>
#include <time.h>
#include <tree_sitter/parser.h>

#include "BinarySearchTree.h"
#include "BinaryTree.h"
#include "DataLog.h"
#include "SLinkedList.h"

#include "AVLTree.h"
using namespace std;

void print(const vector<int> &vector) {
   for (auto i : vector) {
      cout << i << " ";
   }
}
int main() {
   BinarySearchTree<int> BST;
   int arr[] = {41, 20, 65, 11, 29, 50, 91, 32, 72, 99};
   int n = sizeof(arr) / sizeof (arr[0]);
   for (int i = 0; i < n; i++) {
      BST.add(arr[i]);
   }
   vector<int> res = BST.levelAlterTraverse();
   print(res);
   return 0;
}

/*
    3
5       2
  9   1    4
           5  1

3 + 5 + 19 = 27
3 + 2 + 1 = 6
3 + 2 + 4 + 15 = 24
3 + 2 + 4 + 10 = 19


8 + 6 + 9 = 23
8
3 6 3 = 12 (-3)

*/