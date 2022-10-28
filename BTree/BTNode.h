#ifndef BT_NODE
#define BT_NODE
#include <stdlib.h>
#include <stdio.h>
class BTNode {
  public:
   int val;
   BTNode* left;
   BTNode* right;
   BTNode() {
      this->left = this->right = NULL;
   }
   BTNode(int val) {
      this->val = val;
      this->left = this->right = NULL;
   }
   BTNode(int val, BTNode*& left, BTNode*& right) {
      this->val = val;
      this->left = left;
      this->right = right;
   }
   static BTNode* createTree(int* arrBegin, int* arrEnd, int* value) {
      BTNode* root = new BTNode(*arrBegin);
      for (int* temp = arrBegin + 1; temp < arrEnd; temp++) {
         if (*temp == 0);
      }
   }
};

#endif /* BT_NODE */