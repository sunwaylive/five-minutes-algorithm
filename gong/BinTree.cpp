// Authour: GongBenwei
// Date: 2014/8/21
//

#include<iostream>
#include<deque>
using namespace std;

struct BinTree{
	char val;
	BinTree *left;
	BinTree *right;
};

BinTree* CreateTree()
{
	char item;
	cin>>item;
	if(item == '#')
		return NULL;
	else{
		BinTree *tmpNode = new BinTree;
		tmpNode->val = item;
		tmpNode->left = CreateTree();
		tmpNode->right = CreateTree();

		return tmpNode;
	}
}

void PreOrder(BinTree *root)
{
	if(root == NULL)
		return;
	cout<<root->val<<" ";
	PreOrder(root->left);
	PreOrder(root->right);
}
void MidOrder(BinTree *root)
{
	if(root == NULL)
		return;
	MidOrder(root->left);
	cout<<root->val<<" ";
	MidOrder(root->right);
}

void PostOrder(BinTree *root)
{
	if(root == NULL)
		return;
	PostOrder(root->left);
	PostOrder(root->right);
	cout<<root->val<<" ";
}

void LevelOrder(BinTree *root)
{
	if(root == NULL)
		return;
	deque<BinTree *>	q;
	q.push_back(root);
	while(!q.empty())
	{
		BinTree *tmpNode = q.front();
		cout<<tmpNode->val<<" ";
		q.pop_front();
		if(tmpNode->left != NULL)
			q.push_back(tmpNode->left);
		if(tmpNode->right != NULL)
			q.push_back(tmpNode->right);
	}
}

int GetNumOfLeaf(BinTree *root)
{
	if(root == NULL)
		return 0;
	if(root->left == NULL && root->right == NULL)
		return 1;
	return GetNumOfLeaf(root->left) + GetNumOfLeaf(root->right);
}

int GetNumNode(BinTree *root, int k)
{
	if(root == NULL || k<1)
		return 0;
	if(k == 1)
		return 1;
	return GetNumNode(root->left, k-1) + GetNumNode(root->right, k-1);
}

int GetDeepth(BinTree *root)
{
	if(root == NULL)
		return 0;
	if(root->left == NULL && root->right == NULL)
		return 1;
	int l = GetDeepth(root->left);
	int r = GetDeepth(root->right);
	return l > r ? l+1 : r+1;
}

// Exchange the left_Tree and the right_Tree.
void SwapLeftRight(BinTree *root)
{
	if(root == NULL)
		return;
	BinTree *tmpNode = root->left;
	root->left = root->right;
	root->right = tmpNode;
	SwapLeftRight(root->left);
	SwapLeftRight(root->right);
}

// Judge whether a node is in the Tree.
bool IsInside(BinTree *root, BinTree *t)
{
	if(root == NULL)
		return false;
	else if(root == t)
		return true;
	else{
		bool has = false;
		if(root->left != NULL)
			has = IsInside(root->left, t);
		if(!has && root->right != NULL)
			has = IsInside(root->right, t);
		return has;
	}
}

// Judge whether two trees have the same structure.
bool Compare(BinTree *r, BinTree *t)
{
	if(r == NULL && t == NULL)
		return true;
	else if(r == NULL || t == NULL)
		return false;
	bool resultLeft = Compare(r->left, t->left);
	bool resultRight = Compare(r->right, t->right);
	
	return (resultLeft && resultRight);
}

bool ValueCompare(BinTree *r, BinTree *t)
{
	if(r == NULL && t == NULL)
		return true;
	else if(r == NULL || t== NULL)
		return false;
	else if( r->val == t->val)
	{
		return (ValueCompare(r->left, t->left) && ValueCompare(r->right, t->right));
//		Lresult = ValueCompare(r->left, t->left);
//		Rresult = ValueCompare(r->right, t->right);
//		return (Lresult && Rresult);
	}
	else
		return false;
}

bool Contain(BinTree *root, BinTree *test)
{
	if(root == NULL)
		return false;
	if(test == NULL)
		return true;
	if(root->val == test->val){
		if(ValueCompare(root, test))
			return true;
	}
	return (Contain(root->left, test) || Contain(root->right, test));
}



// Find the Nearest ancester of two nodes.
BinTree* GetNearFather(BinTree *root, BinTree *node1, BinTree *node2)
{
//	if(root == NULL)
//		return NULL;
	if(IsInside(node1, node2) )
		return node1;
	if(IsInside(node2, node1) )
		return node2;
	bool left1 = IsInside(root->left, node1);
	bool left2 = IsInside(root->left, node2);
	if(left1 != left2)
		return root;
	else if(left1 && !left2)
		return GetNearFather(root->left, node1, node2);
	else if(!left1 && left2)
		return GetNearFather(root->right, node1, node2);
	else
		return NULL;
}



int main()
{
	BinTree *root = new BinTree;
	root = CreateTree();
	cout<<"The PreOrder of the Tree is: "<<endl;
	PreOrder(root);
	cout<<"\n The MidOrder of the Tree is: "<<endl;
	MidOrder(root);
	cout<<"\n The PostOrder of the Tree is: "<<endl;
	PostOrder(root);
	cout<<"\n The LevelOrder of the Tree is: "<<endl;
	LevelOrder(root);
	int NumofLeaf = GetNumOfLeaf(root);
	cout<<"\n The Num of Leaf Nodes is: "<<NumofLeaf<<endl;
	int Deepth = GetDeepth(root);
	cout<<" The Deepth of the Tree is: "<<Deepth<<endl;
	
	int k =4;
	int NumNode_k = GetNumNode(root, k);
	cout<<" The Num of Node in Level "<<k<<" is: "<<NumNode_k<<endl;
	BinTree *node1 = root->left->right;
	BinTree *node2 = root->left->right->left;
	BinTree *node = GetNearFather(root, node1, node2);
	cout<<node->val<<endl;
	cout<<endl;
	cout<<" Swap the left and right of THe Tree."<<endl;
	SwapLeftRight(root);
	LevelOrder(root);
	
	return 0;
}
