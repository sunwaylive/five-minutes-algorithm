#include <iostream>
using namespace std;

struct heap_t{
    int size;
    int capacity;
    int *elems;
};

heap_t* createHeap(const int capacity)
{
    heap_t *h = (heap_t*)malloc(sizeof(heap_t));
    h->size = 0;
    h->capacity = capacity;
    h->elems = (int*) malloc(sizeof(int) * capacity);
    return h;
}

void heapDestroy(heap_t *h)
{
    free(h->elems);
    free(h);
}

void heap_sift_down(const heap_t *h, const int start)
{
    int i = start, j;
    const int tmp = h->elems[start];

    for(j = 2*i+1; j < h->size; j = 2*i+1){
        //get the bigger child
        //if j = h->size - 1, then no right child of node i, so skip the if
        if(j < h->size - 1
           && h->elems[j+1] > h->elems[j]) j = j + 1;

        if(tmp >= h->elems[j]){
            break;
        }else{
            //elems[j] is maximum, move upward
            h->elems[i] = h->elems[j];
            i = j;
        }
    }
    h->elems[i] = tmp;
}

void heap_sift_up(const heap_t *h, const int start)
{
    int j = start;
    int i = (j - 1) / 2;
    const int tmp = h->elems[start];
    for(; i >= 0; i = (j - 1) / 2){
        if(h->elems[i] > tmp){
            break;
        }else{
            h->elems[j] = h->elems[i];
            j = i;
        }
    }
    h->elems[j] = tmp;
}


void heap_sort(int a[], const int n)
{
    heap_t *h;
    h = createHeap(n);
    int *old_memory = h->elems;
    h->elems = a;
    h->size = n;

    //construct the heap
    int i = (h->size - 2) / 2;
    while(i >= 0){
        heap_sift_down(h, i);
        --i;
    }

    //pop to sort
    for(i = h->size - 1; i > 0; --i){
        swap(h->elems[i], h->elems[0]);
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
        cout<<a[i] <<" ";
    cout<<endl;
    return 0;
}
