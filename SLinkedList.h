#include <iostream>
#include <sstream>
using namespace std;

template <class T>
class SLinkedList {
  public:
   class ListNode;  // Forward declaration
  protected:
   ListNode* head;
   ListNode* tail;
   int count;

  public:
   SLinkedList() {
      this->head = nullptr;
      this->tail = nullptr;
      this->count = 0;
   }
   SLinkedList(T* arr, int length) {
      for (int i = 0; i < length; i++) {
         this->add(arr[i]);
      }
   }
   ~SLinkedList(){};
   void add(T e) {
      ListNode* pNew = new ListNode(e);

      if (this->count == 0) {
         this->head = this->tail = pNew;
      } else {
         this->tail->next = pNew;
         this->tail = pNew;
      }

      this->count++;
   }
   int size() {
      return this->count;
   }
   ListNode* init(T* arr, int length) {
      for (int i = 0; i < length; i++) {
         this->add(arr[i]);
      }
      return this->head;
   }
   void printList() {
      stringstream ss;
      ss << "[";
      ListNode* ptr = head;
      while (ptr != tail) {
         ss << ptr->data << ",";
         ptr = ptr->next;
      }

      if (count > 0)
         ss << ptr->data << "]";
      else
         ss << "]";
      cout << ss.str() << endl;
   }
   static void printList(ListNode* node) {
      stringstream ss;
      ss << "[";
      ListNode* ptr = node;
      while (ptr->next) {
         ss << ptr->data << ",";
         ptr = ptr->next;
      }

      if (node)
         ss << ptr->data << "]";
      else
         ss << "]";
      cout << ss.str() << endl;
   }

  public:
   class ListNode {
     private:
      T data;
      ListNode* next;
      friend class SLinkedList<T>;

     public:
      ListNode() {
         next = 0;
      }
      ListNode(T data) {
         this->data = data;
         this->next = nullptr;
      }
   };

  protected:
   ListNode* mergeLists(ListNode* a, ListNode* b);
   ListNode* mergeSortList(ListNode* head);
   void split4Sort(ListNode* head, ListNode** a, ListNode** b);
  public:
   void bubbleSort();
   void mergeSort() { 
      this->head = mergeSortList(this->head);
      ListNode* temp = this->head;
      while (temp->next) temp = temp->next;
      this->tail = temp;
   }
};

template <class T>
void SLinkedList<T>::bubbleSort() {
   ListNode* curr;
   ListNode* prev;
   bool isSwap = true;
   while (isSwap) {
      prev = head;
      curr = head->next;
      isSwap = false;
      while (curr) {
         if (curr->data < prev->data) {
            std::swap(curr->data, prev->data);
            isSwap = true;
         }
         curr = curr->next;
         prev = prev->next;
      }
      // this->printList();
   }
}

template <typename T>
typename SLinkedList<T>::ListNode* SLinkedList<T>::mergeLists(ListNode* a, ListNode* b) {
   if (a == nullptr) {
      return b;
   }
   if (b == nullptr) {
      return a;
   }
   ListNode* result = nullptr;
   ListNode* end = nullptr;
   ListNode* aP = a;
   ListNode* bP = b;
   while (aP && bP) {
      if (aP->data > bP->data) {
         if (!result) {
            result = bP;
            end = result;
         } else {
            end->next = bP;
            end = end->next;
         }
         bP = bP->next;
      } else {
         if (!result) {
            result = aP;
            end = result;
         } else {
            end->next = aP;
            end = end->next;
         }
         aP = aP->next;
      }
   }
   if (aP) end->next = aP;
   if (bP) end->next = bP;
   return result;
}

template <typename T>
typename SLinkedList<T>::ListNode* SLinkedList<T>::mergeSortList(ListNode* head) {
   ListNode* a;
   ListNode* b;
   split4Sort(head, &a, &b);
   if (a == nullptr) return b;
   if (b == nullptr) return a;
   a = mergeSortList(a);
   b = mergeSortList(b);
   return mergeLists(a, b);
}
template <typename T>
void SLinkedList<T>::split4Sort(ListNode* head, ListNode** a, ListNode** b) {
   if (head == nullptr) return;
   ListNode* oneStep = head;
   ListNode* twoStep = head;
   while (twoStep->next && twoStep->next->next) {
      oneStep = oneStep->next;
      twoStep = twoStep->next->next;
   }
   *a = head;
   *b = oneStep->next;
   oneStep->next = nullptr;
}





/* template <typename T>
typename SLinkedList<T>::ListNode* SLinkedList<T>::mergeSortList(ListNode* head) {
   ListNode* a;
   ListNode* b;
   split4Sort(head, &a, &b);
   if (a == nullptr) return b;
   if (b == nullptr) return a;
   a = mergeSortList(a);
   b = mergeSortList(b);
   return mergeLists(a, b);
}
template <typename T>
void SLinkedList<T>::split4Sort(ListNode*& head, ListNode** a, ListNode** b) {
   if (head == nullptr) return;
   ListNode* oneStep = head;
   ListNode* twoStep = head;
   while (twoStep->next && twoStep->next->next) {
      oneStep = oneStep->next;
      twoStep = twoStep->next->next;
   }
   *a = head;
   *b = oneStep->next;
   oneStep->next = nullptr;
} */
