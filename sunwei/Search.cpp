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
    int a[] = {0, 1, 4, 5, 6, 7, 8};
    int b[] = {0, 1, 2, 3, 4, 5, 6, 7, 8};
    const int m = sizeof(a) / sizeof(a[0]);
    const int n = sizeof(b) / sizeof(b[0]);
    cout<<m<<" "<<n<<endl;
    cout<<findMedianSortedArrays(a, m, b, n)<<endl;;
    cout<<binary_search(a, 0, n, 4) <<endl;
    return 0;
}
