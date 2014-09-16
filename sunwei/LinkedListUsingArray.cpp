#include <iostream>
using namespace std;

struct Node{
    int val;
    int next;
};

class ArrayLinkedList{
public:
    ArrayLinkedList(int cap){
        if(cap == 0) return;

        m_capacity = cap;
        m_elems = new Node[m_capacity]();
        m_head = cap;
        m_available = 0;
        m_length = 0;

        for(int i = 0; i < m_capacity - 1; ++i){
            m_elems[i].next = i + 1;
        }
        m_elems[m_capacity - 1].next = INT_MAX;//最后一个元素的next为INT_MAX;
    }

    ~ArrayLinkedList(){
        delete[] m_elems;
    }

    //insert a element before the element at pos;
    void insertValAt(int pos, int val){
        if(pos >= m_length) return;

        //available 管理可用空间
        int cur_avail = m_available;
        m_elems[m_available].val = val;
        m_available = m_elems[m_available].next;

        //管理已使用空间
        int prev = m_head;
        if(pos == 0){
            m_elems[cur_avail].next = prev;
            m_head = cur_avail;
            m_length++;
            return;
        }else{
            int t = m_head;
            while(--pos){
                t = m_elems[t].next;
            }
            //add a element at the available pos;
            m_elems[cur_avail].next = t;
            m_elems[t].next = cur_avail;
        }
    }

    void delAt(int pos){
        if(pos >= m_length) return;

        int cur_del;
        if(pos == 0){
            cur_del = m_head;
            m_head = m_elems[m_head].next;
            m_length--;
            m_elems[cur_del].next = m_available;
            m_available = cur_del;
        }else{
            int prev_to_del = m_head;
            while(--pos){
                prev_to_del = m_elems[prev_to_del].next;
            }
            //把to_del加到可用空间中去
            int to_del = m_elems[prev_to_del].next;
            m_elems[to_del].next = m_available;
            m_available = to_del;
            //删除结点
            m_elems[prev_to_del].next = m_elems[to_del].next;
        }
    }


private:
    int m_capacity;
    Node *m_elems;
    int m_available;
    int m_head;
    int m_length;
};



int main()
{
    //代码未测试，不一定准确，Pay attention,仅提供一个思路
    return 0;
}
