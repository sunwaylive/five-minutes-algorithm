#include <iostream>
using namespace std;

struct ListNode{
    int val;
    ListNode *next;
    ListNode(int x = 0) : val(x), next(NULL){}
};

class HashTable{
public:
    HashTable(int len);
    ~HashTable();

    int hash(int key);
    bool insert(int key);
    bool search(int key, int &addr);
private:
    ListNode* (*m_elems);
    int m_len;
};

HashTable::HashTable(int len){
    m_len = len;
    m_elems = new ListNode*[m_len];
    for(int i = 0; i < m_len; ++i){
        m_elems[i] = new ListNode();
    }
}

HashTable::~HashTable(){
    for(int i = 0; i < m_len; ++i){
        ListNode *h = m_elems[i];
        while(h != NULL){
            ListNode *t = h;
            h = h->next;
            delete t;
        }
    }
}

int HashTable::hash(int key){
    return key % m_len;
}

bool HashTable::insert(int key){
    int addr = hash(key);
    ListNode *newNode = new ListNode(key);
    newNode->next = m_elems[addr]->next;
    m_elems[addr]->next = newNode;
    return true;
}

bool HashTable::search(int key, int &addr){
    addr = hash(key);
    ListNode *p = m_elems[addr]->next;
    while(p != NULL){
        if(p->val == key) return true;
        p = p->next;
    }
    return false;
}

int main(){
    int a[12] = {12, 67, 56, 16, 25, 37, 22, 29, 15, 47, 48, 34};
    HashTable map(50);
    for(int i = 0; i < 12; ++i){
        map.insert(a[i]);
    }
    int addr;
    cout<<map.search(56, addr)<<endl;
    cout<<map.search(25, addr)<<endl;
    cout<<map.search(1, addr)<<endl;
    return 0;
}
