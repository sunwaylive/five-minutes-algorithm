#include <iostream>
#include <string>
#include <vector>
#include <cmath>
#include <unordered_map>
using namespace std;

//given a array, get all permutations; no duplicates in the array
//https://oj.leetcode.com/problems/permutations/
void permutation_helper(vector<int> &num, vector<vector<int> > &result, vector<int> &path){
    if(path.size() == num.size()){
        result.push_back(path);
    }
    for(int i = 0; i < num.size(); ++i){
        vector<int>::iterator iter = find(path.begin(), path.end(), num[i]);
        if(iter == path.end()){
            path.push_back(num[i]);
            permutation_helper(num, result, path);
            path.pop_back();
        }
    }
}

vector<vector<int> > permutation(vector<int> &num){
    vector<vector<int> > result;
    if(num.empty()) return result;

    sort(num.begin(), num.end());//important!
    vector<int> path;
    permutation_helper(num, result, path);
    return result;
}

//********************************************************************************
//given a array, get all permutations; duplicates exist in the array
//https://oj.leetcode.com/problems/permutations-ii/
void permutation_helper2(vector<int> &num, vector<bool> &visited, vector<vector<int> > &result, vector<int> &path){
    if(path.size() == num.size()){
        result.push_back(path);
    }

    for(int i = 0; i < num.size(); ++i){
        //later half mean: the same state has been searched by the former letter
        if(visited[i] || (i - 1>= 0 && num[i - 1] == num[i] && !visited[i - 1])){
            continue;
        }
        visited[i] = true;
        path.push_back(num[i]);
        permutation_helper2(num, visited, result, path);
        path.pop_back();
        visited[i] = false;
    }
}

vector<vector<int> > permutation2(vector<int> &num){
    vector<vector<int> > result;
    if(num.empty()) return result;

    sort(num.begin(), num.end());//important!
    vector<bool> visited(num.size(), false);
    vector<int> path;
    permutation_helper2(num, visited, result, path);
    return result;
}

//************************************************************
vector<int> next_permutation(vector<int> num){
    if(num.empty()) return num;

    int len = num.size();
    int i = -1;
    for(i = len - 2; i >= 0; --i){
        if(num[i] < num[i + 1])
            break;
    }

    if(i == -1) return num;
    int pivot = i;
    for(i = len - 1; i >= pivot; --i){
        if(num[i] > num[pivot])
            break;
    }
    swap(num[pivot], num[i]);
    reverse(num.begin() + pivot + 1, num.end());
    return num;
}

//************************************************************
//given n:1 ~ 9, find the k-th permutation
string getPermutation(int n, int k){
    const int fac[] = {1, 1, 2, 6, 24, 120, 720, 5040, 40320};//9 numbers, start from 0
    vector<bool> visited(10, false);//1 ~ n

    string ans(n, '0');
    int i, j, t;
    --k;// 前面需要有k-1个排列
    for(i = 0; i < n; ++i){
        t = k / fac[n - 1 -i];//there should be t numbers less than number at i-th position
        //find the t-th unused number
        for(j = 1; j <= n; ++j){
            if(!visited[j]){
                if(t < 0){
                    break;
                }else{
                    --t;
                }
            }//end if
        }//end for
        ans[i] += j;
        visited[j] = true;
    }//end for
    return ans;
}

//************************************************************
//Combination,  is also subsets
//http://answer.ninechapter.com/solutions/subsets/
//no duplicates in number
void subsets_helper(vector<int> &num, vector<vector<int> > &result, vector<int> &path, int pos){
    result.push_back(path);

    for(int i = pos; i < num.size(); ++i){
        path.push_back(num[i]);
        subsets_helper(num, result, path, i + 1);//i 代表当前数加或者不加，i + 1代表考虑下一个数
        path.pop_back();
    }
}

vector<vector<int> > subsets(vector<int> num){
    vector<vector<int> > result;
    if(num.empty()) return result;

    sort(num.begin(), num.end());
    vector<int> path;
    subsets_helper(num, result, path, 0);
    return result;
}

//************************************************************
void subsets_helper2(vector<int> &num, vector<vector<int> > &result, vector<int> &path, int pos){
    result.push_back(path);

    for(int i = pos; i < num.size(); ++i){
        if(i > pos && num[i] == num[i - 1]){
            continue;
        }
        path.push_back(num[i]);
        subsets_helper2(num, result, path, i + 1);
        path.pop_back();
    }
}

vector<vector<int> > subsets2(vector<int> num){
    vector<vector<int> > result;
    if(num.empty()) return result;

    sort(num.begin(), num.end());
    vector<int> path;
    subsets_helper2(num, result, path, 0);
    return result;
}

//************************************************************
//https://oj.leetcode.com/problems/combination-sum-ii/
//each element can be used only once
void combinationSum_helper(vector<int> &candidates, vector<vector<int> > &result, vector<int> &path, int sum, int pos){
    if(sum < 0) return;
    if(sum == 0){
        result.push_back(path);
    }

    int prev = -1;
    for(int i = pos; i < candidates.size(); ++i){
        if(candidates[i] == prev) continue;//同一次扩展中如何和之前重复则跳过

        path.push_back(candidates[i]);
        sum -= candidates[i];
        combinationSum_helper(candidates, result, path, sum, i + 1);
        prev = candidates[i];//important
        path.pop_back();
        sum += candidates[i];
    }
}

vector<vector<int> > combinationSum(vector<int> &candidates, int target){
    vector<vector<int> > result;
    if(candidates.empty()) return result;

    sort(candidates.begin(), candidates.end());
    vector<int> path;
    combinationSum_helper(candidates, result, path, target, 0);
    return result;
}

//************************************************************
// 2https://oj.leetcode.com/problems/combination-sum/
// number can be used many times
void combinationSum_helper2(vector<int> &candidates, vector<vector<int> > &result, vector<int> &path, int sum, int pos){
    if(sum < 0) return;
    if(sum == 0) result.push_back(path);

    for(int i = pos; i < candidates.size(); ++i){
        path.push_back(candidates[i]);
        sum -= candidates[i];
        combinationSum_helper2(candidates, result, path, sum, i);//next is i, duplicates allowed
        sum += candidates[i];
        path.pop_back();
    }
}

vector<vector<int> > combinationSum2(vector<int> &candidates, int target){
    vector<vector<int> > result;
    if(candidates.empty()) return result;

    vector<int> path;
    combinationSum_helper2(candidates, result, path, target, 0);//begin at position 0
    return result;
}

//************************************************************
//http://blog.csdn.net/yanghao58686763/article/details/1812418
vector<string> grayCode(int n){
    vector<string> code;
    code.resize(pow(2, n));

    if(n == 1){
        code[0] = string("0");
        code[1] = string("1");
        return code;
    }

    vector<string> last = grayCode(n - 1);
    for(int i = 0; i < last.size(); ++i){
        code[i] = "0" + last[i];
        code[code.size() - 1 - i] = last[i] + "1";
    }
    return code;
}

//********************************************************************************
template <typename T>
void printMatrix(vector<vector<T> > matrix){
    for(int i = 0; i < matrix.size(); ++i){
        for(int j = 0; j < matrix[i].size(); ++j){
            cout<<matrix[i][j] <<" ";
        }
        cout<<endl;
    }
}

//**************************** Problems *****************************************
/* permutation of a string
PROBLEM: Implement a routine that prints all possible orderings of the characters
in a string. In other words, print all permutations that use all the characters from
the original string. For example, given the string “hat”, your function should print
the strings “tha”, “aht”, “tah”, “ath”, “hta”, and “hat”. Treat each character
in the input string as a distinct character, even if it is repeated. Given the string “aaa”,
your routine should print “aaa” six times. You may print the permutations in any
order you choose.
*/
void StrPermHelper(string &origin, string intermedian, string path, vector<string> &result) {
    if (path.size() == origin.size()) {
        result.push_back(path);
        return;
    }

    for (int i = 0; i < intermedian.size(); ++i) {
        // core, select one in the left
        path.push_back(intermedian[i]);

        string tmp = intermedian;
        tmp.erase(i, 1);
        // pass left to the next round
        StrPermHelper(origin, tmp, path, result);

        // core
        path.pop_back();
    }
}

vector<string> StrPerm(string str) {
    vector<string> result;
    string path;
    StrPermHelper(str, str, path, result);
    return result;
}

/* Combination of a string
POBLEM:
Implement a function that prints all possible combinations of the
characters in a string. These combinations range in length from one to the length
of the string. Two combinations that differ only in ordering of their characters are
the same combination. In other words, “12” and “31” are different combinations
from the input string “123”, but “21” is the same as “12”.
characters in a string. These combinations range in length from one to the length
of the string. Two combinations that differ only in ordering of their characters are
the same combination. In other words, “12” and “31” are different combinations
from the input string “123”, but “21” is the same as “12”. */
void StrCombHelper(string &origin, int level, string &path, vector<string> &result) {
    if (path.size() > 0) {
        result.push_back(path);
    }

    for (int i = level; i < origin.size(); ++i) {
        path.push_back(origin[i]);
        StrCombHelper(origin, i  + 1, path, result);
        path.pop_back();
    }
}

vector<string> StrComb(string str) {
    vector<string> result;
    string path;

    StrCombHelper(str, 0, path, result);

    return result;
}

/* telephone num problem*/
std::unordered_map<char, string> tel_dict = {{'2', "ABC"},
                                             {'3', "DEF"},
                                             {'4', "GHI"},
                                             {'5', "JKL"},
                                             {'6', "MNO"},
                                             {'7', "PRS"},
                                             {'8', "TUV"},
                                             {'9', "WXY"}};

char GetCharKey(char tel_key, int place) {
    return tel_dict[tel_key][place];
}

void TelWordsHelper(string &tel_num, int level, string path,
                    vector<string> &result) {
    if (path.size() == tel_num.size()) {
        result.push_back(path);
        cout << "push " << "level: " << level << endl;
        return;
    }

    // we don't need for loop here, combination or permutation need, but NOT this
    // because combination/permutation have their own way to place each element
    // here we just need to go through all tel_num
    if (tel_num[level] == '0' || tel_num[level] == '1' || tel_num[level] == '-') {
        path.push_back(tel_num[level]);
        TelWordsHelper(tel_num, level + 1, path, result);
    } else {
        for (int j = 0; j < 3; ++j) {
            path.push_back(GetCharKey(tel_num[level], j));
            TelWordsHelper(tel_num, level + 1, path, result);
            path.pop_back();
        }
    }
}

vector<string> TelWords(string tel_num) {
    vector<string> result;
    string path;
    TelWordsHelper(tel_num, 0, path, result);
    return result;
}

vector<string> TelWordsIterative(string tel_num) {
    vector<string> result;
    string path;
    // get replaced string using place = 1
    for (int i = 0; i < tel_num.size(); ++i) {
        if (tel_num[i] == '0' || tel_num[i] == '1' || tel_num[i] == '-') {
            path.push_back(tel_num[i]);
        } else {
            path.push_back(GetCharKey(tel_num[i], 1 - 1));
        }
    }

    // this is kinda new way of thinking, new code structure
    // a while + a for + a state machine
    while (true) {
        result.push_back(path);

        for (int i = tel_num.size() - 1; i >= -1; --i) {
            if (i == -1) {
                return result;
            }

            // simple state machine
            if (path[i] == '0' || path[i] == '1' ||path[i] == '-') {
                continue;
            } else if (path[i] == GetCharKey(tel_num[i], 3 - 1)) {
                // if we have gone all 3 states, we should move to next level,
                // before move to next level, we need RESET to place 1 state,
                // because when next level state changes, cur level should also
                // go through 3 states
                path[i] = GetCharKey(tel_num[i], 1 - 1);
                continue;
            } else if (path[i] == GetCharKey(tel_num[i], 1 - 1)) {
                path[i] = GetCharKey(tel_num[i], 2 - 1);
                break;
            } else if (path[i] == GetCharKey(tel_num[i], 2 - 1)) {
                path[i] = GetCharKey(tel_num[i], 3 - 1);
                break;
            }
        }
    }
    return result;
}

/***************** test case ************************/
int main(){
    string str("2-2");
    vector<string> result = TelWordsIterative(str);
    cout << result.size() << endl;
    for(int i = 0; i < result.size(); ++i) {
        cout << result[i] << endl;
    }
    cout<<endl;
    return 0;
}
