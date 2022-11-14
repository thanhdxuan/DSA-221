#include <algorithm>
#include <iostream>
#include <queue>
#include <sstream>
#include <stack>
#include <string>
#include <vector>
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
   void addRecur(Node*& curr, T value) {
      if (curr == nullptr) {
         curr = new Node(value);
         return;
      }
      if (value >= curr->value) addRecur(curr->pRight, value);
      if (value < curr->value) addRecur(curr->pLeft, value);
   }
   void add(T value) {
      addRecur(root, value);
   }
   void deleteNodeRecur(Node*& curr, T value) {
      if (curr == nullptr) return;
      if (value < curr->value)
         deleteNodeRecur(curr->pLeft, value);
      else if (value > curr->value)
         deleteNodeRecur(curr->pRight, value);
      else {
         if (curr->pRight == nullptr) {
            Node* temp = curr;
            curr = curr->pLeft;
            delete temp;
            return;
         } else if (curr->pLeft == nullptr) {
            Node* temp = curr;
            curr = curr->pRight;
            delete temp;
            return;
         } else {
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
   // TODO: In the first level, we should traverse from left to right (order: 3)
   // and in the second level, we traverse from right to left
   //TODO: count value [lo, hi]

   void inOrderRecur(Node* curr, int k, vector<int> &res) {
      if (curr == nullptr) return;
      inOrderRecur(curr->pLeft, k, res);
      if (res.size() >= k) return;
      res.push_back(curr->value);
      inOrderRecur(curr->pRight, k, res);
   }
   int kthSmallest(int k) {
      vector<int> sorted;
      inOrderRecur(root, k, sorted);
      for (auto i : sorted) cout << i << " ";
      cout << "\n";
      return sorted[k - 1];
   }
   
   int singleChild(Node *curr) {
      if (curr == nullptr) return 0;
      if (curr->pLeft == nullptr && curr->pRight == nullptr) return 0;
      if (curr->pLeft == nullptr || curr->pRight == nullptr) {
         if (curr->pLeft == nullptr) return 1 + singleChild(curr->pRight);
         if (curr->pRight == nullptr) return 1 + singleChild(curr->pLeft);
      }
      return singleChild(curr->pLeft) + singleChild(curr->pRight);
   }
   int singleChild() {
      return singleChild(root);
   }

   //delete every node inrange 
   void deleteIfOutOfRange(Node* &root, int lo, int hi) {
      if (root == nullptr) return;
      if (root->pLeft != nullptr) deleteIfOutOfRange(root->pLeft, lo, hi);
      if (root->pRight != nullptr) deleteIfOutOfRange(root->pRight, lo, hi);
      
      if (root->value < lo) {
         Node *temp = root;
         root = root-> pRight;
         delete temp;
      }
      else if (root->value > hi) {
         Node *temp = root;
         root = root-> pLeft;
         delete temp;
      }
   }
   void delteOOR(int lo, int hi) {
      deleteIfOutOfRange(root, lo, hi);
   } 
   // void subTreeWithRange(Node* root, int lo, int hi) {
   //    if (root == nullptr) return;
   //    if (root->value >= lo && root->value <= hi) {

   //    }
   //    deleteNodeRecur(root->pLeft, )
   // }
   vector<int> levelAlterTraverse(Node* curr) {
      // STUDENT ANSWER
      vector<int> res;
      if (curr == nullptr) return res;
      stack<Node*> s1;
      stack<Node*> s2;
      s1.push(curr);
      while (!s1.empty() || !s2.empty()) {
         while (!s1.empty()) {
            Node* temp = s1.top();
            res.push_back(temp->value);            
            s1.pop();
            if (temp->pLeft != NULL) s2.push(temp->pLeft);
            if (temp->pRight != NULL) s2.push(temp->pRight);
         }
         while (!s2.empty()) {
            Node* temp = s2.top();
            res.push_back(temp->value);            
            s2.pop();
            if (temp->pRight != NULL) s1.push(temp->pRight);
            if (temp->pLeft != NULL) s1.push(temp->pLeft);
         }
      }
      return res;
   }
   vector<int> levelAlterTraverse() {
      return levelAlterTraverse(this->root);
   }
}; 