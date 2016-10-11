#include <iostream>
using namespace std;

struct ListNode{
    int val;
    ListNode *next;
    ListNode(int x) : val(x), next(NULL){}
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
ListNode* insertAtHead(ListNode *head, int val){
    ListNode *newNode = new ListNode(val);
    newNode->next = head;
    return newNode;
}

ListNode* insertAtTail(ListNode *head, int val){
    ListNode dummy(-1);
    dummy.next = head;

    ListNode *p = &dummy;
    while(p->next != NULL){
        p = p->next;
    }
    ListNode *newNode = new ListNode(val);
    p->next = newNode;
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

ListNode* reverse_recur(ListNode *head, ListNode *&new_head) {
    if (head == NULL) {
        return NULL;
    }

    //head keep moving ahead, and arrive at the end node
    if (head->next == NULL) {
        //end of the old list is the new head
        new_head = head;
        return head;
    }

    ListNode *new_tail = reverse_recur(head->next, new_head);
    new_tail->next = head;
    head->next = NULL;
    return head; // this is used as new_tail for the prev function call
}

//************************************************************
//O(1)
bool delNode(ListNode *&head, ListNode *del){
    if(head == NULL || del == NULL) {
        return false;
    }

    if(del->next != NULL) {
        del->val = del->next->val;
        ListNode *tmp = del->next;
        del->next = del->next->next;
        delete tmp;
        return true;
    } else {// the last node
        ListNode dummy(-1);
        dummy.next = head;
        ListNode *prev = &dummy;
        while(prev != NULL && prev->next != del) {
            prev = prev->next;
        }

        if(prev == NULL) {
            return false;
        }

        prev->next =  del->next;
        delete del;
        // must, if del is the head, and there's only one element
        head = dummy.next;
        return true;
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
    if(head == NULL && head->next == NULL) return head;

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
    if(head == NULL) {
        return NULL;
    }

    int cnt = 0;
    ListNode *fast = head, *slow = head;
    while(fast != NULL) {
        fast = fast->next;
        cnt++;
        if(cnt > k){
            slow = slow->next;
        }
    }
    if(cnt < k) return NULL;
    else return slow;
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
    ListNode *h = createList(2);
    ListNode *nh = insertAtHead(h, 100);
    printList(nh);
    ListNode *nh2 = insertAtTail(nh, 200);
    printList(nh2);
    reverse_recur(nh2, nh2);
    printList(nh2);

    int k = 4;
    ListNode *tmp = KthToLast(nh2, k);
    if (tmp == NULL) {
        cout << k << "th to last NULL" <<endl;
    } else {
        cout << k << "th to last value: " << tmp->val << endl;
    }

    return 0;
}
