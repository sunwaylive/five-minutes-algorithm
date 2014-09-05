//Author:  Xin Junbo
//Date: 2014/09/05
//Version 1.0.

#include<iostream>
#include<vector>
#include<string>
using namespace std;

//*******Longest Common Substring(LCS)--must contiguous********
//************Solution**************
//not the best solution using O(n) space, here Space Comlexity: O(N1N2)
//Time Complexity:  O(N1N2)
//dp[i][j] means: the maximun common string of s1[0...i] and  s2[0..j] 
//if s1[i]==s2[j],  obviously, dp[i][j] = dp[i-1][j-1] + 1
//start1 and start2 means the start of common string in s1 and s2
string LCString(string s1, string s2){
	int n1 = s1.length();
	int n2 = s2.length();
	int maxLen = 0;
	int start1 = -1, start2 = -1;
	vector<vector<int> > dp(n1, vector<int>(n2,0));
	for(int j = 0; j < n2; ++j)
	{
		 if(s2[j] == s1[0]){
		    dp[0][j] = 1;
		    if(maxLen == 0){
			    maxLen = 1;
			    start1 = 0;
			    start2 = j;
		     }
		  }
	}
	for(int i = 1; i < n1; ++i){
		if(s1[i] == s2[0]){
		      dp[i][0] = 1;
			  if(maxLen == 0){
				  maxLen = 0;
				  start1 = i;
				  start2 = 0;
			  }
		  } //end if
		  for(int j = 1; j < n2; ++j){
			  if(s1[i] ==s2[j]){ 
				   dp[i][j] = dp[i-1][j-1] + 1;
				   if(maxLen < dp[i][j]){
					   maxLen = dp[i][j];
					   start1 = i - maxLen +1;
					   start2 = j - maxLen + 1;
				   }			   
			  }
		  } // end j while
	} //end  i while
	return s1.substr(start1,maxLen);
}

//*****Longest Common Sequence(LCS) problem****can be non-contiguous*****
//*********Solution**************
//A bit different from the continous LCS, d is a two-dimension array
//d[i][j] means the current max numbers of s1[0...i] and s2[0....j]
//State shift equation:
//For X = (X1, X2,....,Xm) and Y = (Y1,Y2,...., Ym), the LCS is Z = (Z1, Z2, ...Zk)
//1) if Xm == Yn,  then Zk = Xm = Yn, and Z(k-1) is the LCS of  X(m-1) and Y(m-1)
//2) if Xm !=  Yn and Zk != Xm,  then Z is the LCS of X(m-1) and Y
//3) if Xm !=  Yn  and Zk != Yn,  then Z is the LCS of X and Y(n-1)
int LCSubsquence(string s1, string s2){
	int n1 = s1.length();
	int n2 = s2.length();
	vector<vector<int> > d(n1, vector<int>(n2, 0));
	for(int i = 1; i < n1; ++i){
		for(int j = 1;  j < n2; ++j){
			if(s1[i-1] == s2[j-1])
				d[i][j] = d[i-1][j-1] +1;
			else
				d[i][j] = max(d[i][j-1], d[i-1][j]);
		}
	}
	return d[n1-1][n2-1];
}

//***************Longest Increasing Subsequence*********************
//***********Solution************
//1) exhausion method: Time Complexity:  O(N^2)
//DP:   dp[i] = max(1, dp[j]+1),  A[i] > A[j], 0<= j < i
int LIS_basic(int A[], int n){
	int *dp = new int[n];
	int maxNum = 0;
	for(int i =0; i < n; ++i){
		dp[i] = 1;
		for(int j = 0; j < i; ++j){
			 if(A[i] > A[j] && dp[j]+1 > dp[i])
				 dp[i] = dp[j] + 1;
		   }
	     maxNum = max(maxNum, dp[i]);
      }
	return maxNum;
}

//2) better method using binary search: Time Complexity: O(NlogN)
//DP: using an array B[] to record the current longest subsequence
//for A[0,...,i], and B[0...,maxLen-1], if A[i] > B[maxLen-1], add A[i]  at the end of B[maxLen-1]
//if A[i] < B[maxLen-1], since B[] is a sorted array, find the corrent pos to replace B[pos] with A[i]
int binary_search(int A[], int start, int end, int key){
	int left = start;
	int right = end;
	while(left <= right){
		int mid = left + ((right-left) >>1);
		if(A[mid] > key)
			right = mid -1;
		else if(A[mid] < key)
			left = mid+1;
		else 
			return mid;  //return the position to replace the element here
	}
	   return left;  // if not find the key
}

int LIS_better(int A[], int n){
	if(n==0) return 0;
	int* B = new int[n];
	B[0] = A[0];
	int pos = 0;
	int maxLen = 1;
	for(int i =1; i < n; ++i){
		if(A[i] > B[maxLen-1]){
			 B[maxLen++] = A[i];   //add it at the end of B and update maxLen
		}else{
			pos = binary_search(A,0,n-1,A[i]);
			B[pos] = A[i];  //notice:  replace B[pos], not insert!
		}
	}
	return maxLen;
}

//*******************Longest Decreasing Subsequence**************
//***********Solution***************
//1) exhausion method: Time Complexity:  O(N^2)
//DP:   dp[i] = max(1, dp[j]+1),  A[i] <  A[j], 0<= j < i
int LDS_basic(int A[], int n){
	if(n==0) return 0;
	int *dp = new int[n];
	int maxLen = 1;
	for(int i = 0; i < n; ++i){
		dp[i] = 1;
		for(int j = 0; j < i; ++j){
			if(A[j] > A[i] && dp[j] +1 > dp[i])
			    dp[i] = dp[j] + 1;
		}
		maxLen = max(maxLen, dp[i]);
	}
	return maxLen;
}
//A[] is a sorted Decreasing array, different from common Increasing array
int Binary_Search_Reverse(int A[], int low, int high, int key){
	 int left = low, right = high;
	 while(left <= right){
		   int mid = left +( (right - left) >> 1);
		   if(A[mid] > key)
			   left = mid + 1;
		   else if(A[mid] < key)
			   right = mid - 1;
		   else
			   return mid;
	    }
	 return left;
}
//same idea with  LIS_better
int LDS_better(int A[], int n){
	if(n==0) return 0;
	int* B = new int[n];
	int pos = 0;
	int maxLen = 1;
	for(int i = 0; i < n; ++i){
		if(A[i] < B[maxLen -1]){
			B[maxLen++] = A[i];
		}else{
			pos = Binary_Search_Reverse(A,0,n-1,A[i]);
			B[pos] = A[i];
		}
	}
	return maxLen;
}

//******************************Triangle**************************************
//Given a triangle, find the minimum path sum from top to bottom. 
//Each step you may move to adjacent numbers on the row below.
//For example, given the following triangle
//[
//     [2],
//   [3,4],
//  [6,5,7],
//  [4,1,8,3]
//]
//The minimum path sum from top to bottom is 11 (i.e., 2 + 3 + 5 + 1 = 11).
//Bonus point if you are able to do this using only O(n) extra space, where n is the total number of rows in the triangle.

//**********Solution**************
//dp[] is a dynamic one-dimension vector, in which,
//in the i level,  there are i numbers, dp[j] means the previous level i-1, the j+1 number of the level
//for the i level, if j !=0 && j != i, dp[j] = min(dp[j], dp[j-1]) + triangle[i][j]
//If j==0, dp[j] has only one choice, dp[0] = dp[0] + triangle[i][0]
//If j==i, dp[j] has only one choice, dp[j] = dp[j-1] + triangle[i][j], but the dp is initialized with INT_MAX,
//so min(dp[j], dp[j-1]) = min(INT_MAX, dp[j-1]) = dp[j-1]
// after each iteration of i, dp[j]  has one elements added.
int mininumTriangle(vector<vector<int> > &triangle){
	int n = triangle.size();  //lines
	if(n==0)  return 0;
	vector<int> dp(n,  INT_MAX);
	dp[0] = triangle[0][0];
	for(int i = 1; i < n; ++i){
		 for(int j = i; j >=0; --j){
			 if( j==0)
				 dp[j] = dp[0] + triangle[i][0];  //deal with the first column
			 else 
			     dp[j] = min(dp[j], dp[j-1]) + triangle[i][j];
		 }
	}
	int minSum = INT_MAX;
	for(int j=0; j < n; ++j){
		minSum = min(dp[j], minSum);
	}
	  return minSum;
}

//******************Maximum Continuous Subsequence Sum*************
//*********Solution************
//Easy DP problem, dp[i] records the maximum sum of A[0...i], maxSum records the current max
//State shift equation: dp[i] = max(dp[i-1]+A[i], A[i]);
int maxSubarraySum(int A[], int n){
	if(n==0) return INT_MIN;
	int* dp = new int[n];
	dp[0] = A[0];
	int maxSum = A[0];
	for(int i = 1; i < n; ++i){
		dp[i] = max(dp[i-1]+A[i], A[i]);
		maxSum = max(dp[i], maxSum);
	}
	 return maxSum;
}

//***************************Palindrome problem********************************
//*********Basic  Solution**************
// Traversing i from 0 to n, the cur_len records: let i be the center of palindrome ,the maximum length,
// left and right are the symmetric index of the center i
string palindrome_basic(string s){
	string result;
	if( s.empty()) return result;
	int n = s.length();
	int index = 0;
	int maxLen = 0; 

	for(int i =0; i < n; ++i){
		int cur_len = 1;
		int left = i-1;
		int right = i+1;
		while( left >=0 && right <= n-1 && s[left] == s[right]){
			  ++cur_len;
			  --left;
			  ++right;
		   }
		cur_len = right - left - 1;
		if(cur_len > maxLen){
			index = i;
			maxLen = cur_len;
		}
	}
	return s.substr(index - (maxLen-1)/2, maxLen);
}
//*********Better Solution*****************
//manacher algorithm to solve palindrome problem
//prePrecess deals with the odd and even case
string palindromePreprocess(string s){
	string result;
	if(s.empty()) 
		result = "^#";
	else
	     result = "#";
		for(int i =0; i < s.length(); ++i){
			result += "#";
			result += s.substr(i,1);
		}
		result += "$";
		return result;
}
 //Using Manacher Algorithm
        //  ^ # b # a #  b # c # b # a  # b # c #  b # a # c  # c # b # a # $
		//P: 0 1 0 3 0 1 0 7 0 1 0 9 0 1 0 5 0 1 0 1 0 1 2 1 0 1 0 1 0
//P[i] records: let i number of str be the center, the longest palindrome string
//center : the current palindrome center;
//right:     P[i] + center,  the maximum element of currrent center's palindrome range
//           r'                    c                     r             
//   //  ^ # b # a #  b # c # b # a  # b # c #  b # a # c  # c # b # a # $
	 //P: 0 1 0 3 0 1 0 7 
//for example, now i is 8, points to the first c, after calculation, 
//current center is i= 8, P[i] = 7 means the longest palindrome str num of i is 7, and right = i+P[i] = 7+8=15
string palindrome_better(string str)
{
	string newStr = palindromePreprocess(str);
	int n = newStr.length();
	int center = 1;
	int right = 0;
	int maxLen = 0;
	int index = 0;
	int* P =new int[n];
	for(int i = 1; i < n; ++i){
		int i_mirror = 2*center - i;
		if( right > i)
			 P[i] = min(right - i, P[i_mirror]);
		else
			 P[i] = 0;
		while( newStr[i+P[i]+1] == newStr[i-P[i]-1] )
			  P[i]++;
		 if(i + P[i] > right){
			right = i + P[i];
			center = i;
		 }
		  if(maxLen < P[i]){
			   index = i;
			   maxLen = P[i];
		    }
	}
     	return newStr.substr(index - (maxLen-1)/2, maxLen);
}

//******************Maximal Rectangle******************************
//Given a 2D binary matrix filled with 0's and 1's, 
//find the largest rectangle containing all ones and return its area.
int maximaliRectangle(vector<vector<char> > &matrix){
	return 1;
}

//*****************Interleaving String******************************
//Given s1, s2, s3, find whether s3 is formed by the interleaving of s1 and s2.
//For example, Given:
//s1 = "aabcc",
//s2 = "dbbca",
//When s3 = "aadbbcbcac", return true.
//When s3 = "aadbbbaccc", return false.

//****Solution****
//isPart[i][j] is a bool array, means now in s3: s1 has i elements, s2 has j elements
//For the initilization, if j==0, which denotes that s2 has no elments in s3, 
//all the elements in s3 are the same with s1, if s1[i] != s3[i], just break out. Same case if i ==0
//For the state shift problem, isPart[i][j] can departed into two cases:
//1) s1[i-1] == s3[i+j-1] and isPart[i-1][j] is true.     or
//2) s2[j-1] == s3[i+j-1] and isPart[i][j-1] is true.
bool isInterleavingString(string s1, string s2, string s3){
	int n1 = s1.length(), n2 = s2.length(), n3 = s3.length();
	if(n1+n2 != n3) return false;
	if(n1==0) return !s2.compare(s3);
	if(n2==0) return !s1.compare(s3);
	vector<vector<bool> > isPart(n1+1, vector<bool>(n2+1,false));
	isPart[0][0] = 1;
	 for(int i = 0; i < n1; ++i){
		 if(s1[i] == s3[i])
			isPart[i+1][0] = true;
		 else break;
	 } 
	 for(int j = 0; j < n2; ++j){
		 if(s2[j] == s3[j])
			isPart[0][j+1] = true;
		 else break;
	 }

	 for(int i = 1; i <= n1; ++i){
		 for(int j = 1; j <= n2; ++j){
			  isPart[i][j] = (s1[i-1]==s3[i+j-1] && isPart[i-1][j]) ||(s2[j-1]==s3[i+j-1]&& isPart[i][j-1]);
		  }
	 }
       return isPart[n1][n2];
}

//*************************************Scramble string***************************************
/*Given a string s1, we may represent it as a binary tree by partitioning it to two non-empty substrings recursively.
Below is one possible representation of s1 = "great":
    great
   /    \
  gr    eat
 / \    /  \
g   r  e   at
           / \
          a   t
To scramble the string, we may choose any non-leaf node and swap its two children.
For example, if we choose the node "gr" and swap its two children, it produces a scrambled string "rgeat".
    rgeat
   /    \
  rg    eat
 / \    /  \
r   g  e   at
           / \
          a   t
We say that "rgeat" is a scrambled string of "great".
Similarly, if we continue to swap the children of nodes "eat" and "at", it produces a scrambled string "rgtae".
    rgtae
   /    \
  rg    tae
 / \    /  \
r   g  ta  e
       / \
      t   a
We say that "rgtae" is a scrambled string of "great".
Given two strings s1 and s2 of the same length, determine if s2 is a scrambled string of s1.
*/

//when F[i][j][k]=true£¬S1[i..i+k-1] == S2[j..j+k-1], k is the number of char
//when k=1, F[i][j][1] = S1[i] == S2[j]
//when k=2, F[i][j][2] = (F[i][j][1] && F[i+1][j+1][1]) || (F[i][j+1][1] && F[i+1][j][1]
//s1_left==s2_left && s1_right==s2_right   or   s1_left == s2_right && s1_right==s2_left
//F[i][j][1] && F[i+1][j+1][1]  ======> S1[i] == S2[j] && S1[i+1]==S2[j+1]£¨eg£º¡°AC¡± and  ¡°AC¡±£©£¬
 //F[i][j+1][1] && F[i+1][j][1]  ======> S1[i+1] == S2[j] && S1[i] == S2[j + 1] £¨eg£º ¡°AB¡± and ¡°BA¡±£©£¬
 bool isScramble(string s1, string s2) {
         int n= s1.length();
		 int n2 = s2.length();
		if(n != n2) return false;
		bool dp[100][100][100];
		memset(dp,false,sizeof(bool)*100*100*100);
		for(int k = 1; k <= n; ++k){
			for(int i =0; i <= n-k; ++i){
				for(int j = 0; j <= n-k; ++j){
					 if(k ==1)
						 dp[i][j][k] = s1[i]==s2[j];
					 else
						 for(int m = 1; m < k; ++m){
							 if( (dp[i][j][m]&&dp[i+m][j+m][k-m]) || (dp[i][j+k-m][m]&&dp[i+m][j][k-m]) ){
								 dp[i][j][k] = true;
							     break;
							 }//end if
						 }//end m while
				    } //end j while
			} // end i while
		}// end k while
		return dp[0][0][n];
    }

 //****************************Minimun Path Sum**************************************
 //Given a m x n grid filled with non-negative numbers, find a path from top left to bottom right
//	which minimizes the sum of all numbers along its path.
//Note: You can only move either down or right at any point in time.
//Using the DP:  f[i][j] = min( f[i-1][j], f[i][j-1]) + grid[i][j]
 //Notice: Initializition, when i =0  and j =0, there's only one way
 int minPathSum(vector<vector<int> > &grid){
           int m = grid.size();
		   int n = grid[0].size();
		   vector<vector<int> > dp(m,vector<int>(n));
		   int i, j;
		   dp[0][0] = grid[0][0];
		   for(i = 1; i < n; i++)
			   dp[0][i] = dp[0][i-1] + grid[0][i];
		   for(j = 1; j < m;  j++)
			   dp[j][0] = dp[j-1][0] + grid[j][0];

		   for(i = 1; i <  m;  i++)
			     for( j = 1; j <  n;  j++)
					 dp[i][j] = min( dp[i-1][j], dp[i][j-1]) + grid[i][j];
        
            return dp[m-1][n-1];
    }

 //*********************************Edit Distance***************************************
// Given two words word1 and word2, find the minimum number of steps required to convert word1 to word2. 
 //(each operation is counted as 1 step.)
//You have the following 3 operations permitted on a word:
//a) Insert a character
//b) Delete a character
//c) Replace a character
 //*  D[i,j]: the minimal edit distance for the i numbers of s1 and j numbers of s2
 //1. d[0, j] = j;
// 2. d[i, 0] = i;
// 3. d[i, j] = d[i-1, j - 1] if A[i] == B[j]
// 4. d[i, j] = min(d[i-1, j - 1],    substitue
//                          d[i, j - 1],         insert
//                      	 d[i-1, j] ) + 1  if A[i] != B[j]   delete

 int minEditDistance(string word1, string word2){
	     int n1 = word1.length();
		 int n2 = word2.length();
		 vector<vector<int> > dp(n1+1, vector<int>(n2+1,0));
		 for(int i =0 ; i <= n1;  ++i)
			 dp[i][0] = i;
		 for(int j=0; j <= n2; ++j)
			 dp[0][j] = j;
		 for(int i = 1; i <= n1; ++i){
			  for(int j =1; j <= n2; ++j){
				 if(word1[i-1] == word2[j-1])
					 dp[i][j] = dp[i-1][j-1];
				 else
					 dp[i][j] = min( min(dp[i-1][j], dp[i][j-1]), dp[i-1][j-1] ) +1;
			  }
		 }
		    return dp[n1][n2];
 }

//****************Climbing Stairs**********************************
//You are climbing a stair case. It takes n steps to reach to the top.
//Each time you can either climb 1 or 2 steps. In how many distinct ways can you climb to the top?
//*********Solution*************
//Easy solution: Fib array: F(n) = F(n-1) + F(n-2), n>=3
int climbStairs(int n){
	int* d = new int[n+1];
	d[1] = 1, d[2] =2;
	for(int i = 3; i < n+1; ++i)
		d[i] = d[i-1] + d[i-2];
	 return d[n];
}
 
 //*********************************Test******************************************
int main(void){
	//******************LCS***********************
	string s1 = "cbaa";
	string s2 = "acaccbabb";
	string LCSres = LCString(s1,s2);

	//****************Longest Increasing Subsequence*************
	int A[] = {2, 1, 5, 3, 6, 4, 8, 9, 7};
	int LIS = LIS_basic(A,sizeof(A)/sizeof(int));
	int LIS2 = LIS_better(A, sizeof(A)/sizeof(int));

	//***********Interleaving string*********************
	string ss1= "aabcc";
	//string ss2="dbbca";
	string ss2 ="";
	string ss3="aadbbcbcac";
	string ss4="aadbbbaccc";
	string ss5 ="aabcc";
	bool isPart = isInterleavingString(ss1,ss2,ss3);
	bool isPart2 = isInterleavingString(ss1,ss2,ss5);

	//***********mininumTriangle**************
	vector<vector<int> > tri;
	vector<int> temp, temp2;
	temp.push_back(1);
	temp2.push_back(2);
	temp2.push_back(3);
	tri.push_back(temp);
	tri.push_back (temp2);
	int minNum = mininumTriangle(tri);

	//***************Scramble string*****************
	string t1= "greatb";
	string t2="rgtaeb";
	bool isScra= isScramble(t1,t2);

	//**************Edit Distance**********************
	string word1 ="";
	string word2 ="";
	int minDistance = minEditDistance(word1,word2);
	cout << minDistance << endl;

	getchar();
	return 0;
}