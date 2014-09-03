#include <iostream>
#include <vector>
using namespace std;


//comes from programming pearls
void randomShuffle(int a[], int n){
    if(a == NULL) return;

    for(int i = 0; i < n; ++i){
        int tmp = rand() % (n - i);
        swap(a[tmp], a[n - 1 - i]);
    }
}

//************************************************************
//蓄水池抽样
//http://handspeaker.iteye.com/blog/1167092
//1 ------k--------i--------N,  N 趋近无穷大, 以k/i的概率选择第i个

vector<int> reservoirSampling(int k){
    vector<int> result;
    //end with -1;
    int i = 0, val;
    while(result.size() < k){
        cin>>val;
        result.push_back(val);
        i++;//i-th number
    }

    //core part
    while(cin>>val){
        if(val == -1)
            return result;
        i++;
        int m = rand() % i;
        if(m < k){
            result[m] = val;
        }
    }
    return result;
}

int main()
{
    int a[] = {1, 2, 3 ,4, 5, 6, 7, 8};
    const int n = sizeof(a) / sizeof(a[0]);
    randomShuffle(a, n);
    for(int i = 0; i < n; ++i)
        cout<<a[i]<<" ";
    cout<<endl;

    cout<<"sample"<<endl;
    int k = 5;
    vector<int> result = reservoirSampling(k);
    for(int i = 0; i < k; ++i){
        cout<<result[i]<<" ";
    }
    cout<<endl;
    return 0;
}
