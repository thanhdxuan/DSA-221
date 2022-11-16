#include <math.h>

#include <iostream>
#include <queue>
using namespace std;
#define SEPARATOR "#<ab@17943918#@>#"

enum BalanceValue {
   LH = -1,
   EH = 0,
   RH = 1
};

void printNSpace(int n) {
   for (int i = 0; i < n - 1; i++)
      cout << " ";
}

void printInteger(int &n) {
   cout << n << " ";
}

template <class T>
class AVLTree {
  public:
   class Node;

  private:
   Node *root;

  protected:
   int getHeightRec(Node *node) {
      if (node == NULL)
         return 0;
      int lh = this->getHeightRec(node->pLeft);
      int rh = this->getHeightRec(node->pRight);
      return (lh > rh ? lh : rh) + 1;
   }

  public:
   AVLTree() : root(nullptr) {}
   ~AVLTree() {}
   int getHeight() {
      return this->getHeightRec(this->root);
   }
   void printTreeStructure() {
      int height = this->getHeight();
      if (this->root == NULL) {
         cout << "NULL\n";
         return;
      }
      queue<Node *> q;
      q.push(root);
      Node *temp;
      int count = 0;
      int maxNode = 1;
      int level = 0;
      int space = pow(2, height);
      printNSpace(space / 2);
      while (!q.empty()) {
         temp = q.front();
         q.pop();
         if (temp == NULL) {
            cout << " ";
            q.push(NULL);
            q.push(NULL);
         } else {
            cout << temp->data;
            q.push(temp->pLeft);
            q.push(temp->pRight);
         }
         printNSpace(space);
         count++;
         if (count == maxNode) {
            cout << endl;
            count = 0;
            maxNode *= 2;
            level++;
            space /= 2;
            printNSpace(space / 2);
         }
         if (level == height)
            return;
      }
   }
   void printInorderRecur(Node *curr) {
      if (curr == nullptr) return;
      printInorderRecur(curr->pLeft);
      if (curr->pLeft) cout << " ";
      cout << curr->data;
      if (curr->pRight) cout << " ";
      printInorderRecur(curr->pRight);
   }
   void printInorder() {
      printInorderRecur(root);
   }
   bool searchRecur(Node *curr, const T &value) {
      if (curr == nullptr) return false;
      if (curr->data == value) return true;
      return searchRecur(curr->pLeft, value) || searchRecur(curr->pRight, value);
   }
   bool search(const T &value) {
      return searchRecur(root, value);
   }
   void rotateLeft(Node *&curr) {
      if (curr == nullptr) return;
      Node *subRight = curr->pRight;
      Node *temp = curr;
      curr = subRight;
      temp->pRight = curr->pLeft;
      curr->pLeft = temp;
   }
   void rotateRight(Node *&curr) {
      if (curr == nullptr) return;
      Node *subLeft = curr->pLeft;
      Node *temp = curr;
      curr = subLeft;
      temp->pLeft = curr->pRight;
      curr->pRight = temp;
   }
   bool insertBalanceRight(Node *&curr) {
      Node *subRight = curr->pRight;
      if (subRight == nullptr) {
         return false;
         throw "subRight is null";
      }
      if (subRight->balance == RH || subRight->balance == EH) {  // Right of right
         rotateLeft(curr);
         curr->balance = EH;
         (curr->pLeft)->balance = EH;
      } else if (subRight->balance == LH) {  // Left of right
         rotateRight(subRight);
         curr->pRight = subRight;
         rotateLeft(curr);
         if (curr->balance == EH) {
            curr->balance = EH;
            curr->pLeft->balance = EH;
            curr->pRight->balance = EH;
         } else if (curr->balance == RH) {
            curr->balance = EH;
            curr->pLeft->balance = LH;
            curr->pRight->balance = EH;
         } else {
            curr->balance = EH;
            curr->pLeft->balance = EH;
            curr->pRight->balance = RH;
         }
      }
      return false;
   }
   bool insertBalanceLeft(Node *&curr) {
      Node *subLeft = curr->pLeft;
      if (subLeft == nullptr) {
         return false;
         throw "subLeft is null";
      }
      if (subLeft->balance == LH || subLeft->balance == EH) {  // Left of left
         rotateRight(curr);
         curr->balance = EH;
         curr->pRight->balance = EH;
      } else if (subLeft->balance == RH) {  // right of left
         rotateLeft(subLeft);
         curr->pLeft = subLeft;
         rotateRight(curr);
         if (curr->balance == EH) {
            curr->balance = EH;
            curr->pLeft->balance = EH;
            curr->pRight->balance = EH;
         } else if (curr->balance == RH) {
            curr->balance = EH;
            curr->pLeft->balance = LH;
            curr->pRight->balance = EH;
         } else {
            curr->balance = EH;
            curr->pLeft->balance = EH;
            curr->pRight->balance = RH;
         }
      }
      return false;
   }
   bool insert(Node *&curr, const T &value) {  // return true if this tree taller
      if (curr == nullptr) {
         curr = new Node(value);
         return true;
      }
      if (value >= curr->data) {
         bool taller = insert(curr->pRight, value);
         if (taller) {
            if (curr->balance == EH) {
               curr->balance = RH;
               return true;
            } else if (curr->balance == LH) {
               curr->balance = EH;
               return false;
            } else {
               return insertBalanceRight(curr);
            }
         }
      } else {
         bool taller = insert(curr->pLeft, value);
         if (taller) {
            if (curr->balance == EH) {
               curr->balance = LH;
               return true;
            } else if (curr->balance == RH) {
               curr->balance = EH;
               return false;
            } else {
               return insertBalanceLeft(curr);
            }
         }
      }
      return false;  // for pass error
   }

   void insert(const T &value) {
      // TODO
      insert(root, value);
   }
   bool delRightBalance(Node *&curr) {
      if (curr == nullptr) return false;
      if (curr->balance == EH) {
         curr->balance = RH;
         return false;
      } else if (curr->balance == LH) {
         curr->balance = EH;
         return true;
      } else {
         Node *subRight = curr->pRight;
         if (subRight->balance == RH) {  // Right of right
            rotateLeft(curr);
            curr->balance = EH;
            (curr->pLeft)->balance = EH;
         } else if (subRight->balance == LH) {  // Left of right
            rotateRight(subRight);
            curr->pRight = subRight;
            rotateLeft(curr);
            if (curr->balance == EH) {
               curr->balance = EH;
               curr->pLeft->balance = EH;
               curr->pRight->balance = EH;
            } else if (curr->balance == RH) {
               curr->balance = EH;
               curr->pLeft->balance = LH;
               curr->pRight->balance = EH;
            } else {
               curr->balance = EH;
               curr->pLeft->balance = EH;
               curr->pRight->balance = RH;
            }
         } else {
            // E of L
            rotateLeft(curr);
            curr->balance = LH;
            curr->pLeft->balance = RH;
         }
      }
      return false;
   }
   bool delLeftBalance(Node *&curr) {
      if (curr == nullptr) return false;
      if (curr->balance == EH) {
         curr->balance = LH;
         return false;
      } else if (curr->balance == RH) {
         curr->balance = EH;
         return true;
      } else {  // curr->balance == LH
         Node *subLeft = curr->pLeft;
         if (subLeft->balance == LH) {  // Left of left
            rotateRight(curr);
            curr->balance = EH;
            curr->pRight->balance = EH;
         } else if (subLeft->balance == RH) {  // right of left
            rotateLeft(subLeft);
            curr->pLeft = subLeft;
            rotateRight(curr);
            if (curr->balance == EH) {
               curr->balance = EH;
               curr->pLeft->balance = EH;
               curr->pRight->balance = EH;
            } else if (curr->balance == RH) {
               curr->balance = EH;
               curr->pLeft->balance = LH;
               curr->pRight->balance = EH;
            } else {
               curr->balance = EH;
               curr->pLeft->balance = EH;
               curr->pRight->balance = RH;
            }
         } else {  // E of L
            rotateRight(curr);
            curr->balance = RH;
            curr->pRight->balance = LH;
         }
      }
      return false;
   }
   bool removeRecur(Node *&curr, const T &value) {
      if (curr == nullptr) return false;
      if (curr->data == value) {
         if (curr->pLeft == nullptr) {
            Node *temp = curr;
            curr = curr->pRight;
            delete temp;
            return true;
         } else if (curr->pRight == nullptr) {
            Node *temp = curr;
            curr = curr->pLeft;
            delete temp;
            return true;
         }
         // get max value of left
         Node *temp = curr->pLeft;
         while (temp->pRight) {
            temp = temp->pRight;
         }
         curr->data = temp->data;
         bool shorter = removeRecur(curr->pLeft, temp->data);
         if (shorter) {
            return delRightBalance(curr);
         }
      } else if (value < curr->data) {  // delete at lef;t
         bool shorter = removeRecur(curr->pLeft, value);
         if (shorter) {
            return delRightBalance(curr);
         }
      }
      // delete at right
      bool shorter = removeRecur(curr->pRight, value);
      if (shorter) {
         return delLeftBalance(curr);
      }
      return false;
   }
   void remove(const T &value) {
      // TODO
      removeRecur(root, value);
   }

   class Node {
     private:
      T data;
      Node *pLeft, *pRight;
      BalanceValue balance;
      friend class AVLTree<T>;

     public:
      Node(T value) : data(value), pLeft(NULL), pRight(NULL), balance(EH) {}
      ~Node() {}
   };
};