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

//小根堆的自上往下的筛选算法
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
    h->elems[i] = tmp;
    return;
}

//小根堆的自下往上筛选法
void heap_sift_up(const heap_t *h, const int start)
{
    int j = start;
    int i = (j - 1) / 2;
    const int tmp = h->elems[start];
    while(j > 0){
        if(h->elems[i] < tmp){
            break;
        }else{
            h->elems[j] = h->elems[i];
            j = i;
            i = (i - 1) / 2;
        }
    }
    h->elems[j] = tmp;
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

int main()
{
    int a[] = {2, 0, 3, 4, 5, 6, 1, 9, 7, 8};
    heap_sort(a, 10);
    for(int i = 0; i < 10; ++i)
        cout<<a[i]<<" ";
    cout<<endl;
    return 0;
}
