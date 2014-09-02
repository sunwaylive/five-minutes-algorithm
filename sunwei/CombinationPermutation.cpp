#include <iostream>
#include <vector>
#include <cmath>
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
        code.push_back(string("0"));
        code.push_back(string("1"));
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
void printMatrix(vector<vector<int> > matrix){
    for(int i = 0; i < matrix.size(); ++i){
        for(int j = 0; j < matrix[i].size(); ++j){
            cout<<matrix[i][j] <<" ";
        }
        cout<<endl;
    }
}

int main(){
    int a[] = {10, 1, 2, 7, 6, 1, 5};
    const int n = sizeof(a) / sizeof(a[0]);
    vector<int> num(a, a + n);
    vector<vector<int> > res = combinationSum(num, 8);
    for(int i = 0; i < res.size(); ++i){
        for(int j = 0; j < res[i].size(); ++j){
            cout<<res[i][j] <<" ";
        }
        cout<<endl;
    }
    cout<<endl;
    return 0;
}
