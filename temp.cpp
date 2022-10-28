#include <bits/stdc++.h>

#include <iostream>

using namespace std;

struct ListNode {
   int val;
   ListNode* next;
   ListNode(int _val = 0, ListNode* _next = nullptr) : val(_val), next(_next) {}
};

ListNode* mergeLists(ListNode* a, ListNode* b) {
   return nullptr;
}

// Sort and unsorted list given its head pointer
ListNode* mergeSortList(ListNode* head) {
   return nullptr;
}

int main() {
   int arr1[] = {1, 3, 5, 7, 9};
   int arr2[] = {2, 4, 6, 8};
   unordered_map<ListNode*, int> nodeAddr;
   ListNode* a = init(arr1, sizeof(arr1) / 4, nodeAddr);
   ListNode* b = init(arr2, sizeof(arr2) / 4, nodeAddr);
   ListNode* merged = mergeLists(a, b);
   try {
      printList(merged, nodeAddr);
   } catch (char const* err) {
      cout << err << '\n';
   }
   freeMem(merged);
}