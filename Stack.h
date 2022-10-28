#ifndef STACK_H
#define STACK_H

#include "DLinkedList.cpp"
template<class T>
class Stack {
protected:
    DLinkedList<T> list;
public:
    Stack() {}
    void push(T item) ;
    T pop() ;
    T top() ;
    bool empty() ;
    int size() ;
    void clear() ;
};

#endif

template<typename T>
void Stack<T>::push(T item) {
    // TODO: Push new element into the top of the stack
   this->list.add(0, item);
}
template<typename T>
T Stack<T>::pop() {
    // TODO: Remove an element on top of the stack
   if (!this->list.empty()) {
      return this->list.removeAt(0);
   }
   T a;
   return a;
}

template<typename T>
T Stack<T>::top() {
    // TODO: Get value of the element on top of the stack
   if (!this->list.empty()) {
      return this->list.get(0);
   }
   T a;
   return a;     
}
template<typename T>
bool Stack<T>::empty() {
    // TODO: Determine if the stack is empty
    return this->list.empty();
        
}
template<typename T>
int Stack<T>::size() {
    // TODO: Get the size of the stack
    return this->list.size();
        
}
template<typename T>
void Stack<T>::clear() {
    // TODO: Clear all elements of the stack
   this->list.clear();
}