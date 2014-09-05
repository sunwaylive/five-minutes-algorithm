//Author: Xin Junbo
//Date: 2014/09/05

#include<iostream>
#include<vector>
#include<algorithm>
using namespace std;

//*******************************Permutations*****************************************
//Given a collection of numbers, return all possible permutations.
//For example,
//[1,2,3] have the following permutations:
//[1,2,3], [1,3,2], [2,1,3], [2,3,1], [3,1,2], and [3,2,1].
class Permutations {
public:
	bool isVisited[200];
	void DFS(vector<vector<int> >&result,  vector<int> &temp, vector<int> &num, int index){
		if(temp.size() == num.size() ){
			   result.push_back(temp);
			   return;
		   }
		   for(size_t i=0; i < num.size(); i++){
			      if( !isVisited[i]){
					  temp.push_back(num[i]);
					  isVisited[i] = true;    // mark the currrent num
					  DFS(result, temp, num, i+1); //deep search
					  isVisited[i] =  false;  // restore
					  temp.pop_back();
				  }
		   }
	}
    vector<vector<int> > permute(vector<int> &num) {
           vector<vector<int> > all;
		   vector<int> temp;
		   memset(isVisited,false,sizeof(isVisited));
		   DFS(all,temp,num,0);
		   return all;     
       }
};

//**********************************Permutations II**************************************
//Given a collection of numbers that might contain duplicates, return all possible unique permutations.
//For example, [1,1,2] have the following unique permutations  [1,1,2], [1,2,1], and [2,1,1].
class PermutationsII {
public:
	bool isVisted[200];
	void DFS(vector<vector<int> >&result, vector<int> &temp,  vector<int> &num, int index){
		  if(temp.size() == num.size()){
			  result.push_back(temp);
			  return;
		  }

		  for(int i = 0; i < num.size(); ++i){
			  if(! isVisted[i] ){
				  if( i != 0 && num[i] == num[i-1] && !isVisted[i-1] )   // Important!
					  continue;   
				  temp.push_back(num[i]);
				  isVisted[i] = true;   //marked the current num as visited
				  DFS(result, temp, num, i+1);  //deep search
				  isVisted[i] = false;  //restore
				  temp.pop_back();
			  }
		  }
	}
    vector<vector<int> > permuteUnique(vector<int> &num) {
		     vector<vector<int> > all;
			 vector<int> temp;
			 sort(num.begin(), num.end()); // different from permutation, must sort first
             memset(isVisted, false, sizeof(isVisted));
			 DFS(all, temp, num, 0);
			 return all;
    }
};

//***************************************Next Permutation****************************************
//Implement next permutation, which rearranges numbers into the lexicographically next greater permutation of numbers.
//If such arrangement is not possible, it must rearrange it as the lowest possible order (ie, sorted in ascending order).
//The replacement must be in-place, do not allocate extra memory.
//Here are some examples. Inputs are in the left-hand column and its corresponding outputs are in the right-hand column.
//1,2,3 ¡ú 1,3,2
//3,2,1 ¡ú 1,2,3
//1,1,5 ¡ú 1,5,1
class NextPermutation{
public:
	//Using the STL algorithm 'next_permutation'
    void nextPermutation(vector<int> &num){
		   int length = num.size();
		   if(length == 0 || length == 1)  return;
           int i = length -2;
		   //******find the first pair that num[i] >= num[i+1]
		    while( i>=0 && num[i] >= num[i+1] )   i--;
			if(i>=0) { //not till the begin of the vector, find the first element bigger than num[i]
				   int j = length -1;
				   while(num[j] <= num[i])  j--;
				   swap(num[i], num[j]);				  
			  }
			vector<int>::iterator begin = num.begin() + (i +1);
			reverse( begin,  num.end());			     
    }
};

//*********************Permutation Sequence****************************
//The set [1,2,3,¡­,n] contains a total of n! unique permutations.
//By listing and labeling all of the permutations in order,
//We get the following sequence (ie, for n = 3):
//"123", "132", "213", "231", "312", "321"
//Given n and k, return the kth permutation sequence.
//Note: Given n will be between 1 and 9 inclusive.
class PermutationSequence {
public:
    string getPermutation(int n, int k){
           string result;
		   int F[10];
		   bool isVisted[10];
		   F[0] =1;
		   for(int i =1; i < 10; i++)
			   F[i] = F[i-1] * i;
		   memset(isVisted, 0, sizeof(isVisted));
		   -- k;
		   for(int i = n-1; i >= 0; i--) {
			      int temp = k/F[i];
				  int j =1;
 				  for( ; j < 10 ; j++){
  					     if( isVisted[j] == 0) temp --;
 						 if(temp < 0 )	 break;
				  }
				  result += '0' + j;
				  k %= F[i];
				  isVisted[j] = 1;
		   }     
		   return result;    
    }
};

//********************************Combinations***************************************
//Given two integers n and k, return all possible combinations of k numbers out of 1 ... n.For example,
//If n = 4 and k = 2, a solution is:  [ [2,4],  [3,4],  [2,3],  [1,2],  [1,3],  [1,4],  ]
class Combinations {
public:
	//Num is the left number, max to k;  k == k,   max == n; 
	void DFS( int Num, int k,  int max, int index, vector<int> temp, vector<vector<int> > &result){
		    if(Num == 0){
				result.push_back(temp);
				return;
			}
			 for(size_t i=index; i <= max; i++){
				 temp.push_back(i);
				  DFS(Num-1, k, max,  i+1, temp,result);  
				  temp.pop_back();   
			 }
	}
            vector<vector<int> > combinations(int n,  int k){
            vector<vector<int> > final;
			vector<int> tempResult;
			DFS(k, k , n, 1,tempResult, final);
			return final;      
    }
};

//******************************Subsets**************************************
//Given a set of distinct integers, S, return all possible subsets.
//Note: Elements in a subset must be in non-descending order.
//The solution set must not contain duplicate subsets. For example,
//If S = [1,2,3], a solution is:  [  [3],  [1],  [2],  [1,2,3],  [1,3],  [2,3],  [1,2],  []  ]
class Subsets {
public:
     void DFS(vector<int> &S, int index, vector<int> temp, vector<vector<int> > &result){
	      if(index == S.size()){
			  result.push_back(temp);
			  return;
		  }
		  DFS(S, index+1, temp, result);     //not include current element
		  temp.push_back(S[index]);
		  DFS(S, index+1, temp, result);     //include current element			
	}

    vector<vector<int> > subsets(vector<int> &S) {
        sort(S.begin(), S.end());
		int len = S.size();
		vector<int> singleRes;
		vector<vector<int> > res;
		DFS(S, 0, singleRes, res);
		return res;
    }
};

//*****************************Subsets II****************************************
//Given a collection of integers that might contain duplicates, S, return all possible subsets.
//Note:Elements in a subset must be in non-descending order.
//The solution set must not contain duplicate subsets. For example,
//If S = [1,2,2], a solution is: [  [2], [1], [1,2,2], [2,2], [1,2], [] ]
class SubsetsII {
public:
    void DFS(vector<int> &S, int index, vector<int>&temp, vector<vector<int> >& result){
		  result.push_back(temp);
		  for(int i = index;  i < S.size();  i++){
			  if(i != index && S[i] == S[i-1]) continue;
			  temp.push_back(S[i]);
			  DFS(S, i+1, temp, result);
			  temp.pop_back();
	   }
    }

    vector<vector<int> > subsetsWithDup(vector<int> &S) {
        sort(S.begin(),S.end());
		vector<vector<int> > res;
		vector<int> temp;
		DFS(S,0,temp, res);
		return res;
    }
};

//*******************************Combinations Sum***************************************
//Given a set of candidate numbers (C) and a target number (T), 
//find all unique combinations in C where the candidate numbers sums to T.
//The same repeated number may be chosen from C unlimited number of times.   Note:
//All numbers (including target) will be positive integers.
//Elements in a combination (a1, a2, ¡­ , ak) must be in non-descending order. (ie, a1 ¡Ü a2 ¡Ü ¡­ ¡Ü ak).
//The solution set must not contain duplicate combinations.
//For example, given candidate set 2,3,6,7 and target 7, 
//A solution set is: [7]    [2, 2, 3] 
// reference of mannual c++ pp.156-pp.157
class CombinationSum {
public:
		void DFS(vector<int> nums, int gap, int current, vector<int> &temp, vector<vector<int> > &result){
		//     find onde solution
		if( gap == 0){ 
			result.push_back(temp);
			return;
		}
		for(size_t i=current;i<nums.size();i++){
			    if(gap < nums[i])   return ;  // cut it down
				temp.push_back(nums[i]);
				DFS(nums,gap-nums[i],i,temp,result);
				temp.pop_back();
		}		   
	}

    vector<vector<int> > combinationSum(vector<int> &candidates, int target){
		sort(candidates.begin(),candidates.end());
          vector<vector<int> > result;
		  vector<int> temp;
		  DFS(candidates,target,0,temp,result);
		  return result;     
    }
};

//*****************************Combinations Sum II***************************************
//Given a collection of candidate numbers (C) and a target number (T), 
//find all unique combinations in C where the candidate numbers sums to T.
//Each number in C may only be used once in the combination.  Note:
//All numbers (including target) will be positive integers.
//Elements in a combination (a1, a2, ¡­ , ak) must be in non-descending order. (ie, a1 ¡Ü a2 ¡Ü ¡­ ¡Ü ak).
//The solution set must not contain duplicate combinations.
//For example, given candidate set 10,1,2,7,6,1,5 and target 8, 
//A solution set is: [1, 7]   [1, 2, 5]   [2, 6]   [1, 1, 6] 
class CombinationSum2 {
public:
    vector<vector<int> > combinationSum2(vector<int> &num, int target) {
          sort(num.begin(),num.end());
		  vector<vector<int> > result;
		  vector<int> temp;
		   DFS(num,target,0,temp,result);
           return result;
    }
	void DFS(vector<int>&num, int gap, int current, vector<int>  &temp, vector<vector<int> > &result){
		if(gap == 0){
			 result.push_back (temp);
			 return;
		}
		int last = -1;  // mark last time vist
		for(size_t  i= current; i< num.size(); i++){
				if(last == num[i])  continue;   //make sure that the value has not yet been visited
			    if(gap < num[i] )  return;    //cut it down
			    last = num[i];
				temp.push_back(num[i]);
				DFS(num,gap-num[i],i+1,temp,result);  //the current index becomes i+1, not i
				temp.pop_back ();
		}
	}
};

//*****************************Gray Code***********************************
//The gray code is a binary numeral system where two successive values differ in only one bit.
//Given a non-negative integer n representing the total number of bits in the code, 
//print the sequence of gray code. A gray code sequence must begin with 0.
//For example, given n = 2, return [0,1,3,2]. Its gray code sequence is:
//00 - 0
//01 - 1
//11 - 3
//10 - 2
//Note: For a given n, a gray code sequence is not uniquely defined
//For example, [0,2,3,1] is also a valid gray code sequence according to the above definition.
class GrayCode {
public:
    vector<int> grayCode(int n) {
        vector<int> result ;
	   int size = 1<< n;
	   result.resize(size);
	   for(int i = 0; i < size; i++){
		   int temp = i ^ i >>1;
		   result[i] = temp;
	   }
	   return result;
    }
};

//**************************test*********************************
int main(void){
	Permutations a;
	PermutationsII p;
     int arr[] = {1,1,1,4};
	vector<int> num;
	for(int i=0; i< sizeof(arr)/sizeof(int);i++)
		num.push_back (arr[i]);
	vector<vector<int> > result = a.permute(num);
	vector<vector<int> >::iterator outside;
	vector<int>::iterator inside;
	for(outside=result.begin(); outside != result.end(); outside++){
		  for(inside = outside -> begin(); inside != outside -> end(); inside++)
			    cout << *inside << " " ;
		  cout << endl;
	}

	 getchar();
	 return 0;
}