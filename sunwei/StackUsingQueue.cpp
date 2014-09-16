#include <iostream>
#include <queue>

using namespace std;

class StackUsingQueue{
public:
    void push(int x);
    void pop();
    int top();
private:
    queue<int> que1;
    queue<int> que2;

}

void StackUsingQueue::push( int x )
{
    if (!que1.empty())
    {
        que1.push(x);
    }
    else if(!que2.empty())
    {
        que2.push(x);
    }
    else
    {
        que1.push(x);
    }
}

void StackUsingQueue::pop()
{
    if (!que1.empty())
    {
        int tmp;
        tmp = que1.front();
        que1.pop();
        while (!que1.empty())
        {
            que2.push(tmp);
            tmp = que1.front();
            que1.pop();
        }
    }
    else if (!que2.empty())
    {
        int tmp;
        tmp = que2.front();
        que2.pop();
        while (!que2.empty())
        {
            que1.push(tmp);
            tmp = que2.front();
            que2.pop();
        }
    }
}

int StackUsingQueue::top()
{
    if (!que1.empty())
    {
        int tmp;
        while (!que1.empty())
        {
            tmp = que1.front();
            que1.pop();
            que2.push(tmp);
        }
        return tmp;
    }
    else if (!que2.empty())
    {
        int tmp;
        while (!que2.empty())
        {
            tmp = que2.front();
            que2.pop();
            que1.push(tmp);
        }
        return tmp;
    }
    else
    {
        return INT_MAX;
    }
}
int main()
{
    return 0;
}
