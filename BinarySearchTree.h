#include <iostream>
#include <sstream>
#include <string>
using namespace std;
#define SEPARATOR "#<ab@17943918#@>#"

template <class T>
class BinarySearchTree {
  public:
   class Node;

  private:
   Node* root;

  public:
   BinarySearchTree() : root(nullptr) {}
   ~BinarySearchTree() {
      // You have to delete all Nodes in BinaryTree. However in this task, you can ignore it.
   }

   // Helping function

   string inOrderRec(Node* root) {
      stringstream ss;
      if (root != nullptr) {
         ss << inOrderRec(root->pLeft);
         ss << root->value << " ";
         ss << inOrderRec(root->pRight);
      }
      return ss.str();
   }

   string inOrder() {
      return inOrderRec(this->root);
   }

   class Node {
     private:
      T value;
      Node *pLeft, *pRight;
      friend class BinarySearchTree<T>;

     public:
      Node(T value) : value(value), pLeft(NULL), pRight(NULL) {}
      ~Node() {}
   };
   T getMin() {
      // TODO: return the minimum values of nodes in the tree.
      Node* temp = this->root;
      if (temp == nullptr) return -1;
      while (temp->pLeft) {
         temp = temp->pLeft;
      }
      return temp->value;
   }

   T getMax() {
      // TODO: return the maximum values of nodes in the tree.
      Node* temp = this->root;
      if (temp == nullptr) return -1;
      while (temp->pRight) {
         temp = temp->pRight;
      }
      return temp->value;
   }
   bool findRecur(T i, Node* curr) {
      if (curr == nullptr) return false;
      if (i == curr->value) return true;
      if (i >= curr->value) return findRecur(i, curr->pRight);
      return findRecur(i, curr->pLeft);
   }
   bool find(T i) {
      // TODO: return true if value i is in the tree; otherwise, return false.
      return findRecur(i, root);
   }
   T sum(T l, T r, Node* curr) {
      if (curr == nullptr) return 0;
      T res;
      if (curr->value >= l && curr->value <= r) res += curr->value;
      T lS = sum(l, r, curr->pLeft);
      T rS = sum(l, r, curr->pRight);
      res += lS + rS;
      return res;
   }
   T sum(T l, T r) {
      // TODO: return the sum of all element in the tree has value in range [l,r].
      return sum(l, r, root);
   }
   void addRecur(Node* &curr, T value) {
      if (curr == nullptr) { curr = new Node(value); return; }
      if (value >= curr->value) addRecur(curr->pRight, value);
      if (value < curr->value) addRecur(curr->pLeft, value);
   }
   void add(T value) {
      addRecur(root, value);
   }
   void deleteNodeRecur(Node* &curr, T value) {
      if (curr == nullptr) return;
      if (value < curr->value) deleteNodeRecur(curr->pLeft, value);
      else if (value > curr->value) deleteNodeRecur(curr->pRight, value);
      else {
         if (curr->pRight == nullptr) { 
            Node* temp = curr;
            curr = curr->pLeft;
            delete temp;
            return;
         }
         else if (curr->pLeft == nullptr) {
            Node* temp = curr;
            curr = curr->pRight;
            delete temp;
            return;
         }
         else {
            Node* temp = curr->pLeft;
            while (temp->pRight) {
               temp = temp->pRight;
            }
            curr->value = temp->value;
            deleteNodeRecur(curr->pLeft, temp->value);
         }
      }
   }
   void deleteNode(T value) {
      return deleteNodeRecur(root, value);
   }
};