#include <iostream>
#include <cassert>
using namespace std;

void findMost1(int *a, int n, int *ans){
    assert( a != NULL && ans != NULL);
    int candidate[1] = { INT_MAX };
    int cnt[1] = {0};
    for(int i = 0; i < n; ++i){
        if(a[i] == candidate[0]) cnt[0]++;
        else if(cnt[0] == 0) { candidate[0] = a[i]; cnt[0]++; }
        else{
            cnt[0]--;
        }
    }
    ans[0] = candidate[0];
}

void findMost2(int *a, int n, int *ans){
    assert(a != NULL && ans != NULL);
    int candidates[2] = {INT_MAX, INT_MAX};
    int cnt[2] = {0, 0};
    for(int i = 0; i < n; ++i){
        if(a[i] == candidates[0]) cnt[0]++;
        else if(a[i] == candidates[1]) cnt[1]++;
        else if(0 == cnt[0]) { candidates[0] = a[i]; cnt[0]++; }
        else if(0 == cnt[1]) { candidates[1] = a[i]; cnt[1]++; }
        else{
            cnt[0]--, cnt[1]--;
        }
    }
    ans[0] = candidates[0];
    ans[1] = candidates[1];
}

bool findMost3(int *a, int n, int *ans){
    int candidates[3] = {INT_MAX, INT_MAX, INT_MAX};
    int cnt[3] = {0, 0, 0};
    for(int i = 0; i < n; ++i){
        if(a[i] == candidates[0]) cnt[0]++;
        else if(a[i] == candidates[1]) cnt[1]++;
        else if(a[i] == candidates[2]) cnt[2]++;
        else if(cnt[0] == 0) { candidates[0] = a[i]; cnt[0]++; }
        else if(cnt[1] == 0) { candidates[1] = a[i]; cnt[1]++; }
        else if(cnt[2] == 0) { candidates[2] = a[i]; cnt[2]++; }
        else{
            cnt[0]--, cnt[1]--, cnt[2]--;
        }
    }
    ans[0] = candidates[0];
    ans[1] = candidates[1];
    ans[2] = candidates[2];
}

int main()
{
    int a[] = {1, 1, 1, 2, 2, 2, 4, 5, 5, 5};
    int ans[3];
    findMost3(a, 10, ans);
    cout<<ans[0]<<endl;
    cout<<ans[1]<<endl;
    cout<<ans[2]<<endl;
    return 0;
}
