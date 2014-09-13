//Author: Xin Junbo
//Date:   2014/09/06

#include<iostream>
#include<vector>
using namespace std;

//One int bit can store 4 bits of char, because in the mul operation ,a[4]*b[4] can be at most 8 bits
//If only consider add and sub operation, on int bit can at most represent 9 bits of char bits.
const int INT_RADIX = 10000;  
const int MAX_LEN = 200;    //maximum bits of the integer
const int LEN = 4;   //one element has 4 bits
const int N = MAX_LEN/4 + 1;  // maximum bits of the array
int x[N], y[N], result[N+1], result2[2*N];
char a[MAX_LEN], b[MAX_LEN]; //

//*********************Big Integer Add Operation*****************
void BigInt_add(const int x[], const int y[], int result[]){
	   for(int i = 0; i <= N; ++i)
		   result[i] = 0;

	   for(int i = 0; i < N; ++i){
		   result[i] = x[i] + y[i] + result[i];
		   if(result[i] >= INT_RADIX){  // overflow
			     result[i] -= INT_RADIX;
				 result[i+1]++;   
		      }
       }
}

//***********************Big Integer Sub**********************
//Input:  x, y,  x>y
//Output:  z = x - y >= 0
void BigInt_sub(const int x[], const int y[], int result[]){
	   for(int i = 0; i < N; ++i)
		   result[i]  = 0;

	   for(int i = 0; i < N; ++i){
		   result[i] = result[i] + x[i] - y[i];
		   if( result[i] < 0){
			   result[i] += INT_RADIX;
			   result[i+1] --;
		      }
         }
}

//************************Big Integer Muliply*******************
//Input:  x, y, x>=0, y>=0
//Output: z = x*y >= 0
void BigInt_mul(const int x[], const int y[], int result[]){
	  for( int i = 0; i < N*2; ++i )
		  result[i] = 0;

	  for(int i = 0; i < N; ++i){
		    for(int j = 0; j < N; ++j){
				  result[i+j] = result[i+j] + x[i] * y[j];
				  if(result[i+j] >= INT_RADIX){
					   result[i+j+1] = result[i+j]/INT_RADIX;
					   result[i+j] = result[i+j] % INT_RADIX;
				  }
			}
	  }
}

//******************************Big Integer Mod*********************
int BigInt_mod(const int x[], int y){
	int result = 0;
	for(int i = N-1; i >= 0; --i)
		result = (result * INT_RADIX + x[i]) %y;
	return result;
}
//**********Convert char array a[]  to int array result[]******************
void BigInt_input(const char a[], int result[]){
	  int i,  j=0, k;
	  const int len = strlen(a);
	  for(i = 0; i < N; ++i)
		  result[i] = 0;

	  for(int i = len; i > 0; i -= LEN){
		    int temp = 0;
			const int low = i - LEN > 0? i - LEN: 0;
			for(k = low; k < i; ++k){
				 temp = temp*10 + a[k] - '0';
			}
			 result[j++] = temp;
	    }
}

//************************print the big int x**********************
void  BigInt_print(const int x[], const int n){
	bool start = false;
	int i = n  -1;
	while( i >= 0 && x[i] == 0 ) --i;
	if( i <0) printf("0");
	for(; i >=0; --i)
			printf("%04d", x[i]);
	}

int main(void){
	strcpy(a, "134534421948234");
	strcpy(b,   "76643571038290");
	BigInt_input(a, x);
	BigInt_input(b,y);
	BigInt_add(x, y, result);
	cout << a << " + "  << b  << " = ";
	BigInt_print(result, N);
	cout << endl;
    BigInt_sub(x, y, result);
	cout << a << " - " << b << " = " ;
	BigInt_print(result, N);
	cout << endl;
	BigInt_mul(x,y,result2);
	cout << a << " * " << b << " = ";
	BigInt_print(result2, 2*N);
	cout << endl;
	getchar();
	return 0;
}
	
