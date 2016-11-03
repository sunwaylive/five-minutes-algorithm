// refer to /Dropbox/**面试/ACM/后缀数组***.pdf
#include <iostream>
#include <cstdio>

using namespace std;

const int kMaxN = 200001; //
// wss is cnt[i]
int wa[kMaxN], wb[kMaxN], wv[kMaxN], cnt[kMaxN];

int cmp(int *r, int a, int b, int offset) {
    return r[a] == r[b] && r[a + offset] == r[b + offset];
}

void da(int *r, int *sa, int n, int m) {
    int i = 0, gap = 0, p = 0;
    int *x = wa, *y = wb, *tmp = NULL;

    // cnting sort on array r
    for (i = 0; i < m; ++i) cnt[i] = 0;
    for (i = 0; i < n; ++i) cnt[x[i] = r[i]]++; // record the count of element r[i]
    for (i = 1; i < m; ++i) cnt[i] += cnt[i-1]; // add up
    for (i = n - 1; i >= 0; --i) sa[--cnt[x[i]]] = i;

    // 若干次基数排序
    for (gap = 1, p = 1; p < n; gap <<= 1, m = p) {
        // 对第二关键字基数排序, 结果放在y数组中
        for (p = 0, i = n - gap; i < n; ++i) y[p++] = i;
        for (i = 0; i < n; ++i) if (sa[i] >= gap) y[p++] = sa[i] - gap;

        // 对第一关键字基数排序, 复用y数组
        for (i = 0; i < n; ++i) wv[i] = x[y[i]];
        // cnting sort
        for (i = 0; i < m; ++i) cnt[i] = 0;
        for (i = 0; i < n; ++i) cnt[wv[i]]++; // record the count
        for (i = 1; i < m; ++i) cnt[i] += cnt[i - 1]; // add up
        for (i = n - 1; i >= 0; --i) sa[--cnt[wv[i]]] = y[i];

        //
        for (tmp = x, x = y, y = tmp, p = 1, x[sa[0]] = 0, i = 1; i < n; ++i)
            x[sa[i]] = (cmp(y, sa[i - 1], sa[i], gap) != 0) ? p - 1 : p++;
    }

    return;
}

int ranking[kMaxN], height[kMaxN];
void BuildHeight(int *r, int *sa, int n) {
    int i, j, k = 0;
    for (i = 1; i <= n; ++i) ranking[sa[i]] = i;

    for (i = 0; i < n; height[ranking[i++]] = k)
        for (k != 0 ? k-- :  0, j = sa[ranking[i] - 1]; r[i + k] == r[j + k]; ++k)
            ;
}

int main() {
    return 0;
}
