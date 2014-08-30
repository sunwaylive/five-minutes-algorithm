#include <iostream>
using namespace std;

class HashTable{
public:
    HashTable(int length);
    ~HashTable();

    int hash(int key);
    bool insertLinear(int key);
    bool searchLinear(int key, int &addr);
    bool insertRand(int key);
    bool searchRand(int key, int &addr);
private:
    int *m_elems;
    int m_len;
};

HashTable::HashTable(int len){
    m_len = len;
    m_elems = new int[len]();
    for(int i = 0; i < m_len; ++i){
        m_elems[i] = INT_MAX;
    }
}

HashTable::~HashTable(){
    m_len = 0;
    delete m_elems;
}
int HashTable::hash(int key){
    return key % m_len;
}

bool HashTable::insertLinear(int key){
    int addr = hash(key);
    while(m_elems[addr] != INT_MAX){
        addr = (addr + 1) % m_len;//mod if for cycle
        if(addr == hash(key))
            return false;
    }
    m_elems[addr] = key;
    return true;
}

bool HashTable::searchLinear(int key, int &addr){
    addr = hash(key);
    while(m_elems[addr] != key){
        addr = (addr + 1) % m_len;
        if(addr == hash(key) || m_elems[addr] == INT_MAX)
            return false;
    }
    return true;
}

bool HashTable::insertRand(int key){
    int addr = hash(key);
    while(m_elems[addr] != INT_MAX){
        addr = (addr + rand()) % m_len;
    }
    m_elems[addr] = key;
    return true;
}

bool HashTable::searchRand(int key, int &addr){
    addr = hash(key);
    while(m_elems[addr] != key){
        addr = (addr + rand()) % m_len;
        if(m_elems[addr] == INT_MAX || addr == hash(key))
            return false;
    }
    return true;
}

int main(){
    int a[12] = {12, 67, 56, 16, 25, 37, 22, 29, 15, 47, 48, 34};
    HashTable map(50);
    for(int i = 0; i < 12; ++i){
        map.insertRand(a[i]);
    }
    int addr;
    cout<<map.searchRand(56, addr)<<endl;
    cout<<map.searchRand(25, addr)<<endl;
    cout<<map.searchRand(1, addr)<<endl;
}
