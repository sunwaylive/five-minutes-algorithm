#include <iostream>
#include <queue>

using namespace std;

int main()
{
    priority_queue<int, vector<int>, less<int> > max_heap;
    priority_queue<int, vector<int>, greater<int> > min_heap;
    int x;
    double mid = INT_MAX;
    while(cin>>x && x){
        if(mid == INT_MAX){
            max_heap.push(x);
            mid = x;
            cout<<"mid is: " <<mid <<endl;
            continue;
        }

        if(x <= mid) max_heap.push(x);
        else min_heap.push(x);

        int left = max_heap.size();
        int right = min_heap.size();
        int tmp = 0;

        if(left == right){
            mid = ((max_heap.top() + min_heap.top()) / 2.0f);
            cout<<"mid is: " <<mid <<endl;
        }else if(abs(left - right) == 1){
            tmp = (left > right) ? max_heap.top() : min_heap.top();
            mid = tmp;
            cout<<"mid is: " <<mid <<endl;
        }else if(left - right >= 2){
            tmp = max_heap.top(); max_heap.pop();
            min_heap.push(tmp);
            mid = ((max_heap.top() + min_heap.top()) / 2.0f);
            cout<<"mid is: " <<mid <<endl;
        }else if(right - left >= 2){
            tmp = min_heap.top(); min_heap.pop();
            max_heap.push(tmp);
            mid = ((max_heap.top() + min_heap.top()) / 2.0f);
            cout<<"mid is: " <<mid <<endl;
        }
    }
}
