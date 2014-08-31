#include<iostream>
#include<string>
#include"assert.h"
using namespace std;

//********************strcpy***************************
char* strcpy(char* to, const char* from){
	assert(from != NULL && to != NULL);
	char* p = to;
	while((*p++ = *from++) != '\0') ;
	return to;
}
//********************strcat******************************
char* strcat(char*dst, const char* src){
	if(dst == NULL || src == NULL) return dst;
	char*p = dst;
	while(*p != '\0') p++;
	while((*p++ = *src++) != '\0');
	return dst;
}
//*******************strcmp******************************
int strcmp(const char* str1, const char* str2){
	while(*str1 == *str2){
		if(*str1 == '\0') return 0;
		++str1;
		++str2;
	  }
	return  *str1 - *str2;
}
//***********************strStr***************************
char* strStr(char* text, const char*pattern){
	if(text == NULL || pattern == NULL) return text;
	const char* p1, *p2, *p1_advance;
	for(p1_advance = pattern; *pattern; ++pattern)
		p1_advance++;
	for(p1 = text; *p1_advance; p1_advance++){
		char *p1_old = (char*)p1;
		p2 = pattern;
		while(*p1 && *p2 && *p1 == *p2){
			++p1;
			++p2;
		}
		 if(*p2 ==' \0') 
		    	return p1_old;
		 p1 = p1_old+1;
	  }
	return	NULL;
}
//******************strlen*********************************
size_t strlen(char* str){
	const char* s;
	for(s =str; *s; ++s);
	return (s-str);
}
//*******************reverse, left_shift and right_shift**************************
void reverse_str(char* str, int begin, int end){
	if(str == NULL) return;
	while(begin < end){
		  swap(str[begin++], str[end--]);
	}
}

char* left_shift(char* str, int k){
	  if(str == NULL || k==0 ) return str;
	  int len = strlen(str);
	  k %= len;
	  k = len - k; // patition location
	  reverse_str(str, 0, k-1);
	  reverse_str(str, k, len-1);
	  reverse_str(str, 0,len-1);
	  return str;
}

char* right_shift(char* str, int k){
	if(str == NULL || k==0 ) return str;
	int len = strlen(str);
	k %= len;
	reverse_str(str, 0, k-1);
	reverse_str(str, k, len-1);
	reverse_str(str, 0, len-1);
	return str;
}
//*************************longset palindrome************************
//violent method of palindrome
int longest_palindrome(char* str){
	if(str==NULL) return 0;
	int len = strlen(str);
	int maxLen = 0;
	for(int i =0; i < len ; ++i){
		  int cur_len = 1;
		  int left = i-1, right = i+1;
		  while( left >=0 && right <= len-1 && str[left] == str[right]){
			   --left;
			   ++right;
		  }
		  cur_len = right - left -1;
		  maxLen = max(maxLen, cur_len);
	}
	   return maxLen;
}

//manacher method of palidrome
string str_preprocess(string str){
	   size_t len = str.length();
	   string result;
	   if(len ==0) 
		   result = "^#";
	   else
		   result ="^";
	   for(int i =0; i < len; ++i){
		   result  += "#";
		   result += str.substr(i,1);
	   }
	   result += "$";
	   return result;      
}
    //Using Manacher Algorithm
        //  ^ # b # a #  b # c # b # a  # b # c #  b # a # c  # c # b # a # $
		//P: 0 1 0 3 0 1 0 7 0 1 0 9 0 1 0 5 0 1 0 1 0 1 2 1 0 1 0 1 0
int longest_palindrome_better(string str){
        string newStr = str_preprocess(str);
		size_t n = newStr.length();
		int* P = new int[n];
		int center = 0;
		int right = 1;
		int maxLen = 0;
		for(int i = 1; i < n-1; ++i){
			  int i_mirror = 2*center - i;
			  if(right > i)
				  P[i] = min(right-i, P[i_mirror]);
			  else
				  P[i] = 0;
			  while(newStr[i+P[i]+1] == newStr[i-1-P[i]])  //continues to expand, i is the current center
				  P[i]++;
			  if(i+P[i] > right){
				  right = i + P[i];
				  center = i;
			  }
			  maxLen = max(maxLen, P[i]);
		}
		return maxLen;
}

//**************Implentation of string operation***************
class Mystring{
	friend  ostream& operator<<(ostream&, Mystring&);
public:
	Mystring(const char* str = NULL);
	Mystring(const Mystring& other);
	Mystring& operator=(const Mystring& other);
	Mystring operator+(const Mystring& other) const;
	bool operator==(const Mystring&);
	char* operator[](unsigned int);
	size_t size(){ return strlen(m_data); }
	~Mystring(void){if(!m_data) delete[] m_data;}
	
private:
	char* m_data;
	};

//constructor      构造函数
inline Mystring::Mystring(const char* str){
	if(!str) m_data = 0;
	else{
		m_data = new char[strlen(str)+1];
		strcpy(m_data, str);
	}
}
//copy constructor       拷贝构造函数
inline Mystring::Mystring(const Mystring& other){
	if(!other.m_data) m_data = 0;
	else{
		m_data = new char[strlen(other.m_data)+1];
		strcpy(m_data, other.m_data);
	}
}
//operater =        赋值运算重载
inline Mystring& Mystring::operator=(const Mystring& other){
	if(this != &other){
		delete m_data;
		if(!other.m_data) m_data = 0;
		else{
			m_data = new char[strlen(other.m_data)+1];
			strcpy(m_data, other.m_data);
		}
	}
	return *this;
}
//operator +      +号运算重载
inline Mystring Mystring::operator+(const Mystring& other) const{
	   Mystring newstr;
	   if(!other.m_data)
		   newstr = *this;
	   else if(!m_data)
		   newstr = other;
	   else{
		   newstr.m_data = new char[strlen(m_data)+strlen(other.m_data)+1];
		   strcpy(newstr.m_data, m_data);
		   strcat(newstr.m_data, other.m_data);
	   }
	   return newstr;
}
//operator ==      ==运算重载
inline bool Mystring::operator==(const Mystring& other){
	  if(strlen(other.m_data ) != strlen(m_data)) return false;
	  return strcmp(m_data, other.m_data)? false: true;
}

//operator <<     << 友元重载
ostream& operator<<(ostream& os, Mystring& str){
	os << str.m_data;
	return os;
}



int main(void){
	string str = "babcbabcbaccba1";
	int maxLen = longest_palindrome_better(str);
	cout << maxLen << endl;

	char* str2 = "babcbabcb";
	int maxLen2 =  longest_palindrome(str2);
	cout << maxLen2 << endl;

	getchar();
	return 0;
}