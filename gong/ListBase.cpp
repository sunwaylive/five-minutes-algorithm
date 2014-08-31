// Author: GongBenwei 
// Date: 2014/8/10

/*
   Some Basic Operation for Define/ Create/ Print/ Insert/ Delete
 */

//

#include<iostream>
using namespace std;

struct NodeList{
	char data;
	NodeList *next;
//	NodeList(char a): data(a), next(NULL){}
};

//N --- the length of the list.
NodeList* CreateList(int N)
{
	NodeList *head=new NodeList;
	if(head == NULL){
		cout<<"Bad Allocation..."<<endl;
		return NULL;
	}
	head->next = NULL;
	NodeList *pre = head;
	NodeList *p = NULL;
	for(int i=0; i<N; ++i)
	{
		char temp = 0;
		p = new NodeList;
		cout<<"Enter a char: ";
		cin>>temp;
		p->data = temp;
		pre->next = p;
		pre = p;
	}
	p->next = NULL;
	return head;
}

void PrintList(NodeList *h)
{
	NodeList *p;
	p = h->next;
	while(p){
		cout<<p->data<<" ";
		p = p->next;
	}
}

void InsertHead(NodeList *h, NodeList *f)
{
	if(h == NULL || f ==NULL)
	{
		cout<<"Bad Condition..."<<endl;
		return;
	}
	f->next = h->next;
	h->next = f;
}

void InsertMid(NodeList *h, int pos, NodeList *m)
{
	if(m == NULL)
	{
		cout<<"Bad Condition..."<<endl;
		return;
	}
	NodeList *curr = h;
	int i = 0;
	while(curr != NULL && i<pos)
	{
		curr = curr->next;
		i++;
	}
	m->next = curr->next;
	curr->next = m;
}

void InsertEnd(NodeList *h, NodeList *t)
{
	if(h == NULL || t==NULL)
	{
		cout<<"Bad Condition..."<<endl;
		return;
	}
	NodeList *curr = h;
	while(curr->next != NULL)
		curr = curr->next;
	curr->next = t;
//	curr = curr->next;
//	curr->next = NULL;
}

void DeleteList(NodeList *h, int pos)
{
	NodeList *curr = h;
	int i=0;
	while(curr != NULL && i<pos-1){
		i++;
		curr = curr->next;
	}
	NodeList *p = curr->next;
//	cout<<"The Delete data is: "<<p->data<<endl;
	curr->next = p->next;
	delete p;
}

// Reverse a List (No need to change the list).
void Reverse1(NodeList *head)
{
	if(head == NULL)
		return;
	if(head->next != NULL)
		Reverse1(head->next);
	cout<<head->data<<" ";
}

// Reverse a LIST (Change the List)
void Reverse2(NodeList* head)
{
	if(head == NULL || head->next == NULL)
		return;
	NodeList *pre = head;
	NodeList *nes = NULL;
	NodeList *curr = head->next;
	while(curr){
		nes = curr->next;
		curr->next = pre;
		pre = curr;
		curr = nes;
	}
	head->next = NULL;
	head = pre;
}

int main()
{
	int n = 10;
	NodeList *Head = CreateList(n);
	PrintList(Head);
	cout<<endl;
	
	Reverse1(Head);
	cout<<endl;
	Reverse2(Head);
	PrintList(Head);
	cout<<endl;
//	NodeList *first = new NodeList('G');
/*	NodeList *first = new NodeList;
	first->data = 'G';
	first->next = NULL;
	InsertHead(Head, first);
	PrintList(Head);
	cout<<endl;
*/
/*	NodeList *mid = new NodeList;
	mid->data = 'S';
	mid->next = NULL;
	InsertMid(Head, 4, mid);
	PrintList(Head);
	cout<<endl;
	
	NodeList *end = new NodeList;
	end->data = 'Y';
	end->next = NULL;
	InsertEnd(Head, end);
	PrintList(Head);
	cout<<endl;

	DeleteList(Head, 5);
	PrintList(Head);
*/
	return 0;
}
