#include <iostream>
using namespace std;

struct ListNode{
    int val;
    ListNode *next;
    ListNode(int x) : val(x){}
};

ListNode* createList(int n){
    ListNode dummy(-1);
    ListNode *p = &dummy;
    for(int i = 0; i < n; ++i){
        ListNode *t = new ListNode(i);
        p->next = t;
        p = p->next;
    }
    return dummy.next;
}



int main()
{
    return 0;
}
