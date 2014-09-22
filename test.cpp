#include <iostream>
using namespace std;

class M{
public:
    M(){
        cout<<"1" <<endl;
    }
    M(int a){
        cout<<"2" <<endl;
    }
    //M(int a = 1){
    //  cout<<"2" <<endl;
    //}
};

int main(){
    M *tmp = new M;
    M *tmp2 = new M(2);
    return 0;
}
