#include <iostream>
#include <cstring>
#include <vector>
#include <cassert>

using namespace std;

int longestCommonSubstring(const string &txt, const string &query){
    if(txt.empty() || query.empty()) return 0;

    int t_len = txt.length();
    int q_len = query.length();
    vector<int> tmp(t_len, 0), result(t_len, 0);
    int max_end = 0, max_len = 0;

    for(int i = 0; i < q_len; ++i){
        tmp.assign(t_len, 0);//clear every time
        for(int j = 0; j < t_len; ++j){
            if(query[i] == txt[j]){
                if(j == 1){
                    tmp[j] = 0;
                }else{
                    tmp[j] = result[j - 1] + 1;
                }
            }

            if(tmp[j] > max_len){
                max_len = tmp[j];
                max_end = j;
            }
        }// end for
        swap(tmp, result);
    }//end for
    //string s = txt.substr(max_end - max_len + 1, max_len); //获得子串
    return max_len;
}

//************************************************************
//http://blog.csdn.net/yysdsyl/article/details/4226630
void getMaxSequence(const string &pat, vector<vector<int> > &b, int i, int j){
    if(i == 0 || j == 0) return;

    if(b[i][j] == 0){
        getMaxSequence(pat, b, i - 1, j - 1);
        cout<<pat[i - 1]<<" ";
    }else if(b[i][j] == 1){
        getMaxSequence(pat, b, i - 1, j);
    }else{
        getMaxSequence(pat, b, i, j - 1);
    }
}

int longestCommonSubsequence(const string &txt, const string &pat){
    const int t_len = txt.length();
    const int p_len = pat.length();
    vector<vector<int> > c(p_len + 1, vector<int>(t_len + 1, 0));
    vector<vector<int> > b(p_len + 1, vector<int>(t_len + 1, 0));
    //first row and first column is 0, dp starts from second row and second column
    int max_len = 0;
    for(int i = 1; i <= p_len; ++i){
        for(int j = 1; j <= t_len; ++j){
            if(txt[j - 1] == pat[i - 1]){
                c[i][j] = c[i - 1][j - 1] + 1;
                b[i][j] = 0;
            }else if(c[i - 1][j] > c[i][j - 1]){
                c[i][j] = c[i - 1][j];
                b[i][j] = 1;
            }else {
                c[i][j] = c[i][j - 1];
                b[i][j] = -1;
            }
        }
    }

    max_len = c[p_len][t_len];
    //get the max sequence
    getMaxSequence(pat, b, p_len, t_len);
    return max_len;
}

//************************************************************
//http://blog.csdn.net/wangkechuang/article/details/7949151
//longest increasing sequence

//O(n^2)
//dp[i] 表示以第i个数结尾的LIS的长度，必须包含i
int LIS(int *a, int n){
    if(a == NULL) return 0;

    int max_len = 0;
    int *dp = new int[n + 1];
    dp[1] = 1;
    for(int i = 2; i <= n; ++i){
        int m = 0;//当前最大值
        for(int j = 1; j < i; ++j){
            if(a[j - 1] < a[i - 1] && dp[j] > m)//大于当前的最大值
                m = dp[j];
            }
        dp[i] = m + 1;
        max_len = max(max_len, dp[i]);
    }
    return max_len;
}

int LDS(int *a, int n){
    if(a == NULL) return 0;

    int max_len = 0;
    int *dp = new int[n + 1];
    dp[1] = 1;
    for(int i = 2; i <= n; ++i){
        int m = 0;
        for(int j = 1; j < i; ++j){
            if(a[j - 1] >= a[i - 1] && dp[j] > m){
                m = dp[j];
            }
        }
        dp[i] = m + 1;
        max_len = max(max_len, dp[i]);
    }
    return max_len;
}

//************************************************************
//https://oj.leetcode.com/problems/maximum-subarray/
//maximum sub array
int maxSubArray(int *a, int n){
    assert(a != NULL);

    int max_sum = 0;
    int cur_sum = 0;
    int start = -1, end = -1;
    for(int i = 0; i < n; ++i){
        cur_sum += a[i];
        if(cur_sum < 0){
            start = i + 1;
            cur_sum = 0;
        }

        if(cur_sum > max_sum){
            max_sum = cur_sum;
            end = i;
        }
    }
    cout<<start<<" " <<end <<endl;
    return max_sum;
}

//no need to record the start and end
//this method will modify the input, bad one
//O(n)
int maxSubArray2(int *a, int n){
    assert(a != NULL);
    int max_sum = max(a[0], 0);
    for(int i = 1; i < n; ++i){
        a[i] = a[i - 1] > 0 ? (a[i - 1] + a[i]) : a[i];
        max_sum = max(max_sum, a[i]);
    }
    return max_sum;
}

//O(nlogn)
int maxSubArray3(int *a, int start, int end){
    assert(a != NULL);
    if(start + 1 < end){
        int mid = start + ((end - start) >> 1);
        int left = maxSubArray3(a, start, mid);
        int right = maxSubArray3(a, mid + 1, end);

        //left part
        int l = 0, m_l = 0;
        for(int i = mid - 1; i >= start; --i){
            l += a[i];
            m_l = max(m_l, l);
        }
        //right part
        int r = 0, m_r = 0;
        for(int i = mid; i < end; ++i){
            r += a[i];
            m_r = max(m_r, r);
        }
        // compare 3
        return max(left, max(right, m_l + m_r));
    }else{//only one element
        return max(0, a[start]);
    }
}

//************************************************************
//insert delete replace
int editDistance(const string &txt, const string &pat){
    int t_len = txt.length();
    int p_len = pat.length();
    vector<vector<int> > c(p_len + 1, vector<int>(t_len + 1, 0));
    for(int i = 0; i <= p_len; ++i){
        c[i][0] = i;
    }
    for(int j = 0; j <= t_len; ++j){
        c[0][j] = j;
    }

    for(int i = 1; i <= p_len; ++i){
        for(int j = 1; j <= t_len; ++j){
            if(pat[i - 1] == txt[j - 1]){
                c[i][j] = c[i - 1][j - 1];
            }else{
                c[i][j] = min(c[i - 1][j - 1], min(c[i][j - 1], c[i - 1][j])) + 1;
            }
        }
    }
    return c[p_len][t_len];
}

//************************************************************
//https://oj.leetcode.com/problems/triangle/
int minimumTotal(vector<vector<int> > &triangle){
    int row = triangle.size();
    vector<int> tmp(row, 0);
    vector<int> sum(row, 0);
    for(int i = 0; i < row; ++i){
        sum.assign(row, 0);
        for(int j = 0; j <= i; ++j){
            if(j == 0){
                sum[j] = triangle[i][j] + tmp[j];
            }else if(j == i){
                sum[j] = triangle[i][j] + tmp[j - 1];
            }else{
                sum[j] = min(tmp[j], tmp[j - 1]) + triangle[i][j];
            }
        }
        swap(tmp, sum);
    }

    //result saved in tmp
    int min_sum = INT_MAX;
    for(int i = 0; i < row; ++i){
        cout<<"sum[i]: " <<tmp[i]<<" ";
        min_sum = min(min_sum, tmp[i]);
    }
    return min_sum;
}

//************************************************************
//https://oj.leetcode.com/problems/palindrome-partitioning-ii/
//dp[i][j]: str(i~j) is palindrome
int minCut(const string &str){
    if(str.length() == 0) return 0;

    const int n = str.length();
    vector<vector<bool> > dp(n, vector<bool>(n, false));
    for(int i = 0; i < n; ++i){
        int l, r;
        //search odd
        l = i - 1, r = i + 1;
        while(l >= 0 && r <= n && str[l] == str[r]){
            dp[l][r] = true;
            l--, r++;
        }
        //search even
        l = i - 1, r = i;
        while(l >= 0 && r <= n && str[l] == str[r]){
            dp[l][r] = true;
            l--, r++;
        }
    }

    //core part
    //count[i]: (i ~ end)'s min cut; count[i] = min(count[j] + 1) j: i ~ end
    //answer: count[0]
    vector<int> cut(n + 1, 0);
    for(int i = n - 1; i >= 0; --i){
        cut[i] = n - i;
        for(int j = i; j < n; ++j){//j can be equal to i, just one letter
            if(dp[i][j] == 1){
                cut[i] = min(cut[i], cut[j + 1] + 1);
            }
        }
    }
    return cut[0] - 1;
}

//************************************************************
void printMatrix(vector<vector<int> > &matrix){
    for(int i = 0; i < matrix.size(); ++i){
        for(int j = 0; j < matrix[i].size(); ++j){
            cout<<matrix[i][j] <<" ";
        }
        cout<<endl;
    }
}

int main(){
    int a[] = {-2, 1, -3, 4, -1, 2, 1, -5, 4};
    int n = sizeof(a) / sizeof(a[0]);
    cout<<maxSubArray3(a, 0, n) <<endl;

    string txt("A");
    string pat("B");
    cout<<longestCommonSubstring(txt, pat)<<endl;

    int b[] = {1, 7, 3, 5, 9, 4, 8};
    int n_b = sizeof(b) / sizeof(b[0]);
    cout<<LIS(b, n_b) <<endl;
    cout<<LDS(b, n_b) <<endl;

    cout<<editDistance(txt, pat)<<endl;

    cout<<"triangle"<<endl;
    vector<vector<int> > tri;
    for(int i = 0; i < 2; ++i){
        vector<int> tmp;
        for(int j = 0; j <= i; ++j){
            tmp.push_back(rand() % 10);
        }
        tri.push_back(tmp);
    }
    printMatrix(tri);
    cout<<minimumTotal(tri)<<endl;

    string c("aaa");
    cout<<minCut(c) <<endl;
    return 0;
}
