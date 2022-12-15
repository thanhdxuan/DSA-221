#include <iostream>

using namespace std;
class SplayTree {
   struct Node {
      int val;
      Node* pLeft;
      Node* pRight;
      Node* pParent;
      Node(int val = 0, Node* l = nullptr, Node* r = nullptr, Node* par = nullptr) : val(val), pLeft(l), pRight(r), pParent(par) {}
   };
   Node* root;

   // print the tree structure for local testing
   void printBinaryTree(string prefix, const Node* root, bool isLeft, bool hasRightSibling) {
      if (!root && isLeft && hasRightSibling) {
         cout << prefix << "├──\n";
      }
      if (!root) return;
      cout << prefix;
      if (isLeft && hasRightSibling)
         cout << "├──";
      else
         cout << "└──";
      cout << root->val << '\n';
      printBinaryTree(prefix + (isLeft && hasRightSibling ? "|  " : "   "), root->pLeft, true, root->pRight);
      printBinaryTree(prefix + (isLeft && hasRightSibling ? "|  " : "   "), root->pRight, false, root->pRight);
   }

   void printPreorder(Node* p) {
      if (!p) {
         return;
      }
      cout << p->val << ' ';
      printPreorder(p->pLeft);
      printPreorder(p->pRight);
   }

  public:
   SplayTree() {
      root = nullptr;
   }
   ~SplayTree() {
      // Ignore deleting all nodes in the tree
   }

   void printBinaryTree() {
      printBinaryTree("", root, false, false);
   }

   void printPreorder() {
      printPreorder(root);
      cout << "\n";
   }
   Node* rotateLeft(Node* curr) {
      if (curr == nullptr) return curr;
      Node* temp = curr->pRight;
      curr->pRight = temp->pLeft;
      temp->pLeft = curr;
      return temp;
   }
   Node* rotateRight(Node* curr) {
      if (curr == nullptr) return curr;
      Node* temp = curr->pLeft;
      curr->pLeft = temp->pRight;
      temp->pRight = curr;
      return temp;
   }
   void splay(Node* &p) {
      while (p->pParent != nullptr) {
         if (p->pParent->pParent == nullptr) {
            if (p->pParent->pLeft == p) { //Zig
               p = rotateRight(p);
            }
            else {
               p = rotateLeft(p);
            }
         }
         else {
            if (p->pParent->pParent->pLeft) {
               //Zig-Zig
            }
            else if (p->pParent->pParent->pLeft->pLeft) {
               
            }
         }
      }
   }
   Node* insertRecur(Node *&curr, const int &val) {
      if (curr == nullptr) {
         curr = new Node(val);
         return curr;
      }
      if (val < curr->val) {
         Node* newNode = insertRecur(curr->pLeft, val);
         newNode->pParent = curr;
         splay(newNode);
         return newNode;
      }
      Node* newNode = insertRecur(curr->pRight, val);
      splay(newNode);
      return newNode;
   }
   void insert(int val) {
      root = insertRecur(root, val);
   }
};