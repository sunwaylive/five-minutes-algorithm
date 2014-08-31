#include<iostream>

using namespace std;

void swap(int A[], int i, int j){
	int temp = A[i];
	A[i] = A[j];
	A[j] = temp;
}

void BubbleSort(int A[], int size){
	int i,j;
	for(i = 0; i < size; i ++){
		bool swap_flag = false;
		for(j = size - 1; j > i; j --){
			if(A[j] < A[j-1]){
				swap(A,j,j-1);
				swap_flag = true;
			}
		}
		if(swap_flag == false){
			break;
		}
	}
}

void ShellSort(int A[], int size){
	int h = 1;
	while(h < size / 3) h = 3*h + 1;
	int i,j;
	while(h >= 1){
		//insertion sort
		for(i = h; i < size; i ++){
			for(j = i; j >= h; j = j - h){
				if(A[j] < A[j - h]){
					swap(A, j, j - h);
				}else{
					break;
				}
			}
		}
		h = h / 3;
	}
}

int partition(int A[], int i, int j){
	// 前提条件i < j;
	int left = i;
	int right = j+1;

	int n = A[left];
	while(1){
		//while(++left < right && A[left] < n);
		while(A[++left] < n){
			if(left == right)
				break;
		}
		//while(--right >=left && A[--right] > n);
		while(A[--right] > n){
			if(left == right){
				break;
			}
		}
		if(left < right){
			swap(A, left ,right);
		}else{
			break;
		}
	}
	swap(A, i, right);
	return right;

}

void QuickSort(int A[], int i, int j){
	if(i >= j){
		return;
	}
	int n = partition(A, i, j);
	QuickSort(A, i, n -1);
	QuickSort(A, n + 1, j);


}

void Quick3Sort(int A[], int lo, int hi){
	if(lo >= hi)
		return;
	int lt = lo;
	int gt = hi;
	int v = A[lo];
	int i = lo;
	while(i <= gt){
		if(A[i] < v){
			swap(A, i++, lo++);
		}else if(A[i] > v){
			swap(A, i, gt--);
		}else{
			i++;
		}
	}
	Quick3Sort(A, lo, lt-1);
	Quick3Sort(A, gt+1, hi);
}


#define BITS_LENGTH 32

int bucket1[100];
int bucket2[100];

void RadixSort(int A[], int size){
	int i;
	int j;
	int size1;
	int size2;

	for(i = 0; i < BITS_LENGTH; i ++){
		size1 = 0;
		size2 = 0;
		for(j = 0; j < size; j ++){
			if((A[j] >> i) & 1){
				bucket2[size2++] = A[j];
			}else{
				bucket1[size1++] = A[j];
			}
		}
	    int index1 = 0, index2 = 0;
	    while(index1 < size1){
	    	A[index1] = bucket1[index1];
	    	index1 ++;
	    }

	    while(index2 < size2){
	    	A[index1 + index2] = bucket2[index2];
	    	index2 ++;
	    }

	}
}

int main(){

	int A[] = {3,8,1,4,3,9,7,1,4,3};
	Quick3Sort(A, 0, 9);
	int i;
	for(i = 0; i < 10; i ++){
		cout << A[i] << " ";
	}
	cout << endl;

}

