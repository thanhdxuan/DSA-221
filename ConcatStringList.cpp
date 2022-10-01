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
   //ref
   ReferencesList::RefNode* pR = new ReferencesList::RefNode(2,head); // head = 1, tail = 1
   refList.add(*pR);
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
   if(temp == nullptr) return "";
   while (temp) {
      listStr << temp->CharArrayList;
      temp = temp->next;
   }
   return listStr.str();
}

ConcatStringList ConcatStringList::concat(const ConcatStringList &otherS) const {
   CharArrayNode* t = tail;
   t->next = otherS.head;   
   int sizeTotal = this->sizeL + otherS.sizeL;
   int countTotal = this->count + otherS.count; 
   ConcatStringList temp(this->head, otherS.tail, sizeTotal, countTotal);
   //ref
   ReferencesList::RefNode* pR = new ReferencesList::RefNode(0, head);
   ReferencesList::RefNode* pR_1 = new ReferencesList::RefNode(0, otherS.tail);
   // refList.addRefAt(refList.size() - 1, 1);
   // refList.addRefAt(0, 1);
   refList.addRefAt(*pR, 1);
   refList.addRefAt(*pR_1, 1);
   
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

}

//RefList Method
void ConcatStringList::ReferencesList::checkIndex(int index) const {
   if (index < 0 || index >= this->length) 
      throw out_of_range("Index of references list is invalid!");
}

int ConcatStringList::ReferencesList::size() const {
   return length;
}

int ConcatStringList::ReferencesList::refCountAt(int index) const {
   checkIndex(index);
   RefNode* temp = headR;
   int i = 0;
   while(temp) {
      if (i == index) break;
      i++;
      temp = temp->next;
   }
   return temp->val;
}
std::string ConcatStringList::ReferencesList::refCountsString() const {
   stringstream ss;
   RefNode* temp = headR;
   if (headR == nullptr) {
      ss << "RefCounts[]";
      return ss.str();
   }
   ss << "RefCounts[";
   while(temp) {
      ss << temp->val;
      temp = temp->next;
      temp == nullptr ? ss << "]" : ss << ",";
   }
   return ss.str();
}

void ConcatStringList::ReferencesList::add(const RefNode &other) {
   RefNode* newNode = new RefNode(other);
   if (headR == nullptr) {
      headR = tailR = newNode;
      this->length++;
      return;
   }
   tailR->next = newNode;
   tailR = newNode;
   this->length++;
}

void ConcatStringList::ReferencesList::addRefAt(int index, int value) {
   checkIndex(index);
   RefNode* temp = headR;
   int i = 0;
   while(temp) {
      if (i == index) {
         temp->val += value;
         return;
      }
      i++;
      temp = temp->next;
   }
}
void ConcatStringList::ReferencesList::addRefAt(const RefNode &node, int value) {
   RefNode* temp = headR;
   while (temp) {
      if (temp->refAdrs == node.refAdrs) {
         temp->val += value;
         return;
      }
      temp = temp->next;
   }
}
//DelStringList
int ConcatStringList::DeleteStringList::size() const {
   return this->length;
}

std::string ConcatStringList::DeleteStringList::totalRefCountsString() const {
   if (headD == nullptr) return "TotalRefCounts[]";
   int count = 0;
   DelStrNode* temp = headD;
   while(temp) {
      if (temp->headRef == temp->tailRef) count += temp->headRef->val;
      else count += (temp->headRef->val + temp->tailRef->val); 
      temp = temp->next;
   }
   string s = "TotalRefCounts[" + to_string(count) + "]";
   return s;
}
