#include "ConcatStringList.h"
using namespace std;

ConcatStringList::ReferencesList ConcatStringList::refList = ConcatStringList::ReferencesList();
ConcatStringList::DeleteStringList ConcatStringList::delStrList = ConcatStringList::DeleteStringList();

ConcatStringList::ConcatStringList(): head(nullptr), tail(nullptr), sizeL(0), count(0) {}
void ConcatStringList::checkIndex(int index) const { //Check Index
   if (index < 0 || index >= this->sizeL) {
      throw out_of_range("Index of string is invalid!");
   }
}
ConcatStringList::ConcatStringList(const char* ch) {
   this->head = new CharArrayNode(ch);
   this->tail = head;
   this->sizeL = head->getSize();
   count = 1;
}
int ConcatStringList::length() const {
   return this->sizeL;
}
char ConcatStringList::get(int index) const {
   checkIndex(index);
   CharArrayNode* temp = head;
   int count = 0;
   while (temp) {
      if (index <= (temp->getSize() - 1) && index >= 0) {
         return temp->CharArrayList[index];
      }
      index -= temp->getSize();
      temp = temp->next;
   }
   char c;
   return c;
}
//Additional method
ConcatStringList::CharArrayNode* ConcatStringList::getPtr(int index, int &newIdx) const {
   checkIndex(index);
   CharArrayNode* temp = head;
   while (temp) {
      if (index <= (temp->getSize() - 1) && index >= 0) {
         newIdx = index;
         return temp;
      }
      index -= temp->getSize();
      temp = temp->next;
   }
   return temp;
}
void ConcatStringList::addNode(const string &s) {
   CharArrayNode* newNode = new CharArrayNode(s);
   if (head == nullptr) {
      head = tail = newNode;
      sizeL += newNode->getSize();
      count++;
      return;
   }
   tail->next = newNode;
   tail = newNode;
   sizeL += newNode->getSize();
   count++;
}
void ConcatStringList::addNode(const string &s, int index) {
   if (index < 0 || index > this->count) { 
      throw std::out_of_range("Index of string is invalid!");
   }
   if (count == 0 || index == count) {
      addNode(s);
      return;
   }
   else if (index == 0) {
      CharArrayNode* newNode = new CharArrayNode(s);
      newNode->next = head;
      head = newNode;
      sizeL += newNode->getSize();
      count++;
   }
   else {
      CharArrayNode* curNode = head;
      CharArrayNode* prev = head;
      CharArrayNode* newNode = new CharArrayNode(s);
      for (int i = 0; i < count ; i++) {
         if (i == index - 1) {
            prev = curNode;
            curNode = curNode->next;
            break;
         }
         curNode = curNode->next;
      }
      prev->next = newNode;
      newNode->next = curNode;
      sizeL += newNode->getSize();
      count++;
   }
      
}
//End of additional method
int ConcatStringList::indexOf(char c) const {
   CharArrayNode* temp = head;
   for (int i = 0; i < count; i++) {
      size_t found = temp->CharArrayList.find_first_of(c);
      if (found != std::string::npos) return found;
   }
   return -1;
}
std::string ConcatStringList::toString() const {
   stringstream listStr;
   CharArrayNode* temp = head;
   if(temp == nullptr) return "ConcatStringList[\"\"]";
   listStr << "ConcatStringList[\"";
   while (temp) {
      listStr << temp->CharArrayList;
      temp = temp->next;
   }
   listStr << "\"]";
   return listStr.str();
}

ConcatStringList ConcatStringList::concat(const ConcatStringList &otherS) const {
   CharArrayNode* t = tail;
   t->next = otherS.head;   
   int sizeTotal = this->sizeL + otherS.sizeL;
   int countTotal = this->count + otherS.count; 
   ConcatStringList temp(this->head, otherS.tail, sizeTotal, countTotal);
   return temp;
}

ConcatStringList ConcatStringList::subString(int from, int to) const {
   checkIndex(from);
   checkIndex(to);
   if (from >= to) throw logic_error("Invalid range");
   int lCh, rCh;
   CharArrayNode *lNode = this->getPtr(from, lCh);
   CharArrayNode *rNode = this->getPtr(to - 1, rCh);
   ConcatStringList subList;
   if (lNode == rNode) {
      string s = lNode->CharArrayList.substr(lCh, rCh - lCh + 1);
      subList.addNode(s);
      return subList;
   }
   CharArrayNode* temp = lNode;
   string s;
   while(true) {
      if (temp == lNode) {
         s = temp->CharArrayList.substr(lCh);
      }
      else if (temp == rNode) {
         s = temp->CharArrayList.substr(0, rCh + 1);
      }
      else {
         s = temp->CharArrayList;
      }
      subList.addNode(s);
      if (temp == rNode) break;
      temp = temp->next;
   }
   return subList;
   
}

ConcatStringList ConcatStringList::reverse() const {
   CharArrayNode* temp = head;
   ConcatStringList revList;
   while (temp) {
      string s = string(temp->CharArrayList.rbegin(), temp->CharArrayList.rend());
      s.reserve();
      revList.addNode(s, 0);
      temp = temp->next;
   }
   return revList;
}
ConcatStringList::~ConcatStringList() {
   cout << "\n";
   cout << "-----END------\n";
}