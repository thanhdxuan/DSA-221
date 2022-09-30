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

    // TODO: may provide some attributes

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
        // TODO: may provide some attributes

        public:
            int size() const;
            int refCountAt(int index) const;
            std::string refCountsString() const;
    };
    class DeleteStringList {
        // TODO: may provide some attributes

        public:
            int size() const;
            std::string totalRefCountsString() const;
    };
    class CharArrayNode {
        // public: 
        //     class CharArrayList;
        public:
            string CharArrayList;
            CharArrayNode* next;
            int size;
        public:
        CharArrayNode() : CharArrayList(""), next(nullptr), size(0) {}
        CharArrayNode(const char* ch): next(nullptr) {
            int i = 0;
            CharArrayList = "";
            while (ch[i] != '\0') {
                CharArrayList += ch[i];
                i++;
            }
            CharArrayList += '\0';
            size = i;
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