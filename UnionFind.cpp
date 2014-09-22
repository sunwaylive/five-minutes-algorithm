#include <iostream>
#include <fstream>
using namespace std;

const int MAX_NUM = 10;

int cnt = 0;
int id[MAX_NUM];

void init(){
    cnt = MAX_NUM;
    for(int i = 0; i < MAX_NUM; ++i){
        id[i] = i;
    }
}

int find(int p){
    return id[p];
}

bool connected(int p, int q){
    return find(p) == find(q);
}

void myunion(int p, int q){
    int pid = find(p);
    int qid = find(q);
    if(pid == qid) return ;
    for(int i = 0; i < MAX_NUM; ++i){
        if(id[i] == pid)
            id[i] = qid;
    }
    cnt--;
}

int main()
{
    ifstream in;
    in.open("uf.txt");
    cin.rdbuf(in.rdbuf());

    int a, b;
    init();
    while(cin>>a>>b){
        if(connected(a, b)) continue;
        myunion(a, b);
    }
    cout<<cnt<<endl;
    in.close();
    return 0;
}
