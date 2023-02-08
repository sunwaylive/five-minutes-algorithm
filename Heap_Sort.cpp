#include <iostream>
using namespace std;

//typedef int heap_elem_t;

struct heap_t{
    int size;
    int capacity;
    int *elems;
};

heap_t* createHeap(const int capacity)
{
    heap_t *h = (heap_t*) malloc(sizeof(heap_t));
    h->size = 0;
    h->capacity = capacity;
    h->elems = (int*) malloc(capacity * sizeof(int));
    return h;
}

void heapDestroy(heap_t *h)
{
    free(h->elems);
    free(h);
}

//小根堆的自上往下的筛选算法, 通常在删除最大或者最小值得时候使用
//h: 堆对象的指针，  start: 开始的结点的索引
void heap_sift_down(const heap_t *h, const int start)
{
    int i = start, j;
    const int tmp = h->elems[start];

    //j points to the left child of i
    for(j = 2 * i + 1; j < h->size; j = 2 * i + 1){
        //get the smaller child, in order to switch it
        if(j < h->size - 1 &&
           h->elems[j] > h->elems[j+1]) j = j + 1;

        if(tmp <= h->elems[j]) break;
        else{
            //now elems[j] holds the minimum among the three elems
            h->elems[i] = h->elems[j]; //move the minimum one upstairs
            i = j;
        }
    }//end for

    h->elems[i] = tmp; // 考虑极限情况，直接退出循环，tmp必定是赋值给i号位置

    return;
}

//小根堆的自下往上筛选法，通常在插入新元素的时候使用
void heap_sift_up(const heap_t *h, const int start)
{
    int j = start, i = 0; // parent = (child - 1) / 2
    const int tmp = h->elems[start];
    for (i = (j - 1) / 2; i >= 0; i = (j - 1) / 2) {
        if(h->elems[i] < tmp){
            break;
        }else{
            h->elems[j] = h->elems[i];
            j = i;
            i = (j - 1) / 2;
        }
    }

    h->elems[j] = tmp; // 考虑极限情况，直接退出循环，tmp必定是赋值给j号位置
}

void heap_sort(int a[], const int n)
{
    heap_t *h;
    h = createHeap(n);
    //we should delete the memory which is allocated in createHeap()
    int *old_memory = h->elems;
    h->elems = a;
    h->size = n;

    int i = (h->size - 2) / 2;  // h->size - 1 is index, (h->size - 1 - 1) / 2 is its parent
    //自底向上逐步形成最小堆, 从第一个分支节点逆层序遍历，后面的比较每一次都是和3者中另外两个较小的那个比较
    while(i >= 0){
        heap_sift_down(h, i);
        i--;
    }

    //依次取出堆顶
    for(i = h->size - 1; i > 0; --i){
        swap(h->elems[0], h->elems[i]);
        h->size--;
        heap_sift_down(h, 0);
    }

    h->elems = old_memory;
    heapDestroy(h);
}

//updated on Wed Feb 8, 2023
class SmallHeap
{
    bool priorTo(int v1, int v2) { return v1 < v2; }
    
    //上浮, 从下往上调整单个元素
    void swim(vector<int>& heap, int i)
    {
        while (i > 0 && priorTo(heap[i], heap[(i-1)/2]))
        {
            swap(heap[i], heap[(i-1)/2]);
            i = (i-1)/2;
        }
    }
    
    //下沉
    void sink(vector<int>& heap, int i, int N)
    {
        while (2*i+1 <= N)
        {
            //拿到更小的child
            int j = 2*i+1;
            if (j+1 <= N && priorTo(heap[j+1], heap[j]))
            {
                j++;
            }
            
            //父节点小
            if(priorTo(heap[i], heap[j])) break;
            swap(heap[i], heap[j]);
            i = j;
        }
        
    }
}；

int main()
{
    int a[] = {2, 0, 3, 4, 5, 6, 1, 9, 7, 8};
    heap_sort(a, 10);
    for(int i = 0; i < 10; ++i)
        cout<<a[i]<<" ";
    cout<<endl;
    return 0;
}
