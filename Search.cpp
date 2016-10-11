#include <iostream>
using namespace std;

int binary_search(int *a, int start, int end, int target){
    if(a == NULL) return -1;
    int l = start, r = end;
    while(l < r){
        const int mid = l + ((r - l) >> 1);
        if(a[mid] > target){
            r = mid;
        }else if(a[mid] < target){
            l = mid + 1;
        }else{
            return mid;
        }
    }
    return -1;
}

int binary_search_recursive(int *a, int start, int end, int target) {
    if(a == NULL) {
        return -1;
    }

    if (start >= end) {
        return -1;
    }

    int mid = start + (end - start) / 2;
    if (a[mid] > target) {
        return binary_search_recursive(a, start, mid, target);
    } else if (a[mid] < target) {
        return binary_search_recursive(a, mid + 1, end, target);
    } else {
        return mid;
    }
}

//************************************************************
int binary_search_rotated(int *a, int start, int end, int target){
    if(a == NULL) return -1;

    int l = start, r = end;
    while(l < r){
        int m = l + ((r - l) >> 1);
        if(a[m] == target) return m;

        if(a[m] >= a[l]){
            if(target >= a[l] && target <= a[m]){
                r = m;
            }else{
                l = m + 1;
            }
        }else if(a[m] <= a[r - 1]){
            if(target >= a[m] && target <= a[r - 1]){
                l = m + 1;
            }else{
                r = m;
            }
        }
    }
    return -1;
}

//************************************************************
int findKth(int *a, int m, int a_start, int *b, int n, int b_start, int k){
    if(a_start >= m) return b[b_start + k - 1];
    if(b_start >= n) return a[a_start + k - 1];
    if(k == 1) return min(a[a_start], b[b_start]);
    int a_val = (a_start + k / 2 - 1 < m) ?
        a[a_start + k / 2 - 1] : INT_MAX;
    int b_val = (b_start + k / 2 - 1 < n) ?
        b[b_start + k / 2 - 1] : INT_MAX;
    if(a_val < b_val){
        return findKth(a, m, a_start + k / 2, b, n, b_start, k - k / 2);
    }else{
        return findKth(a, m, a_start, b, n, b_start + k / 2, k - k / 2);
    }
}

double findMedianSortedArrays(int *a, int m, int *b, int n){
    int len = m + n;
    if( len & 0x1){
        return findKth(a, m, 0, b, n, 0, len / 2 + 1);
    }else{
        return (findKth(a, m, 0, b, n, 0, len / 2) + findKth(a, m, 0, b, n, 0, len / 2 + 1)) >> 1;
    }
}

//************************************************************

int main()
{
    int a[] = {4, 5, 6, 1, 2, 3};
    int n = sizeof(a) / sizeof(*a);
    cout<<binary_search_rotated(a, 0, n, 14) <<endl;

    int b[] = {1, 2, 3, 4, 5};
    int nb = sizeof(b) / sizeof(*b);
    cout <<"bs recursive: " << binary_search_recursive(b, 0, 5, 3) <<endl;
    return 0;
}
