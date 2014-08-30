#include<iostream>
#include<string>
#include<vector>
using namespace std;

void swap(int&a, int &b){
	int temp;
	temp = a;
	a = b;
	b = temp;
}

//*****************Bubble Sort********************
void BubbleSort(int A[], int n){
	if(n==0) return;
	int i, j;
	bool exchange = true;
	for(i = 0; i < n; ++i){
		exchange = false;
		for( j = n-1; j >= i; --j){
			   if(A[j]<A[j-1]){
				   swap(A[j], A[j-1]);
				   exchange = true;
			   }
		if(!exchange) return;
	  }
   }
}

//**************Insertion Sort**************************
void Insert_sort(int A[], int n){
	  if(n==0) return;
	  int i, j;
	  for(i = 1; i < n;  ++i){
		  int temp = A[i];
		  for(j = i-1; j >=0 && A[j] > temp; --j)
			    A[j + 1] = A[j] ;
		   A[j+1] = temp;
	  }
}
//*********************Selection Sort********************
void Select_sort(int A[], int n){
	  if(n==0) return;
	  int i, j;
	  for(i=0; i < n; --i){
		  int min_num = i;
		  for(j = i+1; j < n; --j)
			  if(A[j] < A[min_num])
				  min_num = j;
		  if(min_num != i)
			  swap(A[min_num],A[i]);
	  }
}
//********************Shell Sort***************************
void Shell_sort(int A[], int n){
	if(n==0) return;
	int gap = n;
	while(gap > 1){
		gap = gap/3 + 1;
		int i, j;
		for(i = gap; i < n; i += gap){
			int temp = A[i];
			for(j = i-gap; j >=0 & A[j] >temp; j -= gap)
				  A[j+gap] = A[j];
			A[j+gap] = temp;
		}
	}
}
//********************Quick Sort*****************************
int partion(int A[], int start, int end){
	  if(NULL == A) return NULL;
	  int i = start;
	  int j = end;
	  int key = A[start];
	  while(i< j){
		    while( i<j &&A[j] >= key) --j;
			A[i] = A[j];
			while(i <j && A[i] <= key) ++i;
			A[j] = A[i];
	  }
	  A[i] = key;
	  return i;
}

void quick_sort(int A[], int left, int right){
	if(NULL == A) return;
	if(left < right){
		int index = partion(A,left, right);
		quick_sort(A,left,index-1);
		quick_sort(A,index+1,right);
	}
}

int  find_kth_smallest(int A[], int start, int end, int k){
	  if(A==NULL || start > end) return -1;
	  int index = partion(A,start,end);
      int num = index - start + 1;
	  if(num > k)
		  find_kth_smallest(A, start, index-1, k);
	  else if( num < k)
		  find_kth_smallest(A, index+1,end, k-num);
	  else
		  return A[index];
}
//******************Merge Sort*********************************
void merge(int A[], int temp[], int start, int mid, int end){
	   for(int i =start; i <= end; ++i)
		     temp[i] = A[i];

	   int i = start, j = mid+1, k =start;
	   while(i <= mid && j <= end){
		   if(temp[i] < temp[j])
			    A[k++] = temp[i++];
		   else
			   A[k++] = temp[j++];
	   }
	   while( i <= mid) A[k++] = temp[i++];
	   while( j <= end) A[k++] = temp[j++];
}

void merge_sort(int A[], int temp[], int begin, int end){
	if(NULL == A || NULL == temp) return;
	if( begin < end)
	{
		   int mid = begin + (end - begin) >> 1;
		   merge_sort(A, temp, begin, mid);
		   merge_sort(A, temp, mid+1, end);
		   merge(A,temp,begin,mid,end);
	}
}

//using merge_sort algorithm to count the reverse-pairs in the array A[]
int merge_count(int A[], int temp[], int begin, int mid, int end){
	    for(int i = begin; i <=  end; ++i)
			  temp[i] = A[i];
		int  i = mid, j = end, k = end;
		int count = 0;
		while( i >= begin && j >= mid+1){
			  if(temp[i] > temp[j]){
				   A[k--] = temp[j--];
				   count += j - mid;
			  }else
				   A[k--] = temp[i--];
		}
		while(i >= begin)   A[k--] = temp[i--];
		while(j >= mid+1) A[k--] = temp[j--];
		return count;
}

int merge_reverse(int A[], int temp[], int begin, int end){
	  if(NULL == A || NULL == temp) return 0;
	  if(begin < end){
		   int mid = begin + (end - begin)>>1;
		   int left = merge_reverse(A,temp, begin,mid);
		   int right = merge_reverse(A,temp, mid+1,end);
		   int mer = merge_count(A,temp,begin,mid,end);
		   return left + right + mer;
	  }
	  return 0;
}

//***********counting sort, elements in A is in range 0~k
void counting_sort(int A[], int n, int k){
	  if(NULL == A || k <0) return;
	  int* count =  new int[k+1];
	  memset( count, 0, sizeof(int)*(k+1) );
	  for(int i = 0; i < n; ++i)
		  count[ A[i] ]++;

	  int j = 0;
	  for(int i = 0; i < k; i++){
		  while(count[i]-- > 0)
			  A[j++] = i;  		
	  }
	  delete[] count;
}

void radix_count(int A[], int n, int maxBucket, int d){
	   int* count = new int[maxBucket]();
	   int* B = new int[n]();
	   for(int i = 0; i < n;  i++){
		   int digit = (A[i] >> (i-1)) & 0x01;
		   count[digit]++;

		for(int i = 1; i < maxBucket; i++)
			count[i] += count[i-1];

		for(int i = n-1; i >= 0; --i)
		{
			  int digit = (A[i] >> (i-1)) & 0x01;
			  B[count[digit]-1]= A[i];
			  count[A[i]] --;
		}
		for(int i = 0; i < n; i++)
			    A[i] = B[i];
	   }
}
void radix_sort(int A[], int n, int d){
	if(NULL == A) return;
	for(int i=0; i < n; i++)
		radix_count(A, n, 10, i);
}




int main(){
    int a[] = {2, 3, 4, 5, 6, 1, 8, 9, 0};
    const int n = sizeof(a) / sizeof(a[0]);

	  getchar();
    return 0;
}