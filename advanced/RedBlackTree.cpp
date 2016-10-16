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
    int N;
    TreeNode(int x, bool c, int s) : val(x), lchild(NULL), rchild(NULL), color(c), N(s){}
};

//************************************************************
//basic operations
bool isRed(TreeNode *root){
    if(root == NULL) return false;
    else return root->color == RED;
}

int size(TreeNode *root){
    if(root == NULL) return 0;
    else return root->N;
}

TreeNode* rotateLeft(TreeNode *root){
    assert(root != NULL && isRed(root->rchild));
    //link
    TreeNode *rc = root->rchild;
    root->rchild = rc->lchild;
    rc->lchild = root;
    //color
    rc->color = root->color;
    root->color = RED;
    //size
    rc->N = root->N;
    root->N = size(root->lchild) + size(root->rchild) + 1;
    return rc;
}

TreeNode* rotateRight(TreeNode *root){
    assert(root != NULL && isRed(root->lchild));
    //link
    TreeNode *lc = root->lchild;
    root->lchild = lc->rchild;
    lc->rchild = root;
    //color
    lc->color = root->color;
    root->color = RED;
    //size
    lc->N = root->N;
    root->N = size(root->lchild) + size(root->rchild) + 1;
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
void insert(TreeNode *&root, TreeNode *newNode){
    if(root == NULL)
        root = newNode;

    if(newNode->val < root->val){
        insert(root->lchild, newNode);
    }else if(newNode->val > root->val){
        insert(root->rchild, newNode);
    }else{
        root->val = newNode->val;//overwrite the value
    }

    if(isRed(root->rchild) && !isRed(root->lchild)) root = rotateLeft(root);
    if(isRed(root->lchild) && root->lchild != NULL && isRed(root->lchild->lchild)) root = rotateRight(root);
    if(isRed(root->lchild) && isRed(root->rchild)) flipColors(root);
    root->N = size(root->lchild) + size(root->rchild) + 1;
}


TreeNode* createRBTree(int n){
    TreeNode *root = NULL;
    for(int i = 0; i < n; ++i){
        TreeNode *newNode = new TreeNode(i, RED, 1);
        insert(root, newNode);
        root->color = BLACK;//every time insert, label the root as BLACK
    }
    return root;
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
//rank k means: in inorder traversal, there are k nodes smaller than it;
TreeNode* selectRank(TreeNode *root, int k){
    assert(root != NULL && k >= 0);

    int t = size(root->lchild);
    if(k > t) return selectRank(root->rchild, k - t - 1);
    else if(k < t) return selectRank(root->lchild, k);
    else return root;
}

//************************************************************
//assume no duplicates, return the rank of the target value
int getRank(TreeNode *root, int target){
    if(root == NULL) return 0;

    if(target > root->val){
        return size(root->lchild) + 1 + getRank(root->rchild, target);
    }else if(target < root->val){
        return getRank(root->lchild, target);
    }else{
        return size(root->lchild);
    }
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
        cout<<p->val<<" "<<"size: " << p->N<<endl;

        if(p->rchild != NULL) stk.push(p->rchild);
        if(p->lchild != NULL) stk.push(p->lchild);
    }
}

int main()
{
    TreeNode *root = createRBTree(5);
    preOrder(root);
    int n;
    while(cin>>n){
        cout<<getRank(root, n) <<endl;
    }
    return 0;
}
