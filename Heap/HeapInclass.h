#include <iostream>

class Heap {
  private:
   int* data;
   int size;
   int capacity;

  public:
   Heap() {
      this->data = NULL;
      this->size = 0;
      this->capacity = 0;
   }

   Heap(int* arr, int n) {
      this->copyFromArray(arr, n);
   }

   ~Heap() {
      this->clear();
   }

   void copyFromArray(int* arr, int n) {
      this->clear();
      this->size = n;
      this->capacity = this->size * 3 / 2;
      this->data = new int[this->capacity];
      for (int i = 0; i < this->size; i++) {
         this->data[i] = arr[i];
      }
   }
   void reHeapUp(int index) {
      if (index <= 0 || index >= size) {
         return;
      }
      int parentIdx = (index - 1) / 2;
      if (data[parentIdx] < data[index]) {
         int temp = data[parentIdx];
         data[parentIdx] = data[index];
         data[index] = temp;
         reHeapUp(parentIdx);
      }
   }
   void reHeapDown(int index) {
        int leftChild = 2 * index + 1;
        if (leftChild >= size) {
            //not have leftChild
            return;
        }
        int rightChild = leftChild + 1;
        if (rightChild >= size) {
            //not have rightChild
            swap(data[leftChild], data[index]);
        }
        else {
            int child = (data[leftChild] > data[rightChild]) ? leftChild : rightChild;
            if (data[child] > data[index]) {
                swap(data[child], data[index]);
                reHeapDown(child);
            }
        }
   }
   void print() {
      for (int i = 0; i < this->size; i++) {
         cout << this->data[i] << " ";
      }
      cout << "\n";
   }

   void clear() {
      if (this->data != NULL) {
         delete this->data;
         this->size = 0;
         this->capacity = 0;
      }
   }
};