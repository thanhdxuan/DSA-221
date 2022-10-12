#ifndef __CONCAT_STRING_LIST_H__
#define __CONCAT_STRING_LIST_H__

#include "main.h"

class ConcatStringList {
public:
    class ReferencesList; // forward declaration
    class DeleteStringList; // forward declaration
    class CharArrayNode;
private:
    CharArrayNode *head;
    CharArrayNode *tail;
    int sizeL;
    int count;
public:
    static ReferencesList refList;
    static DeleteStringList delStrList;


public:
    ConcatStringList();
    ConcatStringList(CharArrayNode* h, CharArrayNode* t, int s, int c): head(h), tail(t), sizeL(s), count(c) {}
    ConcatStringList(const char *);
    int length() const;
    char get(int index) const;
    CharArrayNode* getPtr(int index, int &newIdx) const; //additional
    void addNode(const string &s);
    void addNode(const string &s, int index);
    int indexOf(char c) const;
    std::string toString() const;
    ConcatStringList concat(const ConcatStringList & otherS) const;
    ConcatStringList subString(int from, int to) const;
    ConcatStringList reverse() const;
    void checkIndex(int index) const;
    ~ConcatStringList();

public:
    class ReferencesList {
        public: 
            class RefNode;
        public:
            int length;
            RefNode* headR;
            RefNode* tailR;
        public:
            ReferencesList(): length(0), headR(nullptr), tailR(nullptr) {}
            ~ReferencesList() {
                RefNode* temp = headR;
                while (headR) {
                    temp = headR;
                    headR = headR->next;
                    delete temp;
                }
                headR = nullptr;
                tailR = nullptr;
                length = 0;
            }
            int size() const;
            int refCountAt(int index) const;
            void addRefAt(int index, int value);
            RefNode& addRefAt(const CharArrayNode &node, int value);
            // void addRefAt(const CharArrayNode &node, int value);
            void add(const RefNode &other); 
            void sort();
            RefNode* swap(RefNode* p1, RefNode* p2);
            std::string refCountsString() const;
            void checkIndex(int index) const;
            void check();
        public:
            class RefNode {
                public:
                    int val;
                    CharArrayNode* refAdrs;
                    RefNode* next;
                public:
                    RefNode(): val(0), refAdrs(nullptr), next(nullptr) {}
                    RefNode(const RefNode &other): val(other.val), refAdrs(other.refAdrs), next(nullptr) {}
                    RefNode(const int &v, CharArrayNode* node): val(v), refAdrs(node), next(nullptr) {}
                    ~RefNode() {
                        delete refAdrs;
                        val = -1;
                        refAdrs = nullptr;
                        next = nullptr;
                    }
                    bool operator>(const RefNode& other) {
                        return (this->val > other.val);
                    }
                    bool operator<=(const RefNode& other) {
                        return !(this->operator>(other));
                    }
                    bool operator==(const RefNode& other) {
                        return (this->val == other.val && this->refAdrs == other.refAdrs);
                    }
                    bool operator!=(const RefNode& other) {
                        return !(this->operator==(other));
                    }
                    bool operator<(const RefNode& other) {
                        return (this->val < other.val);
                    }
                    bool operator>=(const RefNode& other) {
                        return !(this->operator<(other));
                    }
                    RefNode& operator[](int index) {
                        if (index < 0) {
                            throw std::out_of_range("Invalid index!");
                        }
                        RefNode* temp = this;
                        int i = 0;
                        while (temp) {
                            if (i == index) break;
                            i++;
                            temp = temp->next;
                        }
                        return *temp;
                    }
            };
    };
    class DeleteStringList {
        // TODO: may provide some attributes
        public:
            class DelStrNode;
            // class ReferencesList::RefNode;
        private:
            int length;
            DelStrNode* headD;
            DelStrNode* tailD;
        public:
            int size() const;
            void add(const DelStrNode &other);
            void delAt(int index);
            void checkNdel(); //check if ref == 0
            std::string totalRefCountsString() const;
        public:
            class DelStrNode {
                public:
                    ReferencesList::RefNode* headRef;
                    ReferencesList::RefNode* tailRef;
                    DelStrNode* next;
                public:
                    DelStrNode(): headRef(nullptr), tailRef(nullptr), next(nullptr) {}
                    ~DelStrNode() {}
                    DelStrNode(ReferencesList::RefNode &h, ReferencesList::RefNode &t) {
                        headRef = new ReferencesList::RefNode();
                        tailRef = new ReferencesList::RefNode();
                        headRef = &h;
                        tailRef = &t;
                        next = nullptr;
                    }
            };
    };
    class CharArrayNode {
        public:
            string CharArrayList;
            CharArrayNode* next;
            int size;
        public:
        CharArrayNode() : CharArrayList(""), next(nullptr), size(0) {}
        ~CharArrayNode() {
            size = 0;
        }
        CharArrayNode(const char* ch): next(nullptr) {
            CharArrayList = ch;
            size = CharArrayList.length();
            // while (ch[i] != '\0') {
            //     CharArrayList += ch[i];
            //     i++;
            // }
        }
        CharArrayNode(const string &str) {
            CharArrayList = str;
            next = nullptr;
            size = str.length();
        }
        int getSize() const {
            return size;
        }
    };


};
#endif // __CONCAT_STRING_LIST_H__