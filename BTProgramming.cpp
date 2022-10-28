#include <iostream>
#include <string>
#include <queue>
class Node {
public:
    int data;
    Node* left;
    Node* right;
    
    Node(const int& data) { this->data = data; }
};

class BinaryTree {
private:
        Node* root;
    
protected:
        int getSizeRec(Node *);
        bool isBSTRecur(Node *);
public:
	BinaryTree()
	{
		this->root = NULL;
	}

   int getSize();
   bool isBST();
   void levelOrderTraverse();
};

bool BinaryTree::isBSTRecur(Node* node) {
   if (node == nullptr) return true;
   if (node->left == nullptr && node->right == nullptr) return true;
   else if (node->left != nullptr) {
      return (node->data > node->left->data) && isBSTRecur(node->left);
   }
   return (node->data <= node->right->data) && isBSTRecur(node->right);
}

bool BinaryTree::isBST() {
   return BinaryTree::isBSTRecur(root);
}
void BinaryTree::levelOrderTraverse() {
	if (root == nullptr) return;
   Node* currentNode = root;
	std::queue<Node*> bfs;
   while (currentNode) {
      std:: cout << currentNode->data;
      if (currentNode->left) { bfs.push(currentNode->left); }
      if (currentNode->right) { bfs.push(currentNode->right); }
      if (!bfs.empty()) {
         std::cout << " ";
         currentNode = bfs.front();
         bfs.pop();
      }
      else {
         currentNode = nullptr;
      }
   }
}