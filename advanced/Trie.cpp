#include <iostream>
#include <string>
using namespace std;

const int kMaxNum = 26; // adjust according to real cases
struct TrieNode {
    TrieNode* next[kMaxNum];
    int cnt;
};

TrieNode g_mem[1000000]; // using in ACM for saving time
int g_alloc_idx = 0; // current available memory

// ************************************************************
TrieNode* CreateNode() {
    TrieNode *new_node = &g_mem[g_alloc_idx++];
    for (int i = 0; i < kMaxNum; ++i) {
        new_node->next[i] = NULL;
    }
    return new_node;
}

void Insert(TrieNode *root, string str) {
    if (root == NULL) {
        return;
    }

    TrieNode *cursor = root;
    int i = 0;
    while (str[i] != '\0') {
        int c = str[i] - 'a';
        if (cursor->next[c] == NULL) {
            cursor->next[c] = CreateNode();
        }

        // update node data
        cursor->next[c]->cnt++;
        cursor = cursor->next[c];
        i++;
    }
}

int Search(TrieNode *root, string str) {
    if (root == NULL) {
        return 0;
    }

    TrieNode *cursor = root;
    int i = 0;
    while (str[i] != '\0') {
        int c = str[i] - 'a';
        if (cursor->next[c] == NULL) {
            // search ends
            return 0;
        } else {
            // go further
            cursor = cursor->next[c];
            i++;
        }
    }

    return cursor->cnt; // return the node cnt that hold the last char of the query stirng
}

int main() {
    TrieNode *root = CreateNode();
    Insert(root, "inn");
    Insert(root, "int");
    Insert(root, "at");
    Insert(root, "age");
    Insert(root, "adv");
    Insert(root, "ant");
    cout << Search(root, "a") << endl;
    cout << Search(root, "in") << endl;
    cout << Search(root, "ad") << endl;
    return 0;
}
