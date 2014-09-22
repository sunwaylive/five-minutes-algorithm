#include <iostream>
#include <stack>
using namespace std;

class QueueUsingStack{
public:
    void push(int key);
    int front();
    void pop();
    bool empty();

private:
    stack<int> in_stk;
    stack<int> out_stk;
};

void QueueUsingStack::push(int key){
    in_stk.push(key);
}

void QueueUsingStack::pop(){
    if(!out_stk.empty()){
        out_stk.pop();
    }else{
        while(!in_stk.empty()){
            out_stk.push(in_stk.top());
            in_stk.pop();
        }
        if(!out_stk.empty()){
            out_stk.pop();
        }
    }
}

int QueueUsingStack::front(){
    if(!out_stk.empty()){
        return out_stk.top();
    }else{
        while(!in_stk.empty()){
            out_stk.push(in_stk.top());
            in_stk.pop();
        }

        if(!out_stk.empty()){
            return out_stk.top();
        }else{
            return INT_MAX;
        }
    }
}

bool QueueUsingStack::empty(){
    return in_stk.empty() && out_stk.empty();
}

int main()
{
    QueueUsingStack qus;
    for(int i = 0; i < 10; ++i){
        qus.push(i);
    }
    while(!qus.empty()){
        cout<<qus.front() <<endl;
        qus.pop();
    }
    return 0;
}
