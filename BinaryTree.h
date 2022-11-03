#ifndef BIN_TREE
#define BIN_TREE
#include <deque>
#include <iostream>
#include <queue>
#include <string>
#include <utility>
using namespace std;

class BTNode;
template <class K, class V>
class BinaryTree {
  public:
   class Node;

  private:
   Node *root;
   friend class BTNode;

  public:
   BinaryTree() : root(nullptr) {}
   ~BinaryTree() {
      // You have to delete all Nodes in BinaryTree. However in this task, you can ignore it.
   }
   class Node {
     private:
      K key;
      V value;
      Node *pLeft, *pRight;
      friend class BinaryTree<K, V>;

     public:
      Node(K key, V value) : key(key), value(value), pLeft(NULL), pRight(NULL) {}
      ~Node() {}
   };

   void addNode(string posFromRoot, K key, V value) {
      if (posFromRoot == "") {
         this->root = new Node(key, value);
         return;
      }

      Node *walker = this->root;
      int l = posFromRoot.length();
      for (int i = 0; i < l - 1; i++) {
         if (!walker)
            return;
         if (posFromRoot[i] == 'L')
            walker = walker->pLeft;
         if (posFromRoot[i] == 'R')
            walker = walker->pRight;
      }
      if (posFromRoot[l - 1] == 'L')
         walker->pLeft = new Node(key, value);
      if (posFromRoot[l - 1] == 'R')
         walker->pRight = new Node(key, value);
   }

   // STUDENT ANSWER BEGIN
   int countTwoChildrenNodeRecur(Node *curr) {
      if (!curr) return 0;
      if (curr->pLeft == nullptr || curr->pRight == nullptr) return 0;
      return 1 + countTwoChildrenNode(curr->pLeft) + countTwoChildrenNode(curr->pRight);
   }
   int countTwoChildrenNode() {
      Node *walker = this->root;
      if (!walker) return 0;
      return countTwoChildrenNodeRecur(walker);
   }
   int getHeightRecur(Node *curr) {
      if (curr == nullptr) return 0;
      return max(getHeightRecur(curr->pLeft), getHeightRecur(curr->pRight)) + 1;
   }
   int getHeight() {
      // TODO: return height of the binary tree.
      return getHeightRecur(root);
   }
   string preOrderRecur(Node *curr) {
      if (curr == nullptr) return "";
      string res = to_string(curr->value);
      string left = preOrderRecur(curr->pLeft);
      string right = preOrderRecur(curr->pRight);
      if (left != "") res += (" " + left);
      if (right != "") res += (" " + right);
      return res;
   }
   string preOrder() {
      return preOrderRecur(root);
   }
   string inOrderRecur(Node *curr) {
      if (curr == nullptr) return "";
      string res;
      string left = inOrderRecur(curr->pLeft);
      string right = inOrderRecur(curr->pRight);
      if (left != "") res += (left) + " ";
      res += to_string(curr->value);
      if (right != "") res += (" " + right);
      return res;
   }
   string inOrder() {
      // TODO: return the sequence of values of nodes in in-order.
      return inOrderRecur(root);
   }
   string postOrderRecur(Node *curr) {
      if (curr == nullptr) return "";
      string res;
      string left = postOrderRecur(curr->pLeft);
      string right = postOrderRecur(curr->pRight);
      if (left != "") res += (left) + " ";
      if (right != "") res += (right) + " ";
      res += to_string(curr->value);
      return res;
   }
   string postOrder() {
      // TODO: return the sequence of values of nodes in post-order.
      return postOrderRecur(root);
   }
   int sumOfLeafsRecur(Node *curr) {
      if (curr == nullptr) return 0;
      if (curr->pLeft == nullptr && curr->pRight == nullptr) return curr->value;
      return sumOfLeafsRecur(curr->pLeft) + sumOfLeafsRecur(curr->pRight);
   }
   int sumOfLeafs() {
      return sumOfLeafsRecur(root);
   }
   void BFSRecur(Node *curr) {
      if (curr == nullptr) return;
      printf("%d", curr->value);
      BFSRecur(curr->pLeft);
      BFSRecur(curr->pRight);
   }
   void BFS() {
      if (root == nullptr) return;
      Node *current = root;
      std::queue<Node *> waitList;
      while (current) {
         printf("%d", current->value);
         if (current->pLeft != nullptr) waitList.push(current->pLeft);
         if (current->pRight != nullptr) waitList.push(current->pRight);
         if (!waitList.empty()) {
            printf(" ");
            current = waitList.front();
            waitList.pop();
         } else {
            break;
         }
      }
   }

   int calcPath(int path[], int pathLen) {
      int sum = 0;
      cout << "path: ";
      int idx = pathLen;
      for (int i = 0; i < pathLen; i++) {
         sum += path[i] * pow(10, idx - 1);
         idx--;
         cout << path[i] << " ";
      }
      printf("- %d\n", sum);
      return sum % 27022001;
   }

   void sumDigitPathRecur(Node *root, int path[], int pathLen, int *sum) {
      if (root == nullptr) return;
      path[pathLen] = root->value;
      pathLen++;
      if (root->pLeft == nullptr && root->pRight == nullptr)
         *sum += calcPath(path, pathLen);
      else {
         sumDigitPathRecur(root->pLeft, path, pathLen, sum);
         sumDigitPathRecur(root->pRight, path, pathLen, sum);
      }
   }
   int sumDigitPath(Node *root) {
      int path[100000];
      int *total = new int();
      *total = 0;
      sumDigitPathRecur(root, path, 0, total);
      int sum = *total;
      delete total;
      return sum;
   }
   int sumDigitPath() {
      return sumDigitPath(this->root);
   }
   void printPathRecur(Node *root) {
   }
   void printPath() { printPathRecur(this->root); };

   // TODO: sum of longest path, if

   bool hasValue(Node *root, pair<int, int> val) {
      if (root == nullptr) return false;
      if (root->value == val.first || root->value == val.second) return true;
      return hasValue(root->pLeft, val) || hasValue(root->pRight, val);
   }

   int lowestAncestor(Node *root, int a, int b) {
      pair<int, int> val;
      val = make_pair(a, b);
      bool hRoot = root->value == a || root->value == b;
      if (hRoot) return root->value;
      bool hL = hasValue(root->pLeft, val);
      bool hR = hasValue(root->pRight, val);
      if (hL && hR)
         return root->value;
      else if (hL)
         return lowestAncestor(root->pLeft, a, b);
      return lowestAncestor(root->pRight, a, b);
   }
   int lowestAncestor(int a, int b) {
      return lowestAncestor(root, a, b);
   }
   int rangeCount(Node *root, int lo, int hi) {
      if (root == nullptr) return 0;
      int lC = rangeCount(root->pLeft, lo, hi);
      int rC = rangeCount(root->pRight, lo, hi);
      if (root->value >= lo && root->value <= hi) {
         return 1 + lC + rC;
      }
      return lC + rC;
   }
   int rangeCount(int lo, int hi) {
      return rangeCount(root, lo, hi);
   }
};

#endif /* BIN_TREE */
       /*
          3
       5     2
           1   4
       
       8 + 6 + 9 = 23
       8
       3 6 3 = 12 (-3)
       
       */