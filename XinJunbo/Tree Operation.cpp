//Author:  Xin Junbo
//Date:    2014/09/02

#include<iostream>
#include<vector>
#include<stack>
#include<queue>
#include<string>
using namespace std;

struct TreeNode{
	int val;
	struct TreeNode* left;
	struct TreeNode* right;
	TreeNode(int x): val(x), left(NULL),right(NULL){};
};

//*****Travering the tree:  preOrder, inOrder, postOrder, leverOrder******
//preOrder of the tree
vector<int> preOrder(TreeNode* root){
	vector<int> preResult;
	stack<TreeNode*> nodeStack;
	TreeNode* p = root;
	while(p != NULL || !nodeStack.empty()){
		while(p != NULL){
			nodeStack.push(p);
			preResult.push_back(p -> val);
			p = p -> left;
		}
		p = nodeStack.top();
		nodeStack.pop();
		p = p -> right;
	}
	return preResult;
}

// inOrder of the tree
vector<int> inOrder(TreeNode* root){
	   vector<int> result;
	   stack<TreeNode*> nodeStack;
	   TreeNode* p = root;
	   while(p != NULL || ! nodeStack.empty() ){
		     while(p != NULL){
				 nodeStack.push(p);
				 p = p -> left;
			 }
			 p = nodeStack.top();
			 result.push_back(p -> val);
			 nodeStack.pop();
			 p = p -> right;
	   }
	   return result;
}

// postOrder of the tree
vector<int> postOrder(TreeNode* root){
	 vector<int> result;
	 stack<TreeNode*> nodeStack;
	 TreeNode* last = NULL;
	 TreeNode* p = root;
	 while(p !=NULL && !nodeStack.empty()){
		   while(p != NULL){
			   nodeStack.push(p);
			   p = p -> left;
	   }
		   p = nodeStack.top();
	//if the current node 'root' has no right child, or has already visit, visit root
		   if(p -> right == NULL || p -> right == last){
			       last = root;
				   result.push_back(p -> val);
				   nodeStack.pop();
				   p = NULL;
		   }else
			   p = p -> right;
  }
	   return result;
}

//levelOrder of the tree
vector<vector<int> > levelOrder(TreeNode* root){
	vector<int> temp;
	vector<vector<int> >  result;
	if(root == NULL) return result;
	queue<TreeNode*> nodeQueue;
	nodeQueue.push(root);
	TreeNode* p = root;
	while(!nodeQueue.empty()){
		int size = nodeQueue.size();
		for(int i=0; i < size; ++i){
			 p = nodeQueue.front();
			 temp.push_back(p->val);
			 nodeQueue.pop();
			 if(p -> left != NULL)
				 nodeQueue.push(p -> left);
			 if(p-> right != NULL)
				 nodeQueue.push(p -> right);
		  }
		result.push_back(temp);
		temp.clear();
	}
	return result;
}

//*********************BFS and DFS of the tree************************
vector<int> DFS(TreeNode* root){
	vector<int> result;
	if(root == NULL) return result;
	stack<TreeNode*> nodeStack;
	nodeStack.push(root);
	TreeNode* p = root;
	while( !nodeStack.empty() ){
		  p = nodeStack.top();
		  result.push_back(p -> val);
		  nodeStack.pop();
		  if(p->right != NULL) nodeStack.push(root -> right);
		  if(p ->left  != NULL) nodeStack.push(root -> left);
	}
	    return result;
}

vector<int> BFS(TreeNode* root){
	  vector<int> result;
	  if(root == NULL) return result;
	  queue<TreeNode*> nodeQueue;
	  nodeQueue.push(root);
	  TreeNode* p= root;
	  while( !nodeQueue.empty()){
		    p = nodeQueue.front();
			result.push_back(p->val);
			nodeQueue.pop();
			if(p -> left != NULL) nodeQueue.push(root -> left);
			if(p-> right != NULL) nodeQueue.push(root -> right);
	  }
	  return result;
}

//**********maxDepth and minDepth and getDepth of the tree****************
int maxDepth(TreeNode* root){
	if(root == NULL)  return 0;
	int left = maxDepth(root-> left);
	int right = maxDepth(root -> right);
	return max(left, right) + 1;
}

int minDepth(TreeNode* root){
	if(root == NULL) return 0;
	int left = minDepth(root -> left);
	int right = minDepth(root -> right);
	if( left == 0 && right == 0) 
		return 1;
	else if(left == 0)
		return 1+ right;
	else if(right == 0)
		return 1 + left;
	else
		return 1+ min(left, right);
}

int getTreeDepth(TreeNode* root){
	if(root == NULL) return 0;
	int nleft = getTreeDepth(root -> left);
	int nright = getTreeDepth(root -> right);
	return max(nleft, nright) + 1;
}

//**************Judge whether a tree is balanced or not**********************
bool isBalanceHelper(TreeNode* root, int* pDepth){  
	  if(root == NULL){
		*pDepth = 0;
		 return true;
	}
	int left,  right;
	if(isBalanceHelper(root->left, &left) && isBalanceHelper(root->right, &right) ){
			  int diff = left - right;
			  if(diff ==0 || diff == -1 || diff == 1){
				  *pDepth = max(left, right) +1;
				    return true;
			  }
		}
		  return false;
}

bool isBalanced(TreeNode* root){
	int depth = 0; 
	return isBalanceHelper(root, &depth);
}

//****************Judge whether a tree is  a BST or not**********************
bool isBSTHelper(TreeNode* root, int minNum, int maxNum){
	  if(root == NULL) return true;
	  if(minNum < root-> val && root -> val < maxNum)
		  return isBSTHelper(root->left, minNum, root -> val) 
		       && isBSTHelper(root->right, root->val, maxNum);
	  else
		  return false;
}
bool isBST(TreeNode* root){
	   return isBSTHelper(root, INT_MIN, INT_MAX);
}

//*********find the given key in the treee*******Iterative & Non-Iteration**********
bool findBST_Iteration(TreeNode* root, int key){   
	  if(root == NULL) return false;
	  if(root -> val  > key) 
		 return findBST_Iteration(root->left, key);
	  else if(root -> val < key)
		 return findBST_Iteration(root -> right, key);
	  else
		   return true;
}
bool findBST(TreeNode* root, int key){
	if(root == NULL) return false;
	TreeNode* p = root;
	while(p != NULL){
		if( p -> val > key)
			p = p->left;
		else if( p -> val < key)
			p = p->right;
		else
			return true;
	}
	  return false;
}
//********insert the given value Node in the tree*****Iteration & Non-Iteration*********
bool insertBST_Iteration(TreeNode* root, int key){
	   if(root == NULL){
		     TreeNode* node = new TreeNode(key);
			 root = node;
			 return true;
	   }
	   if(root -> val > key)
		  return  insertBST_Iteration(root->left, key);
	   else if(root -> val < key)
		return    insertBST_Iteration(root -> right, key);
	   else
		   return false;   
}
//insert BST using non-iterative method
bool insertBST(TreeNode* root, int key){
	TreeNode* node = new TreeNode(key);
	if(root == NULL)  {
		root = node;
		return true;
	}
	TreeNode* p = root;
	TreeNode*parent = NULL;
	while(p != NULL){
		if(p -> val > key){
			parent = p;
			p = p -> left;
		} else if(p -> val < key){
			parent = p;
			p= p -> right;
		} else
			return false;
	}
	  if(parent -> val > key)
		  parent -> left = node;
	  else
		  parent -> right = node;
	 return true;	
}
//***************************delete the given value key in the BST******************************
TreeNode* findMinNode(TreeNode* root){ //not the min-node of root, but the min-node's parent
	   if(root == NULL) return NULL;
	   TreeNode* cur = root;
	   TreeNode* parent = root;
	   while(cur -> left != NULL) {
		   parent = cur;
		   cur = cur -> left;
	   }
		   return parent;
}
//replace node2 with node1, and delete node1
void TransPlant(TreeNode** root, TreeNode* node1_parent, TreeNode* node1, TreeNode* node2){
	if(root == NULL) return;
	if(node1_parent == node1)
		 *root = node2;
	else if(node1_parent -> left ==  node1)
		node1_parent -> left = node2;
	else
		node1_parent -> right = node2;
}
bool deleteBST(TreeNode*& root, int key){
	    if(root == NULL) return false;
		TreeNode* cur = root;
		TreeNode* parent = root;
		while(cur != NULL){
			if(cur -> val > key){
				parent =  cur;
				cur = cur -> left;
			}else if(cur -> val < key){
				parent = cur;
				cur = cur -> right;
			}else break;
		}
		   if(cur == NULL) return false;
		   //cur node has no children
		   if(cur -> left == NULL && cur -> right == NULL)
			    TransPlant(&root, parent, cur, NULL);
		    //  cur node has no left child
		    else if(cur -> left == NULL)
			    TransPlant(&root, parent, cur, cur->right);
		   //cur node has no right child
			else if(cur -> right == NULL)
			    TransPlant(&root, parent, cur, cur->left);
		    //cur node  have both left child and right child
			else{
				  TreeNode * minNode_par = findMinNode(cur->right);
				  TreeNode* minNode = minNode_par->left == NULL? cur -> right: minNode_par -> left;
				  if(cur -> right != minNode){
						//replace minNode with its right child
				        TransPlant(&root,minNode_par, minNode, minNode -> right);		
						minNode -> right = cur -> right;		
				   }
				      TransPlant(&root, parent, cur, minNode);
				  	  minNode -> left = cur -> left;
			}
			return true;
}

//************Judge two trees are the same or not*****************
bool isSameTree(TreeNode* root1, TreeNode* root2){
	if(root1 ==NULL && root1 == NULL) return true;
	if(root1 == NULL || root2 == NULL) return false;
	if(root1 -> val == root2 -> val)
		return         isSameTree(root1->left, root2->left)
		            && isSameTree(root1->right, root2->right);
	else
		return false;
}

//*********Judge whether a tree is symmetric or not*************
bool isSymmetricHelper(TreeNode* root1, TreeNode* root2){
	   if(root1== NULL && root2 == NULL) return true;
	   if(root1 == NULL || root2 == NULL) return false;
	   if(root1 -> val == root2 -> val)
		   return        isSymmetricHelper(root1->left, root2 -> right)
		              && isSymmetricHelper(root1-> right, root2 -> left);
	   else
		   return false;
}
bool isSymmetricTree(TreeNode* root){
      if(root == NULL) return NULL;
	  return isSymmetricHelper(root->left, root->right);	  
}

//*********Judge whether T2 is T1's sub-tree***************
bool isSubTree(TreeNode* T1, TreeNode* T2){
	  if(T1 == NULL) return false;
	  TreeNode* p = T1;
      if(p->val == T2->val){
		  if(isSameTree(p, T2) )   //using isSameTree to judge p and T2
			  return true;
	  }
	  return isSubTree(p->left, T2) || isSubTree(p->right, T2);
}

//***********************build tree from inOrder and postOrder*****************
TreeNode *buildHelper(vector<int>::iterator inL, vector<int>::iterator inR,
	                                      vector<int>::iterator posL, vector<int>::iterator posR){
			if(posL >= posR) return NULL;
			int value = *(--posR);
			TreeNode* root = new TreeNode(value);
			vector<int>::iterator in = find(inL, inR, value);
			int number = in - inL;
	        root -> left = buildHelper(inL, in, posL, posL+number);
			root -> right = buildHelper(in+1, inR, posL+number, posR);
			return root;
}
TreeNode *buildTreeFromInandPost(vector<int>& inOrder, vector<int>&postOrder){
	    if ( inOrder.size() == 0) return NULL;
    	return buildHelper(inOrder.begin(), inOrder.end(), postOrder.begin(), postOrder.end() );
}

//********************build tree from inOrder and preOrder*********************
TreeNode* buildInandPreHelper(vector<int>::iterator inL, vector<int>::iterator inR,
	                                                    vector<int>::iterator preL, vector<int>::iterator preR){
				if(preL >= preR) return NULL;
				int value = *preL;
				TreeNode* root = new TreeNode(value);
				vector<int>::iterator in = find(inL, inR, value);
				int num = in - inL;
				root -> left = buildInandPreHelper(inL,in,preL+1,preL+1+num);
				root -> right = buildInandPreHelper(in+1, inR, preL+1+num, preR);
				return root;
}

TreeNode* buildTreeFromInandPre(vector<int>& inOrder, vector<int>& preOrder){
	 if(inOrder.size() == 0) return NULL;
	  return buildInandPreHelper(inOrder.begin(), inOrder.end(), preOrder.begin(), preOrder.end());
}

//***************create a Tree************************
TreeNode* createTree(void){
	int data;
	TreeNode* root;
	cin >> data;
	if(data == -1) root = NULL;
	else{
		 root = new TreeNode(data);
		 root -> val = data;
		 root -> left = createTree();
		 root -> right = createTree();
	}
	    return root;
}



int main(void){
	TreeNode* root = createTree();
	deleteBST(root,19);
	getchar();
	return 0;
}
