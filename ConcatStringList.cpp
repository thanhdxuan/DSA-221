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
   refList.addRefAt(*this->head, 1);
   refList.addRefAt(*otherS.tail, 1);
   
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
      //ref
      ReferencesList::RefNode* pR = new ReferencesList::RefNode(2, subList.head);
      refList.add(*pR);
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
   //ref
   ReferencesList::RefNode* pR = new ReferencesList::RefNode(1, subList.head);
   ReferencesList::RefNode* pR1 = new ReferencesList::RefNode(1, subList.tail);
   refList.add(*pR);
   refList.add(*pR1);
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
   //ref
   if (revList.head == revList.tail) {
      ReferencesList::RefNode* pR = new ReferencesList::RefNode(2, revList.head);
      refList.add(*pR);
   }
   ReferencesList::RefNode* pR = new ReferencesList::RefNode(1, revList.head);
   ReferencesList::RefNode* pR1 = new ReferencesList::RefNode(1, revList.tail);
   refList.add(*pR);
   refList.add(*pR1);
   return revList;
}

ConcatStringList::~ConcatStringList() {
   DeleteStringList::DelStrNode* newNode = new DeleteStringList::DelStrNode (
      refList.addRefAt(*this->head, -1), 
      refList.addRefAt(*this->tail, -1)
   );
   delStrList.add(*newNode);
   delStrList.checkNdel();
   refList.check();
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
ConcatStringList::ReferencesList::RefNode& ConcatStringList::ReferencesList::addRefAt(const CharArrayNode &node, int value) {
   RefNode* temp = headR;
   while (temp) {
      if (temp->refAdrs == &node) {
         temp->val += value;
         return *temp;
      }
      temp = temp->next;
   }
   return *temp;
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

//additional
void ConcatStringList::DeleteStringList::add(const DelStrNode &other) {
   DelStrNode* newNode = new DelStrNode(other);
   if (headD == nullptr) {
      headD = tailD = newNode;
      this->length++;
      return;
   }
   tailD->next = newNode;
   tailD = newNode;
   this->length++;
}

void ConcatStringList::DeleteStringList::checkNdel() {
   DelStrNode* temp = this->headD;
   while (temp) {
      int sum = temp->headRef->val + temp->tailRef->val;
      if (sum == 0) {
         if (temp->headRef->refAdrs == nullptr) {
            return;
         }
         else if (temp->headRef->refAdrs == temp->tailRef->refAdrs) {
            delete temp->headRef->refAdrs;
         }
         else {
            CharArrayNode* h = temp->headRef->refAdrs;
            CharArrayNode* t = temp->tailRef->refAdrs;
            while (h != t) {
               CharArrayNode* p = h;
               delete p;
               h = h->next;
            }
            delete t;
         }
         temp->headRef->refAdrs = nullptr;
         temp->tailRef->refAdrs = nullptr;
      }
      temp = temp->next;
   }
}

void ConcatStringList::ReferencesList::check() {
   RefNode* temp = this->headR;
   while (temp) {
      if (temp->val != 0) return;
      temp = temp->next;
   }
   while (headR) {
      temp = headR;
      headR = headR->next;
      delete temp;
   }
   this->headR = nullptr;
   this->tailR = nullptr;
   this->length = 0;
}