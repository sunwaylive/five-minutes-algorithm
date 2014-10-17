#include <iostream>
#include <cstdio>
#include <vector>
#include <set>
#include <stack>
#include <algorithm>
#include <unordered_map>
#include <string>
#include <map>

using namespace std;

//************************************************************
//Union and Intersection of two sorted arrays
//http://www.geeksforgeeks.org/union-and-intersection-of-two-sorted-arrays-2/
vector<int> findUnion(int arr1[], int m, int arr2[], int n){
    vector<int> result;
    int i = 0, j = 0;
    while(i < m && j < n){
        if(arr1[i] < arr2[j]) result.push_back(arr1[i++]);
        else if(arr1[i] > arr2[j]) result.push_back(arr2[j++]);
        else{
            result.push_back(arr1[i]);
            i++, j++;
        }
    }

    while(i < m) result.push_back(arr1[i++]);
    while(j < n) result.push_back(arr2[j++]);
    return result;
}

vector<int> findIntersection(int arr1[], int m, int arr2[], int n){
    vector<int> result;
    int i = 0, j = 0;
    while(i < m && j < n){
        if(arr1[i] < arr2[j]) i++;
        else if(arr1[i] > arr2[j]) j++;
        else{
            result.push_back(arr1[i]);
            i++, j++;
        }
    }
    return result;
}

//Union and Intersection of three sorted arrays
//http://www.geeksforgeeks.org/union-and-intersection-of-two-sorted-arrays-2/
set<int> findUnion3(int arr1[], int n1, int arr2[], int n2, int arr3[], int n3){
    set<int> result;
    for(int i = 0; i < n1; ++i) result.insert(arr1[i]);
    for(int i = 0; i < n2; ++i) result.insert(arr2[i]);
    for(int i = 0; i < n3; ++i) result.insert(arr3[i]);
    return result;
}

vector<int> findIntersection3(int arr1[], int n1, int arr2[], int n2, int arr3[], int n3){
    vector<int> result;
    int i = 0, j = 0, k = 0;
    while(i < n1 && j < n2 && k < n3){
        if(arr1[i] == arr2[j] && arr2[j] == arr3[k]) {
            result.push_back(arr1[i]);
            i++, j++, k++;
        }else if(arr1[i] < arr2[j]){
            i++;
        }else if(arr2[j] < arr3[k]){
            j++;
        }else{
            k++;
        }
    }
    return result;
}

//************************************************************
bool isPrim(int n){
    if(n <= 1) return false;

    for(int i = 2; i * i <= n; ++i){
        if(n % i == 0) return false;
    }
    return true;
}

//************************************************************
//筛数法，求N以内的所有素数, n > 2;
vector<int> getAllPrim(int n){
    vector<int> res;

    vector<bool> isPrime(n + 1, false);
    for(int i = 2; i * i <= n; ++i){
        for(int j = 1; j * i <= n; ++j){
            if(isPrime[j * i] && (n % (j * i) == 0))
                isPrime[j * i] = true;
        }//end for j
    }//end for i

}

//************************************************************
//分解质因数，1既不是质数也不是合数
void prim(int n){
    for(int i = 2; i <= n; ++i){
        while(n % i == 0){
            cout<<i<<endl;
            n /= i;
        }
    }
}

void prim_recur(int n, int m){
    if(n > m){
        while(n % m != 0) m++;
        cout<<m<<endl;
        n /= m;
        prim_recur(n, m);
    }
}

//************************************************************
// 1、给定一个字符串，求出其最长的重复子串。
// 思路：使用后缀数组，对一个字符串生成相应的后缀数组后，然后再排序，排完序依次检测相邻的两个字符串的开头公共部分。 这样的时间复杂度为：
// 生成后缀数组 O(N)
// 排序 O(NlogN*N) 最后面的 N 是因为字符串比较也是 O(N)
// 依次检测相邻的两个字符串 O(N * N)
// 总的时间复杂度是 O(N^2*logN),
string longestRepeatSubstring(string &str){
    vector<string> suffix;
    int n = str.length();
    for(int i = 0; i < n; ++i){
        suffix.push_back(str.substr(i));
    }
    sort(suffix.begin(), suffix.end());
    int max_len = 0;
    string max_str;
    for(int i = 1; i < suffix.size(); ++i){
        int p = 0, len = 0;
        while(p < suffix[i - 1].length() && p < suffix[i].length()){
            if(suffix[i - 1][p] != suffix[i][p]) break;
            p++, len++;
        }
        if(len > max_len){
            max_len = len;
            max_str = suffix[i].substr(0, max_len);
        }
    }
    return max_str;
}

//波兰表达式:前缀表达式；逆波兰表达式:后缀表达式

/*1.中缀表达式求值，先中缀转后缀，基于后缀表达式计算值
  使用两个栈，操作符栈，操作数栈，从左往右扫描表达式，遇到操作数直接压入操作数栈，遇到操作符，跟操作符栈栈顶元素比较优先级，当且仅当当前操作符比栈顶小的时候，直接压栈(如果大于或者等于栈顶元素，则弹出栈顶元素，将其压入操作数栈，类似保持金字塔形式)，优先级(乘除 > 加减 > 等号),等号优先级最低 */

/*2.将一个 逆波兰式(后缀表达式) 转回 中缀表达式 的算法：
  这个就相当简单了，就是一个机械的入堆栈出堆栈的操作，
  1）设置一个堆栈，将逆波兰式从左到右开始进行出入堆栈操作，还以上例为例：1,2,3,+,*
  2）遇到数字直接压栈；例如，上例逆波兰先进行三次入栈操作，堆栈的格局是： 1，2，3（栈顶）；
  3）遇到算符，将堆栈中的两个数字出栈。 如，读到+号后，2，3出栈，进行运算。注意，出栈时先出栈的元素是右算子，后出栈的是左算子，上例是2+3，不是3+2；
  4）将运算的结果作为新的算子，压入堆栈中。如运算结果(2+3)入栈，堆栈格局：1,(2+3)；
  5）反复1-4的操作，得到的中序表达式就是： 1*（2+3）；
 */
/*给中缀表达式，1+2*(3-4)+5，建树。
  表达式树特点，操作数必定在叶节点，操作符必定在内部节点。
  过程：选最后一个计算的符号，放在根节点，该运算符的左半部分放在左子树，有半部分放在由子树，递归直至结束
*/

vector<string> inToPost(vector<string> &expression){
    vector<string> post;
    if(expression.empty()) return post;

    map<char, int> cache;
    cache['+'] = 0;
    cache['-'] = 0;
    cache['*'] = 1;
    cache['/'] = 1;

    stack<char> oper;
    stack<int> opnd;
    for(int i = 0; i < (int)expression.size(); ++i){
        string tmp = expression[i];
        if(tmp.size() == 1 && tmp[0] == '+' && tmp[0] == '-'
           && tmp[0] == '*' && tmp[0] == '/'){
            while(!oper.empty()){
                if(cache[tmp[0]] < cache[oper.top()])
                    break;

                string op;
                op[0] = tmp[0];//char to string
                post.push_back(op);
                oper.pop();
            }
            oper.push(tmp[0]);
        }else{
            post.push_back(expression[i]);
        }
    }//end for
    return post;
}

//************************************************************
//正负交替
// 给定一个包含正负数的数组，按照正负交替的方式重新排列元素，但是正数或负数内部各自元素的相对位置不变，要求
// 空间复杂度O(1), 比如
// 输入： arr[] = {1, 2, 3, -4, -1, 4}
// 输出：arr[] = {-4, 1, -1, 2, 3, 4}
// 输入：arr[] = {-5, -2, 5, 2, 4, 7, 1, 8, 0, -8}
// 输出：arr[] = {-5, 5, -2, 2, -8, 4, 7, 1, 8, 0}
void rearrange(int *a, int n){

}

//************************************************************
//实现引用计数类，见隔壁的文件ReferenceCount.cpp


//************************************************************
//题目是这样的，两个长度相等的字符串，每个字符串中删掉一个字符，剩下的字符顺序不变，如果这样操作后得到的两个结果相同，就说是原来的两个字符串是相似的，实现函数
//O(n^2)
bool isSimilar(char str1[], char str2[], int length){
    if(str1 == NULL && str2 == NULL) return true;
    else if(str1 == NULL || str2 == NULL) return false;

    string s1(str1);
    string s2(str2);
    for(int i = 0; i < length; ++i){
        string tmp1 = s1;
        tmp1.erase(i, 1);
        for(int j = 0; j < length; ++j){
            string tmp2 = s2;
            tmp2.erase(j, 1);
            if(tmp1 == tmp2) return true;
        }
    }
    return false;
}

//O(n)
bool isSimilar2(char str1[], char str2[], int length){
    if(str1 == NULL && str2 == NULL) return true;
    else if(str1 == NULL || str2 == NULL) return false;

    int p1 = 0, p2 = length - 1;
    while(p1 < p2 && str1[p1] == str2[p1]) p1++;
    while(p1 < p2 && str1[p2] == str2[p2]) p2--;

    string s1(str1), s2(str2);
    string tmp1 = s1, tmp2 = s2;
    if(tmp1.erase(p1, 1) == tmp2.erase(p1, 1)) return true;
    tmp1 = s1, tmp2 = s2;
    if(tmp1.erase(p1, 1) == tmp2.erase(p2, 1)) return true;
    tmp1 = s1, tmp2 = s2;
    if(tmp1.erase(p2, 1) == tmp2.erase(p1, 1)) return true;
    tmp1 = s1, tmp2 = s2;
    if(tmp1.erase(p2, 1) == tmp2.erase(p2, 1)) return true;
    return false;
}

//************************************************************
//一个整数数组，长度为n，每个数的范围都是1~n+1，每个数字不重复，乱序的，求缺失的一个数
int findOneMissing(int *a, int n){
    if(a == NULL) return INT_MAX;
    unordered_map<int, bool> cache;
    for(int i = 0; i < n; ++i){
        cache[a[i]] = true;
    }

    for(int i = 1; i <= n + 1; ++i){
        if(cache.find(i) == cache.end()){
            return i;
        }
    }
    return INT_MAX;
}

//一个整数数组，长度为n，每个数的范围都是1~n+2，每个数字不重复，乱序的，求缺失的两个数
vector<int> findTwoMissing(int *a, int n){
    vector<int> result;
    if(a == NULL) return result;

    unordered_map<int, bool> cache;
    for(int i = 0; i < n; ++i){
        cache[a[i]] = true;
    }

    for(int i = 1; i <= n + 2; ++i){
        if(cache.find(i) == cache.end()){
            result.push_back(i);
        }
    }
    return result;
}
//以上类型的问题，可以通过 不同的方式 构造方程，然后解方程。缺失两个数，就构造两个方程，3个数就构造三个方程(和，积， 平方和，立方和等等)

//************************************************************
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
//求一个序列的第k个排列
vector<int> kth_permutation(vector<int> &num, int k){
    if(num.empty()) return num;

    for(int i = 0; i < k; ++i){
        next_permutation(num.begin(), num.end());
    }
    return num;
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
        cout<<"from " << a <<" to " <<c<<endl;//same
    }else{
        hanoi(n - 1, a, c, b);
        cout<<"from " << a <<" to " <<c <<endl;//same
        hanoi(n - 1, b, a, c);
    }
}

//************************************************************
//singleton

//1.first
class SingletonLazy{
private:
    SingletonLazy(){
    }
public:
    static SingletonLazy* getInstance(){
        static SingletonLazy *instance = new SingletonLazy();
        return instance;
    }
};

//2.second
class SingletonHunger{
private:
    SingletonHunger(){
    }
    static SingletonHunger *instance;

public:
    static SingletonHunger* getInstance(){
        return instance;
    }
};
//必须放在类外定义
SingletonHunger* SingletonHunger::instance = new SingletonHunger();

//3.third
class SingletonNest{
private:
    SingletonNest(){
    }
    static SingletonNest *instance;//这里是声明

    class Nest{
    public:
        ~Nest(){
            delete SingletonNest::instance;
        }
    };
    static Nest Garbo;
public:
    static SingletonNest* getInstance(){
        if(instance == NULL){
            instance = new SingletonNest();
        }
        return instance;
    }
};

SingletonNest* SingletonNest::instance = NULL;

//4.fourth, 线程安全的
//CCriticalsection 是windows下的,知道这么用即可，本质上是“对象管理内存”
// class Lock{
// public:
//     Lock(CCriticalSection cs) : m_cs(cs){
//         m_cs.Lock();
//     }
//     ~Lock(){
//         m_cs.UnLock();
//     }

// private:
//     CCriticalSection m_cs;
// };

// class SingletonThread{
// private:
//     SingletonThread(){
//     }
//     static SingletonThread* instance;
//     static CCriticalSection cs;
// public:
//     static SingletonThread* getInstance(){
//         if(instance == NULL){
//             Lock l(cs);//局部对象 自动销毁调用 析构函数
//             if(instance == NULL){
//                 instance = new SingletonThread();
//             }
//         }
//         return instance;
//     }
// };
//************************************************************
void printSet(set<int> &array){
    for(auto it = array.begin(); it != array.end(); ++it){
        cout<<*it<<" ";
    }
    cout<<endl;
}

int main()
{
    int ar1[] = {1, 5, 10, 20, 40, 80};
    int ar2[] = {6, 7, 20, 80, 100};
    int ar3[] = {3, 4, 15, 20, 30, 70, 80, 120};
    int n1 = sizeof(ar1)/sizeof(ar1[0]);
    int n2 = sizeof(ar2)/sizeof(ar2[0]);
    int n3 = sizeof(ar3)/sizeof(ar3[0]);

    set<int> res_union = findUnion3(ar1, n1, ar2, n2, ar3, n3);
    printSet(res_union);
    return 0;
}
