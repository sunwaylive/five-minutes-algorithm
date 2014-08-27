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

int main()
{
    int a[] = {0, 1, 4, 5, 6, 7, 8, 9};
    const int n = sizeof(a) / sizeof(a[0]);
    cout<<binary_search(a, 0, n, 4) <<endl;
    return 0;
}
