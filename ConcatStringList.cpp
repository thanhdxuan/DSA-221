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
   refList.sort();
   return temp;
}

ConcatStringList ConcatStringList::subString(int from, int to) const {
   checkIndex(from);
   //check index for "to" in subString function
   if (to < 0 || to > this->sizeL) {
      throw out_of_range("Index of string is invalid!");
   }
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
   refList.sort();
   delStrList.add(*newNode);
   delStrList.checkNdel();
   refList.check();
   this->count = 0;
   this->head = nullptr;
   this->tail = nullptr;
   this->sizeL = 0;
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
   if (newNode->val == 0) return;
   RefNode* curr = headR;
   RefNode* prev = headR;
   if (headR == nullptr) {
      headR = tailR = newNode;
      this->length++;
      return;
   }
   //if (new value <= head value or head value == 0) -> insert at head
   if (newNode->val <= headR->val || headR->val == 0) {
      newNode->next = headR;
      headR = newNode;
      this->length++;
      return;
   }

   //else if (new value  < head value), traverse and insert before 0
   while (curr && curr->val != 0) {
      if (newNode->val <= curr->val) {
         newNode->next = curr;
         prev->next = newNode;
         this->length++;
         return;
      }
      if (prev->next == curr) prev = prev->next;
      curr = curr->next;
   }
   // else -> insert at tail
   if (curr == nullptr) {
      tailR->next = newNode;
      tailR = newNode;
      this->length++;
   }
   else {
      newNode->next = curr;
      prev->next = newNode;
      this->length++;
   }
   
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
void ConcatStringList::DeleteStringList::delAt(int index) {
 if (index < 0 || index >= length) { 
         throw std::out_of_range("");
      }
      if (index == 0) {
         DelStrNode* temp = headD;
         headD = headD ->next;
         temp->next = nullptr;
         delete temp;
         length--;
         return;
      }
      else if (index == length - 1) {
         DelStrNode* temp = headD;
         while (temp->next->next != nullptr) {
            temp = temp->next;
         }
         tailD = temp;
         temp = temp->next;
         tailD->next = nullptr;
         delete temp;
         length--;
         return;
      }
      else {
         DelStrNode* prev = headD;
         DelStrNode* curr = headD;
         for (int i = 0; i < length; i++) {
            if (i == index - 1) {
               curr = curr->next;
               prev->next = curr->next;
               curr->next = nullptr;
               delete curr;
               length--;
               return;
            }
            prev = prev->next;
            curr = curr->next;
         }
      }
}
void ConcatStringList::DeleteStringList::checkNdel() {
   //check if sum of head and tail == 0 -> delete between head and tail
   //delete this node
   DelStrNode* prev = this->headD;
   DelStrNode* temp = this->headD;
   while (temp) {
      int sum = temp->headRef->val + temp->tailRef->val;
      if (sum == 0) {
         if (temp->headRef->refAdrs == nullptr) {}
         else if (temp->headRef->refAdrs == temp->tailRef->refAdrs) {
            delete temp->headRef->refAdrs;
         }
         else {
            CharArrayNode* h = temp->headRef->refAdrs;
            CharArrayNode* t = temp->tailRef->refAdrs;
            while (h && h->size != 0) {
               CharArrayNode* p = h;
               h = h->next;
               delete p;
            }
            h = nullptr;
            t = nullptr;
         }
         temp->headRef->refAdrs = nullptr;
         temp->tailRef->refAdrs = nullptr;
         //delete this node
         if (temp == headD) { //delete at head
            headD = headD->next;
            delete temp;
            temp = headD;
            prev = headD;
            length--;
            continue;
         }
         else if (temp == tailD) {
            tailD = prev;
            tailD->next = nullptr;
            delete temp;
            length--;
            return;
         }
         else {
            prev->next = temp->next;
            delete temp;
            temp = prev->next;
            length--;
            continue;
         }

      }
      if (temp != headD) prev = prev->next;
      temp = temp->next;
   }
}

void ConcatStringList::ReferencesList::check() {
   RefNode* temp = this->headR;
   while (temp) {
      if (temp->val != 0) return;
      temp = temp->next;
   }
   this->~ReferencesList();
}

ConcatStringList::ReferencesList::RefNode* ConcatStringList::ReferencesList::
swap(RefNode* p1, RefNode* p2) {
   RefNode* temp = p2->next;
   p2->next = p1;
   p1->next = temp;
   return p2;
}
void ConcatStringList::ReferencesList::sort() {
   if (headR == nullptr || length == 1) return;
   //move zeros
   RefNode** head_ref = &headR;
   RefNode* temp = headR->next, *prev = headR;
   int count = 0;
   //move non-zeros to begin
   while (prev) {
      if (prev->val == 0) {
         count++;
      }
      prev = prev->next;
   }
   //reset prev
   prev = headR;
   if (count != 0) {
      while (temp) {
         if (temp->val != 0) {
            RefNode* curr = temp;
            temp = temp->next;
            prev->next = temp;
            //move to begin
            if (curr == tailR) { tailR = prev; }
            curr->next = *head_ref;
            *head_ref = curr;
         }
         else {
            prev = temp;
            temp = temp->next;
            count++;
         }
      }
   }
   //sort non-zero elements
   int rL = length - count;
   for (int k = 0; k < rL; k++) {
      head_ref = &headR;
      int swapped = 0;
      for (int i = 0; i < rL - k - 1; i++) {
         RefNode* p1 = *head_ref;
         RefNode* p2 =  p1->next;
         if (p1->val > p2->val && p1->val != 0 && p2->val != 0) { //swap
            
            //update head_ref
            if (p2->next == nullptr) {
               
            }
            *head_ref = swap(p1, p2);
            swapped = 1;
         }
         head_ref = &(*head_ref)->next;
      }
      if (swapped == 0) break;
   }
}