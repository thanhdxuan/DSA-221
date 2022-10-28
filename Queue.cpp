#include "Queue.h"
#include <queue>
#include <stack>
using namespace std;
template <typename T>
void Queue<T>::push(T item) {
   // TODO: Push new element into the end of the queue
   this->list.add(item);

}
template <typename T>
T Queue<T>::pop() {
   // TODO: Remove an element in the head of the queue
   if (!this->list.empty()) {
      return this->list.removeAt(0);
   }
   return -1;
}
template <typename T>
T Queue<T>::top() {
   // TODO: Get value of the element in the head of the queue
   if (!this->list.empty()) {
      return this->list.get(0);
   }
   return -1;
}
template <typename T>
bool Queue<T>::empty() {
   // TODO: Determine if the queue is empty
   return this->list.empty();
      
}
template <typename T>
int Queue<T>::size() {
   // TODO: Get the size of the queue
   return this->list.size();
}
template <typename T>
void Queue<T>::clear() {
   // TODO: Clear all elements of the queue
   this->list.clear();
}

// template <typename T>
// void Queue<T>::reverseQueue(std::queue<int> &q) {
//    // TODO
//    stack<int> mystack;
//    while (!q.empty()) {
//       mystack.push(q.front());
//       q.pop();
//    }
//    while (!mystack.empty()) {
//       q.push(mystack.top());
//       mystack.pop();
//    }
// }