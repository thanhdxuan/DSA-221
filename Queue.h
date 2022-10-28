#ifndef QUEUE_H
#define QUEUE_H
#include "DLinkedList.h"
#include <queue>
template<class T>
class Queue {
protected:
   DLinkedList<T> list;
public:
   Queue() {}
   void push(T item) ;
   T pop() ;
   T top() ;
   bool empty() ;
   int size() ;
   void clear() ;
   // void reverseQueue(std::queue<T> & q);
};
class QueueS {
private:
    stack<int> st;
    stack<int> temp;
public:
    void enqueue(int value) {
        st.push(value);
        while (!temp.empty()) temp.pop();
        stack<int> ST = st;
        while (!ST.empty()) {
          int data = ST.top();
          ST.pop();
          temp.push(data);
        }
    }
    int dequeue() {
        if (temp.size() == 0) throw std::out_of_range("Empty queue");
        int data = temp.top();
        temp.pop();
        return data;
    }
    int front() {
        if (temp.size() == 0) throw std::out_of_range("Empty queue");
        int data = temp.top();
        return data;
    }
    int rear() {
        if (st.size() == 0) throw std::out_of_range("Empty queue");
        int data = st.top();
        return data;
    }
    
    string toString() {
        string s;
        if (temp.size() == 0) {
            s = "FRONT||REAR";
            return s;
        }
        stack<int> t = this->temp;
        s += "FRONT|";
        while(!t.empty()) {
            s = s + " " + to_string(t.top());
            t.pop();
        }
        s += "|REAR";
        return s;
    }
};
#endif /* QUEUE_H */