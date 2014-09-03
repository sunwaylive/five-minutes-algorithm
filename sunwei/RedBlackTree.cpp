#include <iostream>
#include <cassert>
#include <queue>
#include <stack>
using namespace std;

const bool RED = true;
const bool BLACK = false;

struct TreeNode{
    int val;
    TreeNode *lchild, *rchild;
    bool color;//red: 1, black: 0
    TreeNode(int x, bool c) : val(x), lchild(NULL), rchild(NULL), color(c){}
};

//************************************************************
//basic operations
bool isRed(TreeNode *root){
    if(root == NULL) return false;
    else return root->color == RED;
}

TreeNode* rotateLeft(TreeNode *root){
    assert(root != NULL && isRed(root->rchild));
    TreeNode *rc = root->rchild;
    root->rchild = rc->lchild;
    rc->lchild = root;
    rc->color = root->color;
    root->color = RED;
    return rc;
}

TreeNode* rotateRight(TreeNode *root){
    assert(root != NULL && isRed(root->lchild));
    TreeNode *lc = root->lchild;
    root->lchild = lc->rchild;
    lc->rchild = root;
    lc->color = root->color;
    root->color = RED;
    return lc;
}

void flipColors(TreeNode *root){
    assert(root != NULL && root->lchild != NULL && root->rchild != NULL);
    // h must have opposite color of its two children
    assert ((isRed(root) && !isRed(root->lchild) && !isRed(root->rchild))
        || (!isRed(root) && isRed(root->lchild) && isRed(root->rchild)) );

    root->color = !root->color;
    root->lchild->color = !root->lchild->color;
    root->rchild->color = !root->rchild->color;
}

//************************************************************
bool search(TreeNode *root, int target){
    while(root != NULL){
        if(target == root->val){
            return true;
        }else if(target > root->val){
            return search(root->rchild, target);
        }else {
            return search(root->lchild, target);
        }
    }
    return false;
}

//************************************************************
void insert(TreeNode *&root, int val){
    if(root == NULL) root = new TreeNode(val, RED);
    if(val < root->val){
        insert(root->lchild, val);
    }else if(val > root->val){
        insert(root->rchild, val);
    }else{
        root->val = val;//overwrite the value
    }

    if(isRed(root->rchild) && !isRed(root->lchild)) root = rotateLeft(root);
    if(isRed(root->lchild) && root->lchild != NULL && isRed(root->lchild->lchild)) root = rotateRight(root);
    if(isRed(root->lchild) && isRed(root->rchild)) flipColors(root);
}


TreeNode* createRBTree(int n){
    TreeNode *root = NULL;
    for(int i = 0; i < n; ++i){
        insert(root, i);
        root->color = BLACK;//every time insert, label the root as BLACK
    }
    return root;
}

//************************************************************
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

int main()
{
    TreeNode *root = createRBTree(5);
    preOrder(root);
    return 0;
}
