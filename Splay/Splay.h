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
   void rotateLeft(Node*& curr) {
      if (curr == nullptr) return;
      Node* subRight = curr->pRight;
      Node* temp = curr;
      curr = subRight;
      temp->pRight = curr->pLeft;
      curr->pLeft = temp;
      if (temp->pParent) temp->pParent->pLeft = curr;
      //change parent
      subRight->pParent = temp->pParent;
      temp->pParent = subRight;
      if (temp->pRight) temp->pRight->pParent = temp;
   }
   void rotateRight(Node*& curr) {
      if (curr == nullptr) return;
      Node* subLeft = curr->pLeft;
      Node* temp = curr;
      curr = subLeft;
      temp->pLeft = curr->pRight;
      curr->pRight = temp;
      if (temp->pParent) temp->pParent->pRight = curr;
      //change parent
      subLeft->pParent = temp->pParent;
      temp->pParent = subLeft;
      if (temp->pLeft) temp->pLeft->pParent = temp;
   }
   void splay(Node* p) {
      // To Do
      while (p->pParent != nullptr) {
         if (p->pParent->pParent == nullptr) {
            // Zic
            if (p->pParent->pLeft == p) {
               rotateRight(p->pParent);
            } else {
               // Zac
               rotateLeft(p->pParent);
            }
         } else {
            if (p->pParent->pLeft == p && p->pParent->pParent->pLeft == p->pParent) {
               // Zig-Zig
               rotateRight(p->pParent->pParent);
               rotateRight(p->pParent);
               
            } else if (p->pParent->pRight == p && p->pParent->pParent->pRight == p->pParent) {
               // Zac-Zac
               rotateLeft(p->pParent->pParent);
               rotateRight(p->pParent);
            } else if (p->pParent->pRight == p && p->pParent->pParent->pLeft == p->pParent) {
               // Zig-Zag
               rotateLeft(p->pParent);
               rotateRight(p->pParent);
            } else {
               // Zag-Zig
               rotateRight(p->pParent);
               rotateLeft(p->pParent);
            }
         }
      }
   }
   void insertRecur(Node *&curr, const int &val) {
      if (curr == nullptr) {
         curr = new Node(val);
         return;
      }
      if (val < curr->val) {
         insertRecur(curr->pLeft, val);
         if (curr->pLeft) curr->pLeft->pParent = curr;
         Node* subLeft = curr->pLeft;
         splay(subLeft);
         curr = subLeft;
         return;
      }
      else {
         insertRecur(curr->pRight, val);
         if (curr->pRight) curr->pRight->pParent = curr;
         Node *subRight = curr->pRight;
         splay(subRight);
         curr = subRight;
         return;
      }
   }
   void insert(int val) {
      insertRecur(root, val);
   }
};