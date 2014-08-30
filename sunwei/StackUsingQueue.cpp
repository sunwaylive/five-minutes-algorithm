#include <iostream>
#include <queue>
using namespace std;

class StackUsingQueue{
public:
    void push(int key){
        if(!que1.empty()){
            que1.push(key);
        }else if(!que2.empty()){
            que2.push(key);
        }else{
            que1.push(key);
        }
    }

    int top(){
        if(que1.empty()){
            while(que2.size() > 1){
                que1.push(que2.front());
                que2.pop();
            }
            if(!que2.empty()){
                int tmp = que2.front();
                que2.pop();

                que1.push(tmp);
                return tmp;
            }else {
                return INT_MAX;
            }
        }else{
            while(que1.size() > 1){
                que2.push(que1.front());
                que1.pop();
            }
            int tmp = que1.front();
            que1.pop();
            que2.push(tmp);
            return tmp;
        }
    }

    void pop(){
        if(que1.empty()){
            while(que2.size() > 1){
                que1.push(que2.front());
                que2.pop();
            }
            if(!que2.empty()){
                que2.pop();
            }
        }else{
            while(que1.size() > 1){
                que2.push(que1.front());
                que1.pop();
            }
            if(!que1.empty()){
                que1.pop();
            }
        }
    }

    bool empty(){
        return que1.empty() && que2.empty();
    }

private:
    queue<int> que1;
    queue<int> que2;
};

int main()
{
    StackUsingQueue suq;
    for(int i = 0; i < 10; ++i){
        int tmp = rand() % 20;
        suq.push(tmp);
        cout<<"push: " <<tmp<<endl;
        cout<<"top: " <<suq.top() <<endl;
    }

    cout<<"**********************" <<endl;

    while(!suq.empty()){
        cout<<"top: "<<suq.top() <<endl;
        suq.pop();
    }
    return 0;
}
