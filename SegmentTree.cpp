/*
 * Base 版本的 线段树，仅供理解, 线段树并不一定是完全二叉树，国内博客有误
 * 高级版本的在后半部分
 * */

#include <iostream>
using namespace std;

/*
 * 对于线段树，在思考流程的时候可以以这种方式去思考
      [0,6)
       min*
    |      |
 [0,3)    [3,6)
 min*      min*

 区间+最值，这种方式去可视化思考过程.
 * */

const int kMaxTreeNodeNum = 1000;
struct SegTreeNode {
    SegTreeNode() : val(0) {
    }

    int val;
}g_seg_tree[kMaxTreeNodeNum];

// 如果区间超过1个元素，则左半边区间build到左子树，右半边build到右子树，然后当前根节点的值是 左右孩子的min
// 如果区间只有一个值，则当前根节点的值就是这个元素的值
// root: tree root position in the tree ndoe array
// start: interval start
// end: interval end
void Build(int *arr, int root, int start, int end) {
    // base case 1: no element
    if (start >= end) {
        return;
    }

    // base case 2: only one element
    if (start + 1 == end) {
        g_seg_tree[root].val = arr[start];
        return;
    }

    // iterative case
    int mid = start + (end - start) / 2;
    // build left child root
    Build(arr, 2*root+1, start, mid);
    // build right child root
    Build(arr, 2*root+2, mid, end);
    g_seg_tree[root].val = min(g_seg_tree[2*root+1].val, g_seg_tree[2*root+2].val);
}

// only in query, we can return a value, because we won't make any change to the tree
int Query(int root, int start, int end, int query_start, int query_end) {
    if (query_start <= start && query_end >= end) {
        // 查询区间 包含 当前区间
        return g_seg_tree[root].val;
    } else if (query_start >= end || query_end <= start) {
        // 查询区间 和 当前区间 没有交集
        return INT_MAX;
    }

    int mid = start + (end - start) / 2;
    return min(Query(root*2+1, start, mid, query_start, query_end),
               Query(root*2+2, mid, end, query_start, query_end));
}

// interval is left closed, right open
void UpdateAt(int root, int start, int end, int pos, int new_val) {
    if (start >= end) {
        return;
    }

    if (start + 1 == end && start == pos) {
        g_seg_tree[root].val = new_val;
        return;
    }

    int mid = start + (end - start) / 2;
    if (pos < mid) {
        // left child root
        UpdateAt(2*root+1, start, mid, pos, new_val);
    } else {
        // right child root
        UpdateAt(2*root+2, mid, end, pos, new_val);
    }
    // update self using left and right
    g_seg_tree[root].val = min(g_seg_tree[2*root+1].val, g_seg_tree[2*root+2].val);
}

/****************************************************************************/
/*
 * Advanced and super simple implementation of Segment Tree
 * for int type
 * */
const int kMaxArrSize = 1e5; // 1e5 = 100,000
int n;
int t[2 * kMaxArrSize];

void build() {
    for (int i = n - 1; i > 0; --i) {
        t[i] = t[i>>1] + t[i>>1 | 1]; // i>>1 = i / 2, i>>1 | 1 = i / 2 + 1;
    }
}

void modify(int p, int val) {
    for (t[p+=n] = val; p > 1; p >>= 1) {
        // if p if left child, p^1 is right child, and vice versa
        t[p>>1] = t[p] + t[p^1];
    }
}

// [l, r)
int query(int l, int r) {
    int res = 0;
    for (l += n, r += n; l < r; l>>=1, r>>=1) {
        // 左边有落单的
        if (l&1) res += t[l++];
        // 右边有落单的
        if (r&1) res += t[--r];
        // 如果都没有落单的,则交由父节点去求和
    }

    return res;
}


int main() {
    int a[] = {2, 5, 1, 4, 9, 3};
    //int n = sizeof(a) / sizeof(*a);
    int n = 6;
    Build(a, 0, 0, n);
    cout << Query(0, 0, n, 0, 3) << endl;
    UpdateAt(0, 0, n, 2, 10);
    cout << Query(0, 0, n, 0, 3) << endl;
    return 0;
}
