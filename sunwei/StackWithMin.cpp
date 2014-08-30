#include <iostream>
#include <stack>
using namespace std;

class StackWithMin{
public:
    void push(int key){
        val_stk.push(key);
        if(min_stk.empty() || key <= min_stk.top()){
            min_stk.push(key);
        }
    }

    void pop(){
        if(!val_stk.empty()){
            int t = val_stk.top();
            val_stk.pop();

            if(!min_stk.empty() && t <= min_stk.top()){
                min_stk.pop();
            }
        }
    }

    int top(){
        if(!val_stk.empty()){
            return val_stk.top();
        }else{
            return INT_MAX;
        }
    }
    int getMin(){
        if(!min_stk.empty()){
            return min_stk.top();
        }else{
            return INT_MAX;
        }
    }

private:
    stack<int> val_stk;
    stack<int> min_stk;
};

int main()
{
    StackWithMin swm;
    for(int i = 0; i < 10; ++i){
        int tmp = rand() % 20;
        swm.push(tmp);
        cout<<"push: " <<tmp <<endl;
        cout<<"top: " <<swm.top() <<endl;
        cout<<"min: " <<swm.getMin() <<endl;
    }
    return 0;
}
