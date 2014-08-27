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

//************************************************************
ListNode* reverse(ListNode *head){
    ListNode *pre = NULL, *cur = head, *nxt = NULL;
    while(cur != NULL){
        nxt = cur->next;
        cur->next = pre;
        pre = cur;
        cur = nxt;
    }
    return pre;
}

ListNode* reverse_recur(ListNode *list, ListNode *&head){
    if(list == NULL || list->next == NULL){
        head->next = NULL;
        head = list;
        return list;
    }else{
        ListNode *tmp = reverse_recur(list->next, head);
        tmp->next = list;
        return list;
    }
}
// LISTNODE *NH = HEAD;
// REVERSE_RECUR(NH, NH);

//************************************************************
//O(1)
void delNode(ListNode *&head, ListNode *del){
    if(head == NULL || del == NULL) return;

    if(del->next != NULL){
        del->val = del->next->val;
        ListNode *tmp = del->next;
        del->next = del->next->next;
        delete tmp;
    }else{// the last node
        ListNode dummy(-1);
        dummy.next = head;
        ListNode *prev = &dummy;
        while(prev != NULL && prev->next != del)
            prev = prev->next;

        if(prev == NULL) return;
        ListNode *tmp = del;
        prev->next =  del->next;
        delete tmp;
        head = dummy.next;
    }
}

//************************************************************
ListNode* kthNode(ListNode *head, int k){
    if(head == NULL) return NULL;
    while(--k > 0 && head != NULL)
        head = head->next;
    return head;
}

//************************************************************
ListNode* findMid(ListNode *head){
    ListNode *slow = head, *fast = head->next;
    while(fast != NULL && fast->next != NULL){
        fast = fast->next->next;
        slow = slow->next;
    }
    return slow;
}

//************************************************************
ListNode* mergeTwoSortedList(ListNode *h1, ListNode *h2){
    ListNode dummy(-1);
    ListNode *p = &dummy;
    while(h1 != NULL && h2 != NULL){
        if(h1->val < h2->val){
            p->next = h1;
            h1 = h1->next;
        }else{
            p->next = h2;
            h2 = h2->next;
        }
        p = p->next;
    }
    if(h1 != NULL) p->next = h1;
    if(h2 != NULL) p->next = h2;
    return dummy.next;
}

//************************************************************
ListNode* merge(ListNode *h1, ListNode *h2){
    ListNode dummy(-1);
    ListNode *p = &dummy;
    while(h1 != NULL && h2 != NULL){
        if(h1->val < h2->val){
            p->next = h1;
            h1 = h1->next;
        }else{
            p->next = h2;
            h2 = h2->next;
        }
        p = p->next;
    }
    if(h1 != NULL) p->next = h1;
    if(h2 != NULL) p->next = h2;
    return dummy.next;
}

ListNode* sortList(ListNode* head){
    if(head == NULL || head->next == NULL){
        return head;
    }

    ListNode *slow = head, *fast = head->next;
    while(fast != NULL && fast->next != NULL){
        fast = fast->next->next;
        slow = slow->next;
    }
    ListNode *mid = slow;

    ListNode *h1 = head, *h2 = mid->next;
    mid->next = NULL;
    h1 = sortList(h1);
    h2 = sortList(h2);
    return merge(h1, h2);
}

//************************************************************
bool hasCycle(ListNode *head){
    if(head == NULL) return false;

    ListNode *slow = head, *fast = head;
    do{
        if(fast == NULL || fast->next == NULL)
            return false;
        fast = fast->next->next;
        slow = slow->next;
    }while(fast != slow);
    return true;
}

ListNode* detectCycle(ListNode *head){
    if(head == NULL) return NULL;

    ListNode *slow = head, *fast = head;
    do{
        if(fast == NULL || fast->next == NULL)
            return NULL;
        fast = fast->next->next;
        slow = slow->next;
    }while(fast != slow);

    fast = head;
    while(fast != slow){
        fast = fast->next;
        slow = slow->next;
    }
    return fast;
}
//test program:
// ListNode *h1 = createList(10);
// ListNode *tail = h1;
// while(tail != NULL && tail->next != NULL){
//     tail = tail->next;
//  }
// ListNode *kth = kthNode(h1, 3);
// tail->next = kth;
// ListNode *enter = detectCycle(h1);
// cout<<enter->val <<endl;
// cout<<hasCycle(h1) <<endl;

//************************************************************
ListNode* lastKth(ListNode *head, int k){
    if(head == NULL) return NULL;

    ListNode *fast = head;
    while(k-- && fast != NULL){
        fast = fast->next;
    }
    //k > length
    if(fast == NULL && k > 0)
        return NULL;

    ListNode *slow = head;
    while(fast != NULL){
        fast = fast->next;
        slow = slow->next;
    }
    return slow;
}

//************************************************************
void printList(ListNode *head){
    while(head != NULL){
        cout<<head->val <<" ";
        head = head->next;
    }
    cout<<endl;
}

int main()
{
    ListNode *head = createList(10);
    ListNode *kth = lastKth(head, 10);
    cout<<kth->val <<endl;
    return 0;
}
