#include <iostream>
using namespace std;

const int MAX_LEN = 10;

class CircularQueue{
public:
    CircularQueue(int len);
    ~CircularQueue();

    bool push(int key);
    void pop();
    int front();
    bool empty();

private:
    int m_front, m_rear;
    int m_len;
    int *m_elems;
};

CircularQueue::CircularQueue(int len){
    m_len = len;
    m_elems = new int[len];
    m_front = 0, m_rear = 0;
}

CircularQueue::~CircularQueue(){
    delete m_elems;
}

bool CircularQueue::push(int key){
    if((m_rear + 1) % m_len == m_front){
        return false;
    }else{
        m_elems[m_rear] = key;
        m_rear = (m_rear + 1) % m_len;
        return true;
    }
}

void CircularQueue::pop(){
    if(m_rear == m_front){
        return;
    }else{
        m_front = (m_front + 1) % m_len;
    }
}

int CircularQueue::front(){
    if(m_rear == m_front){
        return INT_MAX;
    }else{
        return m_elems[m_front];
    }
}

bool CircularQueue::empty(){
    return m_rear == m_front;
}

int main(){
    CircularQueue cq(MAX_LEN);
    int n = 7;
    while(n--){
        int tmp = rand() % 50;
        cq.push(tmp);
        cout<<"push: " <<tmp <<endl;
        cout<<"front: " <<cq.front() <<endl;
    }
    cout<<"********************" <<endl;
    while(!cq.empty()){
        cout<<"front: " <<cq.front() <<endl;
        cq.pop();
    }
    return 0;
}
