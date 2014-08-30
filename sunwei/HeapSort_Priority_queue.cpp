#include <iostream>
#include <queue>
#include <vector>
using namespace std;
struct ListNode{
    int val;
    ListNode(int x) : val(x){}
};

struct cmp{
    bool operator()(ListNode a, ListNode b){
        return a.val > b.val;
    }
};

int main(){
    priority_queue<ListNode, vector<ListNode>, cmp> pq;
    for(int i = 0; i < 10; ++i){
        ListNode tmp(rand() % 100);
        pq.push(tmp);
    }

    while(!pq.empty()){
        ListNode t = pq.top();
        pq.pop();
        cout<<t.val <<endl;
    }

    return 0;
}
