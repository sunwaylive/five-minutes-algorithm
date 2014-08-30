#include <iostream>
#include <queue>
#include <stack>
#include <fstream>

using namespace std;

struct TreeNode{
    int val;
    TreeNode *lchild, *rchild;
    TreeNode(int x) : val(x), lchild(NULL), rchild(NULL){}
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
void insertBST(TreeNode *&root, TreeNode *newNode){
    if(root == NULL)
        root = newNode;
    else if(newNode->val < root->val)
        insertBST(root->lchild, newNode);
    else if(newNode->val > root->val)
        insertBST(root->rchild, newNode);
}

void delBST(TreeNode *&root, TreeNode *newNode){

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
int isBalancedHelper(TreeNode *root, bool &is_balanced){
    if(root == NULL) return 0;
    if(!is_balanced) return 0;

    int lh = isBalancedHelper(root->lchild, is_balanced);
    int rh = isBalancedHelper(root->rchild, is_balanced);
    if(!is_balanced) return 0;//if is_balanced has been change in above two lines
    is_balanced = abs(lh - rh) <= 1;
    return max(lh, rh) + 1;
}

bool isBalanced(TreeNode *root){
    bool is_balanced = true;
    return isBalancedHelper(root, is_balanced);
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
void destroyTree(TreeNode *root){
    if(root == NULL) return;
    else if(root->lchild == NULL && root->rchild == NULL){
        delete root;
    }
    if(root->lchild != NULL) destroyTree(root->lchild);
    if(root->rchild != NULL) destroyTree(root->rchild);
    delete root;
}

int main()
{
    ifstream in;
    in.open("input.txt");
    cin.rdbuf(in.rdbuf());
    TreeNode *root = createTree();
    cout<<"preOrder: ";
    preOrder(root);
    cout<<endl;

    cout<<"inOrder: ";
    inOrder(root);
    cout<<endl;

    cout<<"postOrder: ";
    postOrder(root);
    cout<<endl;

    cout<<"levelOrder: "<<endl;
    levelOrder(root);

    cout<<"dfs: ";
    dfs(root);
    cout<<endl;

    cout<<"bfs: ";
    bfs(root);
    cout<<endl;

    in.close();

    //test for BST
    ifstream bst_in;
    bst_in.open("bst_in.txt");
    cin.rdbuf(bst_in.rdbuf());
    cout<<endl;
    TreeNode *bst = createBST();
    cout<<"bst levleOrder: " <<endl;
    levelOrder(bst);
    cout<<endl <<searchBST(bst, 10) <<endl;
    cout<<searchBST(bst, 5) <<endl;
    bst_in.close();
    return 0;
}
