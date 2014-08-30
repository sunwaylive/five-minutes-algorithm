#include <iostream>
#include <algorithm>
using namespace std;

int partition(int *a, int start, int end){
    int l = start, r = end - 1;
    const int pivot_val = a[l];
    while(l < r){
        while(l < r && a[r] >= pivot_val) --r;
        a[l] = a[r];
        while(l < r && a[l] <= pivot_val) ++l;
        a[r] = a[l];
    }
    a[l] = pivot_val;
    return l;
}

void quick_sort(int *a, int start, int end){
    if(a == NULL) return ;

    if(start + 1 < end){
        const int pivot_pos = partition(a, start, end);
        quick_sort(a, start, pivot_pos);
        quick_sort(a, pivot_pos + 1, end);
    }
}

//kth_small_num(a, n, 0, n, n - k)<<endl;//n - k position holds k-th biggest number
int kth_small_num(int *a, int n, int start, int end, int k){
    const int pivot_pos = partition(a, start, end);
    if(pivot_pos < k){
        return kth_small_num(a, n, pivot_pos + 1, end, k);
    }else if(pivot_pos > k){
        return kth_small_num(a, n, start, pivot_pos, k);
    }else{
        return a[pivot_pos];
    }
}
//************************************************************
void bubble_sort(int *a, int start, int end){
    if(a == NULL) return ;
    bool exchange;
    for(int i = start; i < end - 1; ++i){
        exchange = false;
        for(int j = end - 1; j > i; --j){
            if(a[j] < a[j - 1]){
                swap(a[j], a[j - 1]);
                exchange = true;
            }
        }
        if(!exchange) return;
    }
}
//************************************************************
void merge(int *a, int *tmp, int start, int mid, int end){
    for(int i = start; i < end; ++i){
        tmp[i] = a[i];
    }
    int i = start, j = mid, k = start;
    while(i < mid && j < end){
        if(tmp[i] < tmp[j]) a[k++] = tmp[i++];
        else a[k++] = tmp[j++];
    }
    while(i < mid) a[k++] = tmp[i++];
    while(j < end) a[k++] = tmp[j++];
}

void merge_sort(int *a, int *tmp, int start, int end){
    if(a == NULL || tmp == NULL) return ;

    if(start + 1 < end){
        int mid = start + ((end - start) >> 1);
        merge_sort(a, tmp, start, mid);
        merge_sort(a, tmp, mid, end); //mid should not plus 1
        merge(a, tmp, start, mid, end);
    }
}

//use merge sort to count reversion count
int mrmerge(int *a, int *tmp, int start, int mid, int end){
    for(int i = start; i < end; ++i)
        tmp[i] = a[i];

    int i = mid - 1, j = end - 1, k = end - 1;
    int cnt = 0;
    while(i >= start && j >= mid){
        if(tmp[i] > tmp[j]){
            cnt += (j - mid + 1);
            a[k--] = tmp[i--];
        }else{
            a[k--] = tmp[j--];
        }
    }

    while(i >= start) a[k--] = tmp[i--];
    while(j >= mid) a[k--] = tmp[j--];
    return cnt;
}

int mrcount(int *a, int *tmp, int start, int end){
    if(a == NULL || tmp == NULL) return 0;
    if(start + 1 < end){
        int mid = start + ((end - start) >> 1);
        int left = mrcount(a, tmp, start, mid);
        int right = mrcount(a, tmp, mid, end);
        int own = mrmerge(a, tmp, start, mid, end);
        return left + right + own;
    }
    return 0;
}

//************************************************************
void selection_sort(int *a, int start, int end){
    if(a == NULL) return ;

    for(int i = start; i < end; ++i){
        int min_idx = i;
        for(int j = i + 1; j < end; ++j){
            if(a[j] < a[min_idx])
                min_idx = j;
        }
        if(min_idx != i){
            swap(a[i], a[min_idx]);
        }
    }
}

//************************************************************
void straight_insert_sort(int *a, int start, int end){
    if(a == NULL) return ;

    int i, j;
    for(i = start + 1; i < end; ++i){
        int tmp = a[i];
        for(j = i - 1; j >= start && tmp < a[j] ; --j)
            a[j + 1] = a[j];

        a[j + 1] = tmp;
    }
}

//************************************************************
void shell_insert(int *a, int start, int end, int gap){
    int i, j;
    for(i = start + gap; i < end; i += gap){
        int tmp = a[i];
        for(j = i - gap; j >= start && tmp < a[j]; j -= gap){
            a[j + gap] = a[j];
        }
        a[j + gap] = tmp;
    }

}

void shell_sort(int *a, int start, int end){
    if(a == NULL) return;

    int gap = end - start;
    while(gap > 1){
        gap = gap / 3 + 1;
        shell_insert(a, start, end, gap);
    }
}

//************************************************************
//array a range: 0 ~ k
void counting_sort(int *a, int n, int k){
    if(a == NULL) return;

    int *count = (int*) malloc(sizeof(int) * (k + 1));
    memset(count, 0, sizeof(int) * (k + 1));

    for(int i = 0; i < n; ++i)
        count[a[i]]++;

    for(int i = 1; i <= k; ++i)
        count[i] += count[i - 1];

    int *b = (int*) malloc(sizeof(int) * n);
    for(int i = n - 1; i >= 0; --i){
        b[count[a[i]] - 1] = a[i];
        count[a[i]]--;
    }

    for(int i = 0; i < n; ++i)
        a[i] = b[i];

    free(count);
    free(b);
}

//this one is much better
void counting_sort2(int *a, int n, int k){
    if(a == NULL) return;

    int *count = new int[k + 1]();
    for(int i = 0; i < n; ++i)
        count[a[i]]++;

    int j = 0;
    for(int i = 0; i <= k; ++i){
        while(count[i]-- > 0){
            a[j++] = i;
        }
    }

    delete[] count;
}

//************************************************************
//n: array number, rm: radius max, d: d-th digit
void radix_counting_sort(int *a, int n, int radius_max, int d){
    int *count = (int*) malloc(sizeof(int) * (radius_max + 1));
    memset(count, 0, sizeof(int) * (radius_max + 1));
    int *b = (int*)malloc(sizeof(int) * n);

    for(int i = 0; i < n; ++i){
        int digit = (a[i] >> (d - 1)) & 1;
        count[digit]++;
    }

    for(int i = 1; i <= radius_max; ++i)
        count[i]+= count[i - 1];

    for(int i = n - 1; i >= 0; --i){
        int digit = (a[i] >> (d - 1)) & 0x1;
        b[count[digit] - 1] = a[i];
        count[digit]--;
    }

    for(int i = 0; i < n; ++i)
        a[i] = b[i];

    free(count);
    free(b);
}

//d: 最大2进制的位数
void radix_sort(int *a, int n, int d){
    if(a == NULL) return ;

    for(int i = 1; i <= d; ++i){
        radix_counting_sort(a, n, 1, i);
    }
}

int main(){
    int a[] = {3, 5, 1, 4, 5, 6};
    const int n = sizeof(a) / sizeof(a[0]);
    counting_sort2(a, n, 6);
    for(int i = 0; i < n; ++i)
        cout<<a[i] <<" ";
    cout<<endl;
    return 0;
}
