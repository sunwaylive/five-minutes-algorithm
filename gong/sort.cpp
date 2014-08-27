// The Quick-sort from <An introduction to Algorithm>

#include<iostream>
using namespace std;

void swap(int &a, int &b)
{
	int temp = a;
	a = b;
	b = temp;
}

int partition(int A[], int p, int q)
{
	int x = A[q];
	int i = p-1;
	for(int j=p; j<q; ++j)
	{
		if(A[j]<x){
			++i;
			swap(A[i], A[j]);
		}
	}
	swap(A[i+1], A[q]);
	return i+1;
}

int partion2(int A[], int p, int q)
{
	int key = A[p];
	while(p<q)
	{
		while(p<q && A[q]>=key) --q;
		swap(A[p], A[q]);
		while(p<q && A[q]<=key) ++p;
		swap(A[p], A[q]);
	}
	return p;
}

void Quick_Sort(int A[], int p, int q)
{
	if(p<q){
		int m = partition(A, p, q);
		Quick_Sort(A, p, m-1);
		Quick_Sort(A, m+1, q);
	}
}

