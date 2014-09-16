#include <iostream>
#include <cstring>
#include <vector>
#include <cassert>

using namespace std;

//************************************************************
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
                if(j == 0) tmp[j] = 1;
                else tmp[j] = result[j - 1] + 1;
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
    int *dp = new int[n + 1]();
    dp[1] = 1;
    for(int i = 2; i <= n; ++i){
        for(int j = 1; j < i; ++j){
            if(a[j - 1] < a[i - 1] && dp[j] + 1 > dp[i])//大于当前的最大值
                dp[i] = dp[j] + 1;
            }
        max_len = max(max_len, dp[i]);
    }
    delete[] dp;
    return max_len;
}

int LDS(int *a, int n){
    if(a == NULL) return 0;

    int max_len = 0;
    int *dp = new int[n + 1];
    dp[1] = 1;
    for(int i = 2; i <= n; ++i){
        for(int j = 1; j < i; ++j){
            if(a[j - 1] >= a[i - 1] && dp[j] + 1 > dp[i]){
                dp[i] = dp[j] + 1;
            }
        }
        max_len = max(max_len, dp[i]);
    }
    delete[] dp;
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
//贪心法活动选择。活动已经按照结束时间从早到晚 排好序, P225
//若未排序，则：http://blog.csdn.net/crescent__moon/article/details/8828241
vector<int> selectActivity(int *s, int *f, int n){
    vector<int> result;
    if(s == NULL || f == NULL) return result;

    //第一个必选
    result.push_back(0);
    int last_end = f[0];
    for(int i = 0; i < n; ++i){
        if(s[i] >= last_end){    //找到余下合理活动中最早结束的那个，合理的意思是 在上一个活动结束后开始。记住 已经排好序
            result.push_back(i);
            last_end = f[i];
        }
    }
    cout<<result.size() <<endl;
    return result;
}

//************************************************************
//算法导论 P196, 装配线调度
//a0, a1: 装配线的装配时间；n，一条装配线上装配点数目； e0，e1 进入装配线的时间， l0 l1:离开装配线的时间， t0， t1：切换装配线的时间
void printWay(int *l0, int *l1, int n, int line){
    for(int j = n - 1; j >= 0; --j){
        cout<<j + 1<<" station is on "<< line<<endl;
        if(line  == 0)
            line = l0[j];
        else
            line = l1[j];
    }
}

int fastestWay(int *a0, int *a1, int n, int e0, int e1, int x0, int x1, int *t0, int *t1){
    if(a0 == NULL || a1 == NULL || t0 == NULL || t1 == NULL)
        return INT_MAX;
    //for printWay
    int *l0 = new int[n]();
    int *l1 = new int[n]();

    vector<vector<int> > c(n, vector<int>(n, 0));
    c[0][0] = e0 + a0[0];
    c[1][0] = e1 + a1[0];
    for(int j = 1; j < n; ++j){
        c[0][j] = min(c[0][j - 1], c[1][j - 1] + t1[j - 1]) + a0[j];
        c[1][j] = min(c[1][j - 1], c[0][j - 1] + t0[j - 1]) + a1[j];
        //update l0
        if(c[0][j - 1] < c[1][j - 1] + t1[j - 1]) l0[j] = 0;
        else l0[j] = 1;

        //update l1
        if(c[1][j - 1] < c[0][j - 1] + t0[j - 1]) l1[j] = 1;
        else l1[j] = 0;
    }

    if(c[0][n - 1] + x0 < c[1][n - 1] + x1) printWay(l0, l1, n, 0);
    else printWay(l0, l1, n, 1);

    delete[] l0;
    delete[] l1;
    return min(c[0][n - 1] + x0, c[1][n - 1] + x1);
}

//test program
// int a1[] = {7, 9, 3, 4, 8, 4};
// int a2[] = {8, 5, 6, 4, 5, 7};
// int line_len = sizeof(a1) / sizeof(a1[0]);
// int t1[] = {0, 2, 3, 1, 3, 4};
// int t2[] = {0, 2, 1, 2, 2, 1};
// int e1 = 2, e2 = 4;
// int l1 = 3, l2 = 2;
// int fw = fastestWay(a1, a2, line_len, e1, e2, l1, l2, t1, t2);
// cout<<fw<<endl;

//************************************************************
//双机调度问题
//dp[k][i] 表示完成前k个任务， 机器A花费小于或等于i的时间时， 机器B所需要的时间
//递推公式：dp[k][i] = min{dp[k - 1][i] + tb[k], dp[k - 1][i - ta[k]]};
//http://blog.csdn.net/will_lee_buaa/article/details/8531888
int task_schedule(int *ta, int *tb, int n){
    if( ta == NULL || tb == NULL) return 0;
    int sa = 0;
    for(int i = 0; i < n; ++i)
        sa += ta[i];

    vector<vector<int> > dp(n + 1, vector<int>(sa + 1, 0));
    for(int k = 1; k <= n; ++k){
        for(int i = 0; i <= sa; ++i){
            if(i < ta[k - 1]){//不能放到A上去运行， ta[k - 1]表示第k个任务的运行时间
                dp[k][i] = dp[k - 1][i] + tb[k - 1];
            }else{
                dp[k][i] = min(dp[k - 1][i] + tb[k - 1], dp[k - 1][i - ta[k - 1]]);
            }
        }
    }
    int result = INT_MAX;
    for(int i = 0; i <= sa; ++i){
        int tmp = max(dp[n][i], i);
        result = min(result, tmp);
    }
    return result;
}

//************************************************************
//http://chenjianneng3.blog.163.com/blog/static/128345126201110174316561/
//并行机调度, m台机器， n个任务,t为任务的执行时间
bool cmp(const int &a, const int &b){
    return a > b;
}

int parallel_schedule(int *t, int n, int m){
    if(t == NULL) return 0;

    sort(t, t + n, cmp);
    int *c = new int[m]();
    //初始化m个机器执行任务的时间
    for(int i = 0; i < m; ++i){
        c[i] = t[i];
    }
    //对于剩下的任务，每次从机器中选择当前耗时最短的来执行
    for(int j = m; j < n; ++j){
        sort(c, c + m, cmp);
        c[m - 1] += t[j];
    }
    //选出最大的即是所求解
    sort(c, c + m, cmp);
    int result = c[0];
    delete[] c;
    return result;
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
    int t[] = {10, 8, 3, 1, 7, 5};
    for(int i = 0; i < 6; ++i)
        cout<<t[i]<<" ";
    cout<<endl;
    cout<<parallel_schedule(t, 6, 2)<<endl;
    return 0;
}
