// Author: GongBenwei
// Date: 2014/8/10
/*
   The Program is about some Senior Operation for list.
   Delete a node in o(1) time.
   Reverse a list. Get the last kth node.
   Get the Mid node of the list.	
   Judge if the list has a Circle, if yes, return the length before the Circle.
   Judge if two lists intersect, if yes, return the first node of Intersection.
   */
//
//

#include<iostream>
using namespace std;

struct Node{
	char data;
	Node *next;
}

// Delete a node in o(1) time.
void DeleteRandomNode(Node *h, Node *curr)
{
	if(curr == NULL || curr->next == NULL){
		cout<<"Bad condition..."<<endl;
		return;
	}
	Node *pNext = curr->next;
	curr->data = pNext->data;
	curr->next = pNext->next;
	delete curr;

/*	if(pNext->next != NULL)
	{
		curr->data = pNext->data;
		curr->next = pNext->next;
		delete pNext;
	}
*/
}


void Reverse1(Node *head)
{
	if(head == NULL)
		return;
	if(head->next != NULL)
		Reverse1(head->next);
	cout<<head->data<<" ";
}

Node* Reverse2(Node *head)
{
	if(head == NULL || head->next ==NULL)
		return head;
	Node *Pre = NULL;
	Node *curr = head;
	Node *Next = NULL;
	while(curr != NULL)
	{
		Next = curr->next;
		curr->next = Pre;
		Pre = curr;
		curr = Next;
	}
	head->next = NULL;
	head = Pre;
	return Pre;
}

//return the last kth Node;
NodeList* GetNode(NodeList *head, int k)
{
	NodeList *first = head;
	NodeList *second = head;
	int i=0;
	while(i<k && first->next != NULL)
		first = first->next;
	while(first->next){
		first = first->next;
		second = second->next;
	}
	cout<<"The last kth NodeValue is: "<<second->data<<endl;
	return second;
}

// return the mid Node;
NodeList* GetNodeMid(NodeList *head)
{
	NodeList *first = head;
	NodeList *second = head;
	while(second){
		if(second->next) second = second->next;
		if(second->next) second = second->next;
		first = frist->next;
	}
	return first;
}

// Judge if a list have circle.
bool DetectCricle(NodeList *head)
{
	if(head == NULL || head->next == NULL)
		return false;
	NodeList *first = head;
	NodeList *second = head;
	while(second){
		first = first->next;
		if(second) second = second->next;
		else break;
		if(second) second = second->next;
		else break;
		if(fist == second)
			return true;
	}
	return false;
}

