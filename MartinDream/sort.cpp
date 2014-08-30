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

int main(){

	int A[] = {3,8,1,4,3,9,7,1,4,3};
	Quick3Sort(A, 0, 9);
	int i;
	for(i = 0; i < 10; i ++){
		cout << A[i] << " ";
	}
	cout << endl;

}

