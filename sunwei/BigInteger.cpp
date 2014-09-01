#include <iostream>
using namespace std;

const int N = 210;
char str1[N], str2[N];
int num1[N], num2[N], num3[N];
int num4[N * 2];// for multiple

//************************************************************
void add(int num1[], int num2[], int num3[]){
    for(int i = 0; i < N; ++i)
        num3[i] = 0;

    for(int i = 0; i < N; ++i){
        num3[i] = num1[i] + num2[i] + num3[i];//add num3 itself
        if(num3[i] >= 10){
            num3[i] -= 10;
            num3[i + 1]++;//num3 itself store the carry bit
        }
    }
}

//************************************************************
//default num1 >= num2
void sub(int num1[], int num2[], int num3[]){
    for(int i = 0; i < N; ++i)
        num3[i] = 0;

    for(int i = 0; i < N; ++i){
        num3[i] = num1[i] - num2[i] + num3[i];
        if(num3[i] < 0){
            num3[i] += 10;
            num3[i + 1]--;
        }
    }
}

//************************************************************
//O(n^2)
void multiple(int num1[], int num2[], int num3[]){
    for(int i = 0; i < N * 2; ++i)//size of num3 is twice of num1 and num2
        num3[i] = 0;

    for(int i = 0; i <= N; ++i){
        for(int j = 0; j <= N; ++j){
            num3[i + j] = num1[i] * num2[j] + num3[i + j];
            if(num3[i + j] >= 10){
                num3[i + j + 1] += num3[i + j] / 10;
                num3[i + j] %= 10;
            }
        }
    }
}

//O(n)
void multiple2(int num1[], int num2[], int num3[]){

}
//************************************************************
void print(int num[]){
    int i, j;

    for(i = N - 1; i >= 0 && num[i] == 0; --i)
        ;
    if(i == -1){
        cout<<0;
    }else{
        for(j = i; j >= 0; --j){
            cout<<num[j];
        }
    }
    cout<<endl;
}

int main(){
    //initialize
    cin>>str1>>str2;
    memset(num1, 0, sizeof(num1));
    memset(num2, 0, sizeof(num2));
    const int str1_len = strlen(str1);
    const int str2_len = strlen(str2);
    int i, j;
    j = 0;
    for(i = str1_len - 1; i >= 0; --i){
        num1[j++] = str1[i] - '0';
    }
    j = 0;
    for(i = str2_len - 1; i >= 0; --i){
        num2[j++] = str2[i] - '0';
    }

    //1. add
    add(num1, num2, num3);
    print(num3);

    //2. sub
    int sign = strcmp(str1, str2);
    if (sign >= 0){
        sub(num1, num2, num3);
    }else{
        sub(num2, num1, num3);
    }
    if(sign < 0) cout<<"-";
    print(num3);

    //3. multiple
    multiple(num1, num2, num4);
    print(num4);
    return 0;
}
