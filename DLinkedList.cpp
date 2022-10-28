#include "DLinkedList.h"

template <class T>
std::string DLinkedList<T>::toString() const {
   std::stringstream ss;
   Node* temp = head;
   ss << "[";
   while (temp) {
      ss << temp->data;
      temp->next == nullptr ? ss << "" : ss << ", ";
      temp = temp->next;
   }
   ss << "]";
   return ss.str();
}
template <class T>
void DLinkedList<T>::add(const T& e) {
   /* Insert an element into the end of the list. */
   Node* newNode = new Node(e);
   if(head == nullptr) {
      head = tail = newNode;
      count++;
      return;
   }
   this->tail->next = newNode;
   newNode->previous = this->tail;
   tail = newNode;
   count++;
}

template<class T>
void DLinkedList<T>::add(int index, const T& e) {
   /* Insert an element into the list at given index. */ 
   if (index < 0 || index > count) {
      throw std::out_of_range("");
   }
   else if (count == 0 || index == count) {
      add(e);
      return;
   }
   else if (index == 0) {
      Node* newNode = new Node(e);
      newNode->next = this->head;
      this->head->previous = newNode;
      this->head = newNode;
      count++;
      return;
   }
   Node* newNode = new Node(e);
   Node* prev = head;
   Node* temp = head;
   //if index < count / 2;
   if (index < count / 2) {
      for (int i = 0; i < index - 1; i++) {
         temp = temp->next;
         prev = prev->next;
      }
      temp = temp->next; // get current node
      prev->next = newNode;
      newNode->previous = prev;
      newNode->next = temp;
      temp->previous = newNode;
   }
   else {
      temp = tail;
      prev = tail;
      for (int i = 0; i < count - index - 1; i++) {
         temp = temp->previous;
         prev = prev->previous;
      }
      temp = temp->previous; //get current node
      newNode->previous = temp;
      newNode->next = prev;
      temp->next = newNode;
      prev->previous = newNode;
   }
   count++;
}
template<class T>
T DLinkedList<T>::removeAt(int index) {
   if (index < 0 || index >= count) { 
      throw std::out_of_range("");
   }
   if (count == 1) {
         T val = head->data;
         count = 0;
         delete head;
         head = tail = nullptr;
         return val;
   }
   else if (index == 0) {
      Node* temp = head;
      head = head ->next;
      head->previous = nullptr;
      temp->next = nullptr;
      T val = temp->data;
      delete temp;
      count--;
      return val;
   }
   else if (index == count - 1) {
      Node* temp = tail;
      T val = tail->data;
      tail = tail->previous;
      delete temp;
      tail->next = nullptr;
      count--;
      return val;
   }
   Node* prev = head;
   Node* temp = head;
   if (index < count / 2) {
      for (int i = 0; i < index - 1; i++) {
         temp = temp->next;
         prev = prev->next;
      }
      temp = temp->next; // get current node
      prev->next = temp->next;
      temp->next->previous = prev;
      T val = temp->data;
      delete temp;
      count--;
      return val;
   }
   else {
      temp = tail;
      prev = tail;
      for (int i = 0; i < count - index - 2; i++) {
         temp = temp->previous;
         prev = prev->previous;
      }
      temp = temp->previous; //get current node
      prev->previous = temp->previous;
      prev->previous->next = prev;
      T val = temp->data;
      delete temp;
      count--;
      return val;
   }
   T a;
   return a;
}
template<class T>
bool DLinkedList<T>::removeItem(const T &removeItem ) {
   if (contains(removeItem)) {
      int i = indexOf(removeItem);
      removeAt(i);
      return true;
   }
   return false;
}
template<class T>
int DLinkedList<T>::size() {
   /* Return the length (size) of list */ 

   return count;
}

template<class T>
T DLinkedList<T>::get(int index) {
   /* Give the data of the element at given index in the list. */
   if (index < 0 || index >= count) {
      throw std::out_of_range("");
   }
   Node* temp;
   if (index < count / 2) {
      temp = head;
      for (int i = 0; i < index; i++) {
         temp = temp->next;
      }
      return temp->data;
   }
   //if  index >= count / 2 -> traverse at tail 
   temp = tail;
   for (int i = 0; i < count - index - 1; i++) {
      temp = temp->previous;
   }
   return temp->data;
}

template <class T>
void DLinkedList<T>::set(int index, const T& e) {
   /* Assign new value for element at given index in the list */
   if (index < 0 || index >= count) {
      throw std::out_of_range("");
   }
   Node* temp;
   if (index < count / 2) {
      temp = head;
      for (int i = 0; i < index; i++) {
         temp = temp->next;
      }
      temp->data = e;
      return;
   }
   //if  index >= count / 2 -> traverse at tail 
   temp = tail;
   for (int i = 0; i < count - index - 1; i++) {
      temp = temp->previous;
   }
   temp->data = e;
}

template<class T>
bool DLinkedList<T>::empty() {
   /* Check if the list is empty or not. */
   return count == 0;
}

template<class T>
int DLinkedList<T>::indexOf(const T& item) {
   /* Return the first index wheter item appears in list, otherwise return -1 */
   Node* temp;
   temp = head;
   for (int i = 0; i < count; i++) {
      if (temp->data == item) {
         return i;
      }
      temp = temp->next;
   }
   return -1;
}

template<class T>
bool DLinkedList<T>::contains(const T& item) {
   /* Check if item appears in the list */
   int i = indexOf(item);
   return i != -1;
}

template<class T>
void DLinkedList<T>::clear() {
   Node* temp = head;
   while (head) {
      temp = head;
      head = head->next;
      delete temp;
   }
   head = tail = nullptr;
   count = 0;
}

// NOTE: reverse
template <typename T>
void DLinkedList<T>::reverse(int l, int r) {
   int mid = (l + r) / 2;
   Node *left = head;
   Node *right = tail
   while (l > 0) {
      left = left->next;
      l--;
   } 
   while (count - r - 1 > 0) {
      right = right->previous;
      r++;
   }
   while (mid) {
      //swap(left, right)
   }
}



/*
* TODO: Implement class Iterator's method
* Note: method remove is different from SLinkedList, which is the advantage of DLinkedList
*/
template <class T>
DLinkedList<T>::Iterator::Iterator(DLinkedList<T> *pList, bool begin) {
   this->pList = pList;
   if (begin) {
      if (this->pList->head) {
         this->current = this->pList->head;
         index = 0;
      }
      else {
         this->current = NULL;
         index = -1;
      }
   }
   else {
      this->current = NULL;
      if (pList) {
         index = this->pList->count;
      }
      else {
         index = 0;
      }
   }
}

template <class T>
typename DLinkedList<T>::Iterator& DLinkedList<T>::Iterator::operator=(const DLinkedList<T>::Iterator &iterator) {
   this->pList = iterator.pList;
   this->current = iterator.current;
   this->index = iterator.index;
   return *this;
}

template <class T> 
void DLinkedList<T>::Iterator::set(const T &e) {
   if (current == nullptr) {
      throw std::out_of_range("Segmentation fault!");
   }
   this->current->data = e;
}

template<class T>
T& DLinkedList<T>::Iterator::operator*()  {
   if (current == nullptr) {
      throw std::out_of_range("Segmentation fault!");
   }
   return this->current->data;
}

template<class T>
void DLinkedList<T>::Iterator::remove() {
/*
* TODO: delete Node in pList which Node* current point to. 
*       After that, Node* current point to the node before the node just deleted.
*       If we remove first node of pList, Node* current point to nullptr.
*       Then we use operator ++, Node* current will point to the head of pList.
*/
   if (this->current == this->pList->head) {
      this->pList->removeAt(0);
      this->current = nullptr;
      index--;
      return;
   }
   this->current = this->current->previous;
   this->pList->removeAt(index);
   index--;
}

template<class T>
bool DLinkedList<T>::Iterator::operator!=(const DLinkedList::Iterator &iterator) {
   return !(this->current == iterator.current && this->index == iterator.index);
}

template<class T>
typename DLinkedList<T>::Iterator& DLinkedList<T>::Iterator::operator++() {
   if (this->current == NULL && this->index == -1 && this->pList != NULL) {
      this->current = this->pList->head;
      this->index = 0;
      return *this;
   }
   if (this->current->next == NULL) {
      throw std::out_of_range("Segmentation fault!");
   }
   this->current = this->current->next;
   this->index++;
   return *this;
}

template<class T>
typename DLinkedList<T>::Iterator DLinkedList<T>::Iterator::operator++(int) {
   Iterator iterator= *this;
   ++(*this);
   return iterator;
}