#include <iostream>
#include <cstring>
#include <vector>
using namespace std;

//longest common substring
int lcs(const string &txt, const string &query){
    if(txt.empty() || query.empty()) return 0;

    int t_len = txt.length();
    int q_len = query.length();
    vector<int> tmp(t_len);
    vector<int> arr(tmp);;
    int max_length = 0;
    for(int i = 0; i < q_len; ++i){
        string s = query.substr(i, 1);
        arr.assign(t_len, 0);
        for(int j = 0; j < t_len; ++j){
            if(txt.compare(j, 1, s) == 0){
                if(j == 0) {
                    arr[j] = 1;
                } else{
                    arr[j] = tmp[j - 1] + 1;
                }

                if(arr[j] > max_length){
                    max_length = arr[j];
                }
            }
        }
        tmp.assign(arr.begin(), arr.end());
    }
    return max_length;
}

int main(){
    string text = "acaccbabb";
    string query = "acbac";
    cout<<lcs(text, query)<<endl;
    return 0;
}
