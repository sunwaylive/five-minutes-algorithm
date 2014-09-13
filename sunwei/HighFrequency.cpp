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

//************************************************************
//求整数得二进制表示中1的个数
int func(unsigned int i){
    unsigned int temp = i;
    temp = (temp & 0x55555555) + ((temp & 0xaaaaaaaa) >> 1);
    temp = (temp & 0x33333333) + ((temp & 0xcccccccc) >> 2);
    temp = (temp & 0x0f0f0f0f) + ((temp & 0xf0f0f0f0) >> 4);
    temp = (temp & 0x00ff00ff) + ((temp & 0xff00ff00) >> 8);
    temp = (temp & 0x0000ffff) + ((temp & 0xffff0000) >> 16);
    return temp;
}

//************************************************************
//hanoi recursive solutions
void hanoi(int n, char a, char b, char c){
    if(n == 1){
        cout<<"from " << a <<" to " <<c<<endl;
    }else{
        hanoi(n - 1, a, c, b);
        cout<<"from " << a <<" to " <<c <<endl;
        hanoi(n - 1, b, a, c);
    }
}

int main()
{
    cout<<func(0x7f530829) <<endl;
    return 0;
}
