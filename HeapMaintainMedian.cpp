#include <iostream>
#include <queue>

using namespace std;

class MidFinder {
public:
    void AddNum(int num) {
        // the size of max heap doesn't change, min heap size add one
        // cool codes!
        m_max_heap.push(num);
        m_min_heap.push(m_max_heap.top());
        m_max_heap.pop();

        if (m_min_heap.size() > m_max_heap.size()) {
            m_max_heap.push(m_min_heap.top());
            m_min_heap.pop();
        }
    }

    float FindMedian() {
        if (m_max_heap.size() == m_min_heap.size()) {
            return (m_max_heap.top() + m_min_heap.top()) / 2.0f;
        } else {
            // only one possibility, min heap size is one larger
            return m_min_heap.top();
        }
    }

private:
    priority_queue<int> m_max_heap;
    priority_queue<int, vector<int>, greater<int> > m_min_heap;
};

int main() {
    MidFinder mf;
    mf.AddNum(2);
    mf.AddNum(3);
    cout << mf.FindMedian() << endl;
    mf.AddNum(4);
    cout << mf.FindMedian() << endl;
    return 0;
}

