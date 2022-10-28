#ifndef BIN_TREE
#define BIN_TREE
#include <iostream>
#include <string>
#include <queue>
using namespace std;

template <class K, class V>
class BinaryTree {
  public:
   class Node;

  private:
   Node *root;

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
   void BFSRecur(Node* curr) {
      if (curr == nullptr) return;
      printf("%d", curr->value);
      BFSRecur(curr->pLeft);
      BFSRecur(curr->pRight);
   }
   void BFS() {
      if (root == nullptr) return;
      Node *current = root;
      std::queue<Node*> waitList;
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
};
// STUDENT ANSWER END

#endif /* BIN_TREE */