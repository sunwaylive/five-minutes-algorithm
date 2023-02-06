#include <iostream>
#include <queue>
#include <stack>
#include <fstream>

using namespace std;

struct TreeNode{
    int val;
    TreeNode *lchild, *rchild;
    TreeNode(int x) : val(x), lchild(NULL), rchild(NULL){}
    TreeNode(TreeNode *l = NULL, TreeNode *r = NULL): lchild(l), rchild(r){}
};

TreeNode* createTree(){
    TreeNode *T;
    int data;
    cin>>data;
    if(data == -1){
        T = NULL;
    }else{
        T = new TreeNode(data);
        T->lchild = createTree();
        T->rchild = createTree();
    }
    return T;
}

//************************************************************
//1 while
void preOrder(TreeNode *root){
    if(root == NULL) return ;
    stack<TreeNode*> stk;
    TreeNode *p = root;
    stk.push(p);//no need for inOrder and postOrder
    while(!stk.empty()){
        p = stk.top();
        stk.pop();
        cout<<p->val<<" ";

        if(p->rchild != NULL) stk.push(p->rchild);
        if(p->lchild != NULL) stk.push(p->lchild);
    }
}
//2 while
void inOrder(TreeNode *root){
    if(root == NULL) return ;
    stack<TreeNode*> stk;
    TreeNode *p = root;
    while(!stk.empty() || p != NULL){
        //left
        while(p != NULL){
            stk.push(p);
            p = p->lchild;
        }
        //self
        p = stk.top();
        stk.pop();
        cout<<p->val <<" ";
        //right
        p = p->rchild;
    }
}

//3 while, 1 do
void postOrder(TreeNode *root){
    if(root == NULL) return;
    stack<TreeNode*> stk;
    TreeNode *p, *q;
    p = root;
    do{
        while(p != NULL){
            stk.push(p);
            p = p->lchild;
        }//left most

        q = NULL;
        while(!stk.empty()){
            p = stk.top();
            stk.pop();

            if(q == p->rchild){
                cout<<p->val<<" ";
                q = p;
            }else{
                stk.push(p);
                p = p->rchild;
                break;//important
            }
        }
    }while(!stk.empty());
}

void levelOrder(TreeNode *root){
    if(root == NULL) return;
    queue<TreeNode*> que;
    TreeNode *p = root;
    que.push(p);
    while(!que.empty()){
        int level_size = que.size();
        for(int i = 0; i < level_size; ++i){
            p = que.front();
            que.pop();
            cout<<p->val <<" ";

            if(p->lchild != NULL) que.push(p->lchild);
            if(p->rchild != NULL) que.push(p->rchild);
        }
        cout<<endl;
    }
}

void bfs(TreeNode *root){
    if(root == NULL) return;
    queue<TreeNode*> que;
    TreeNode *p = root;
    que.push(p);
    while(!que.empty()){
        p = que.front();
        que.pop();
        cout<<p->val <<" ";

        if(p->lchild != NULL) que.push(p->lchild);
        if(p->rchild != NULL) que.push(p->rchild);
    }
}

void dfs(TreeNode *root){
    if(root == NULL) return;
    stack<TreeNode*> stk;
    TreeNode *p = root;
    stk.push(p);
    while(!stk.empty()){
        p = stk.top();
        stk.pop();
        cout<<p->val <<" ";

        if(p->rchild != NULL) stk.push(p->rchild);
        if(p->lchild != NULL) stk.push(p->lchild);
    }
}

//************************************************************
//recursive
void insertBST(TreeNode *&root, TreeNode *newNode){
    if(root == NULL)
        root = newNode;
    else if(newNode->val < root->val)
        insertBST(root->lchild, newNode);
    else if(newNode->val > root->val)
        insertBST(root->rchild, newNode);
}

bool searchBST(TreeNode *root, int target){
    if(root == NULL) return false;

    if(target < root->val){
        return searchBST(root->lchild, target);
    }else if(target > root->val){
        return searchBST(root->rchild, target);
    }else{
        return true;
    }
}

//************************************************************
TreeNode* createBST(){
    TreeNode *root = NULL;
    int data;
    while(cin>>data){
        TreeNode *t = new TreeNode(data);
        insertBST(root, t);
    }
    return root;
}

//************************************************************
//iterative
//remember this instead of above
TreeNode* searchBSTIterative(TreeNode *root, int val){
    TreeNode *p = root;
    while(p != NULL){
        if(val < p->val){
            p = p->lchild;
        }else if(val > p->val){
            p = p->rchild;
        }else{
            return p;
        }
    }
    return NULL;
}

bool insertBSTIterative(TreeNode *&root, int val){
    TreeNode *par = NULL;
    TreeNode *cur = root;
    while(cur != NULL){
        if(val < cur->val){
            par = cur;
            cur = cur->lchild;
        }else if (val > cur->val){
            par = cur;
            cur = cur->rchild;
        }else{
            return false;//如果BST中存在相同则返回false
        }
    }

    TreeNode *newNode = new TreeNode(val);
    if(par == NULL){
        root = newNode;
    }else{
        if(val > par->val){
            par->rchild = newNode;
        }else{
            par->lchild = newNode;
        }
    }
    return true;
}

//************************************************************
//Given two values, print all the keys in Balanced Search Tree in the range in increasing order
void searchRangeInBSTHelper(TreeNode *root, vector<int> &result, int &low, int &high){
    if(root == NULL) return;

    if(root->val >= low && root->val <= high){
        searchRangeInBSTHelper(root->lchild, result, low, high);
        result.push_back(root->val);
        searchRangeInBSTHelper(root->rchild, result, low, high);
    }else if(root->val > high){
        searchRangeInBSTHelper(root->lchild, result, low, high);
    }else if(root->val < low){
        searchRangeInBSTHelper(root->rchild, result, low, high);
    }
}

vector<int> searchRangeInBST(TreeNode *root, int low, int high){
    vector<int> result;
    if(root == NULL) return result;

    searchRangeInBSTHelper(root, result, low, high);
    return result;
}

//************************************************************
//You need to find the inorder successor and predecessor of a given key.
//In case the given key is not found in BST,
//then return the two values within which this key will lie.
//Following is the algorithm to reach the desired result. Its a recursive method:
void findPrevSuc(TreeNode *root, TreeNode *&prev, TreeNode *&suc, int key){
    if(root == NULL) return ;

    if(root->val == key){
        if(root->lchild != NULL){
            TreeNode *tmp = root->lchild;
            while(tmp->rchild != NULL)
                tmp = tmp->rchild;
            prev = tmp;
        }

        if(root->rchild != NULL){
            TreeNode *tmp = root->rchild;
            while(tmp->lchild != NULL)
                tmp = tmp->lchild;
            suc = tmp;
        }
    }else if(root->val > key){//go left
        suc = root;
        findPrevSuc(root->lchild, prev, suc, key);
    }else{//go right
        prev = root;
        findPrevSuc(root->rchild, prev, suc, key);
    }
}

//************************************************************
bool delNode(TreeNode *&node){
    TreeNode *par;
    if(node->rchild == NULL){
        par = node; node = node->lchild;free(par);
    }else if(node->lchild == NULL){
        par = node; node = node->rchild; free(par);
    }else{//internal node
        par = node;
        TreeNode *tmp = node->lchild;
        while(tmp->rchild != NULL){
            par = tmp;//update parent
            tmp = tmp->rchild;
        }
        node->val = tmp->val;//replace
        if(par == node){
            par->lchild = tmp->lchild;
        }else{
            par->rchild = tmp->lchild;
        }
        free(tmp);
    }
    return true;
}

bool delBST(TreeNode *&root, int val){
    if(root == NULL) return false;

    if(val < root->val){
        return delBST(root->lchild, val);
    }else if(val > root->val){
        return delBST(root->rchild, val);
    }else{
        return delNode(root);
    }
}

//************************************************************
bool isValid(TreeNode *root, int lower, int upper){
    if(root == NULL) return true;
    return (root->val > lower) && (root->val < upper)
        &&isValid(root->lchild, lower, root->val)
        &&isValid(root->rchild, root->val, upper);
}

bool isValidBST(TreeNode* root){
    return isValid(root, INT_MIN, INT_MAX);
}

//************************************************************
// 修改一下GetHeight的函数，加入平衡的返回结果作为参数即可
int GetHeight(TreeNode *root, bool &is_balanced){
    if(root == NULL) return 0;
    if(!is_balanced) return 0;

    int lh = GetHeight(root->lchild, is_balanced);
    int rh = GetHeight(root->rchild, is_balanced);
    if(!is_balanced) return 0;//if is_balanced has been change in above two lines
    is_balanced = abs(lh - rh) <= 1;
    return max(lh, rh) + 1;
}

bool isBalanced(TreeNode *root){
    bool is_balanced = true;
    GetHeight(root, is_balanced);
    return is_balanced;
}

//************************************************************
int treeDepth(TreeNode *root){
    if(root == NULL) return 0;
    return max(treeDepth(root->lchild), treeDepth(root->rchild)) + 1;
}

//************************************************************
int minDepth(TreeNode *root){
    if(root == NULL) return 0;
    int ld = minDepth(root->lchild);
    int rd = minDepth(root->rchild);
    if(ld == 0){
        return rd + 1;
    }else if(rd == 0){
        return ld + 1;
    }else{
        return min(ld, rd) + 1;
    }
}

int maxDepth(TreeNode *root){
    if(root == NULL) return 0;
    int ld = maxDepth(root->lchild);
    int rd = maxDepth(root->rchild);
    if(ld == 0){
        return rd + 1;
    }else if(rd == 0){
        return ld + 1;
    }else{
        return max(ld, rd) + 1;
    }
}

//************************************************************
bool isSameTree(TreeNode *r1, TreeNode *r2){
    if(r1 == NULL && r2 == NULL) return true;
    else if(r1 == NULL || r2 == NULL) return false;

    return (r1->val == r2->val)
        && isSameTree(r1->lchild, r2->lchild)
        && isSameTree(r1->rchild, r2->rchild);
}

//************************************************************
bool isSymmetricTree(TreeNode *lchild, TreeNode *rchild){
    if(lchild == NULL && rchild == NULL) return true;
    else if(lchild == NULL || rchild == NULL) return false;

    return lchild->val == rchild->val
        && isSymmetricTree(lchild->lchild, rchild->rchild)
        && isSymmetricTree(lchild->rchild, rchild->lchild);
}

bool isSymmetricTree(TreeNode *root){
    if(root == NULL) return true;
    else return isSymmetricTree(root->lchild, root->rchild);
}

//************************************************************
//破坏原来的树
TreeNode* getSymmetricTree(TreeNode *&root){
    if(root == NULL) return root;

    TreeNode *l = getSymmetricTree(root->lchild);
    TreeNode *r = getSymmetricTree(root->rchild);
    root->lchild = r;
    root->rchild = l;
    return root;
}
//不破坏原来的树
TreeNode* getSymmetricTree2(TreeNode *root){
    if(root == NULL) return root;

    TreeNode *rootCopy = new TreeNode(root->val);
    rootCopy->lchild = getSymmetricTree2(rootCopy->rchild);
    rootCopy->rchild = getSymmetricTree2(rootCopy->lchild);
    return rootCopy;
}
//************************************************************
void destroyTree(TreeNode *root){
    if(root == NULL)
        return;
    destroyTree(root->lchild);
    destroyTree(root->rchild);
    delete root;
}

///////////////////////////advanced//////////////////////////
//************************************************************
//完全二叉树
bool isCompleteTree(TreeNode *root){
    if(root == NULL) return true;

    queue<TreeNode*> que;
    TreeNode *p = root;
    que.push(p);
    bool see_unfull = false;
    while(!que.empty()){
        p = que.front();
        que.pop();

        //left
        if(p->lchild != NULL){
            if(see_unfull) return false;
            else que.push(p->lchild);
        }else{
            see_unfull = true;
        }
        //right
        if(p->rchild != NULL){
            if(see_unfull) return false;
            else que.push(p->rchild);
        }else{
            see_unfull = true;
        }
    }
    return true;
}

//https://oj.leetcode.com/problems/flatten-binary-tree-to-linked-list/
//not in ordered
void flatten(TreeNode *root){
    if(root == NULL) return;

    flatten(root->lchild);
    flatten(root->rchild);

    //flatten process
    if(root->lchild != NULL){
        TreeNode *tmp = root->lchild;
        while(tmp->rchild != NULL)
            tmp = tmp->rchild;

        tmp->rchild = root->rchild;
        root->rchild = tmp;
        root->lchild = NULL;
    }
}

//http://www.cnblogs.com/remlostime/archive/2012/10/29/2745300.html
//convert BST to double linked list
TreeNode convert(TreeNode *root){
    if(root == NULL){
        return TreeNode();
    }

    //flatten process
    TreeNode ltree = convert(root->lchild);
    TreeNode rtree = convert(root->rchild);
    root->lchild = ltree.rchild;//left
    if(ltree.rchild != NULL)
        ltree.rchild->rchild = root;

    root->rchild = rtree.lchild;//right
    if(rtree.lchild != NULL)
        rtree.lchild->lchild = root;

    //as whole
    TreeNode *l = ltree.lchild == NULL ? root : ltree.lchild;
    TreeNode *r = rtree.rchild == NULL ? root : rtree.rchild;
    return TreeNode(l, r);
}

TreeNode* convert2DoubleList(TreeNode *root){
    TreeNode ret = convert(root);
    return ret.lchild;
}

//test program
// TreeNode *bst = createBST();
// TreeNode *h = convert2DoubleList(bst);
// while(h != NULL){
//     cout<<h->val <<" ";
//     h = h->rchild;
//  }
// cout<<endl;

//************************************************************
//find the first common ancestor of two nodes
// Lowest Common Ancestor: famouse problem
// use case: find LCA in classes hierarchy
bool IsFather(TreeNode *root, TreeNode *sun) {
    if (root == NULL || sun == NULL) return false;
    if (root->lchild == sun || root->rchild == sun) return true;

    return IsFather(root->lchild, sun) || IsFather(root->rchild, sun);
}

void LCA(TreeNode *root, TreeNode *s1, TreeNode *s2, TreeNode *&ans) {
    if (root == NULL || s1 == NULL || s2 == NULL)
        return;

    // only both father, we need go deeper
    // if not, recursive process ends
    if (IsFather(root, s1) && IsFather(root, s2)) {
        ans = root;
        LCA(root->lchild, s1, s2, ans);
        LCA(root->rchild, s1, s2, ans);
    }
}

// an easier case, get the LCA on binary search tree, assume s1->val <= s2->val
void BSTLCA(TreeNode *root, int small, int big, TreeNode *&ans) {
    if (root == NULL) {
        return;
    }

    while (root != NULL) {
        if (root->val >= small && root->val <= big) {
            ans = root;
            return;
        } else if (big < root->val) {
            root = root->lchild;
        } else if (small > root->val) {
            root = root->rchild;
        }
    }

    return;
}

//************************************************************
//树中两节点间的最大距离


//************************************************************
//build tree from preorder and inorder
TreeNode* build(vector<int> &preorder, int pl, int pr,
                vector<int> &inorder, int il, int ir){
    TreeNode *root;
    if(pl > pr || il > ir){
        root = NULL;
    }else {
        root = new TreeNode(preorder[pl]);
        int i;
        for(i = il; i <= ir && inorder[i] != root->val; ++i)
            ;
        root->lchild = build(preorder, pl + 1, pl + i - il, inorder, il, i - 1);
        root->rchild = build(preorder, pl + i - il + 1, pr, inorder, i + 1, ir);
    }
    return root;
}

TreeNode* buildTree(vector<int> &preorder, vector<int> &inorder){
    return build(preorder, 0, preorder.size() - 1,
                 inorder, 0, inorder.size() - 1);
}

//************************************************************
//build tree from inorder and postorder
TreeNode* build2(vector<int> &inorder, int il, int ir,
                 vector<int> &postorder, int pl, int pr){
    TreeNode *root;
    if(il > ir || pl > pr){
        root = NULL;
    }else{
        root = new TreeNode(postorder[pr]);
        int i;
        for(i = il; i <= ir && inorder[i] != root->val; ++i)
            ;
        root->lchild = build(inorder, il, i - 1, postorder, pl, i - il + pl - 1);
        root->rchild = build(inorder, i + 1, ir, postorder, i - il + pl, pr - 1);
    }
    return root;
}


//************************************************************
/*
 *  * 12. 求二叉树中节点的最大距离：getMaxDistanceRec
 *
 *  首先我们来定义这个距离：
 *  距离定义为：两个节点间边的数目.
 *  如：
 *     1
 *    / \
 *   2   3
 *        \
 *         4
 *   这里最大距离定义为2，4的距离，为3.
 * 求二叉树中节点的最大距离 即二叉树中相距最远的两个节点之间的距离。 (distance / diameter)
 * 递归解法：
 * 返回值设计：
 * 返回1. 深度， 2. 当前树的最长距离
 * (1) 计算左子树的深度，右子树深度，左子树独立的链条长度，右子树独立的链条长度
 * (2) 最大长度为三者之最：
 *    a. 通过根节点的链，为左右深度+2
 *    b. 左子树独立链
 *    c. 右子树独立链。
 *
 * (3)递归初始条件：
 *   当root == null, depth = -1.maxDistance = -1;
 */
struct Result{
    int maxDist;
    int depth;
    Result(int dist = -1, int depth = -1) : maxDist(dist), depth(depth){}
};

Result getMaxDistHelper(TreeNode *root){
    Result res;
    if(root == NULL) return res;

    Result l = getMaxDistHelper(root->lchild);
    Result r = getMaxDistHelper(root->rchild);
    res.depth = max(l.depth, r.depth) + 1;//1.update depth

    int cross = l.depth + 1 + r.depth + 1;//对于一个跨点的路径，跟左右的最大深度有关
    res.maxDist = max(cross, max(l.maxDist, r.maxDist));//2.update max dist
    return res;
}

int getMaxDist(TreeNode *root){
    return getMaxDistHelper(root).maxDist;
}

//************************************************************
//Trie
struct TrieNode
{
    int data;
    int count;
    unordered_map<char, TrieNode*> children;
    TrieNode() : data(0),count(0), children(unordered_map<char, TrieNode*>()) {}
};

TrieNode* BuildTrie(vector<string> words)
{
    TrieNode* root = new TrieNode();
    for (string word : words)
    {
        TrieNode* cur = root;
        for (char c : word)
        {
            if (cur->children.find(c) == cur->children.end())
            {
                cur->children[c] = new TrieNode();
            }

            cur = cur->children[c];
            cur->count++;
        }
    }

    return root;
}

//字典树查找前缀出现次数
int searchPrefix(TrieNode* root, string str)
{
    if (root == nullptr || str.length() == 0) return -1;

    TrieNode* cur = root;
    for (char c : str)
    {
        if (cur->children.find(c) == cur->children.end())
        {
            return -1;
        }
        else
        {
            cur = cur->children[c];
        }
    }

    return cur->count;
}

//************************************************************
int main()
{
    //ifstream in("input.txt");
    //cin.rdbuf(in.rdbuf());
    TreeNode *t = createBST();
    int small = 4, big = 14;
    TreeNode *ans = NULL;
    BSTLCA(t, small, big, ans);
    if (ans != NULL) {
        cout << ans->val << endl;
    }
    //in.close();
    return 0;
}
