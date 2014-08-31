//
//

#include<iostream>
using namespace std;

struct BiNode{
	char val;
	BiNode *left, *right;
}

bool SearchBST(BiNode *root, char key, BiNode& *p)
{
	if(root == NULL)
	{
		*p = root;
		return false;
	}
	if(key == root->val)
	{
		*p == root;
		return true;
	else if(key < root->val)
		SearchBST(root->left, key, p);
	else if(key > root->val)
		SearchBST(root->right, key, p);
}

bool Insert(BiNode *root, char key)
{
	BiNode *p;
	if(SearchBST(root, key, &p))
		return false;
	else{
		BiNode *s = new BiNode;
		s->val = key;
		s->left = s->right = NULL;
	
		if(p)
			root = s;
		else if(key < p->val)
			p->left = s;
		else
			p->right = s;
		
		return true;
	}
}

