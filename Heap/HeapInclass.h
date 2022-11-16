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
        int firstLeaf = size / 2;
        if (index < 0 || index >= firstLeaf) {
            return;
        }
        int leftChildIdx = 2 * index + 1;
        int rightChildIdx = 2 * index + 2;
        if (rightChildIdx < size) {
            if (data[leftChildIdx] < data[rightChildIdx]) {
                //swap parent with right child
                if (data[index] < data[rightChildIdx]) {
                    int temp = data[rightChildIdx];
                    data[rightChildIdx] = data[index];
                    data[index] = temp;
                    reHeapDown(rightChildIdx);
                }
            }
            else {
                //swap parent with left child
                if (data[index] < data[leftChildIdx]) {
                    int temp = data[leftChildIdx];
                    data[leftChildIdx] = data[index];
                    data[index] = temp;
                    reHeapDown(leftChildIdx);
                }
            }
        }
        else {
            if (data[index] < data[leftChildIdx]) {
                int temp = data[leftChildIdx];
                data[leftChildIdx] = data[index];
                data[index] = temp;
                reHeapDown(leftChildIdx);
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