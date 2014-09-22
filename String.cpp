#include <iostream>
#include <cassert>
#include <cstdio>
#include <algorithm>
#include <iomanip> // for class String
using namespace std;

char* strstr(char *txt, char *pat){
    if(txt == NULL || pat == NULL) return NULL;
    int t_len = strlen(txt);
    int p_len = strlen(pat);

    int i, j;
    for(i = 0; i <= t_len - p_len; ++i){
        for(j = i; j < p_len; ++j){
            if(txt[i + j] != pat[j])
                break;
        }
        if(j == p_len) return txt + i;
    }
    return NULL;
}
//************************************************************
void getNext(char *pat, int *next){
    int m = strlen(pat);
    next[0] = -1;
    int i, j = -1;
    for(i = 1; i < m; ++i){
        while(j > -1 && pat[i] != pat[j + 1]) j = next[j];
        if(pat[i] == pat[j + 1]) j++;
        next[i] = j;
    }
}

void kmp(char *txt, char *pat){
    if(txt == NULL || pat == NULL) return ;
    const int t_len = strlen(txt);
    const int p_len = strlen(pat);
    int *next = new int[p_len]();
    getNext(pat, next);

    int i, j = -1;
    for(i = 0; i < t_len; ++i){
        while(j > -1 && txt[i] != pat[j + 1]) j = next[j];
        if(txt[i] == pat[j + 1]) j++;
        if(j == p_len - 1){
            cout<<"found: " << i - j + 1 <<" ";
        }
    }
    delete next;
}

//************************************************************
char* strcpy(char *to, char *from){
    assert(to != NULL && from != NULL);
    char *p = to;
    while((*p++ = *from++) != '\0') ;
    return to;
}

//************************************************************
char* strcat(char *dst, const char *src){
    if(dst == NULL || src == NULL) return dst;
    char *p = dst;
    while(*p != '\0') p++;
    while((*p++ = *src++) != '\0');
    return dst;
}

//************************************************************
int strcmp(const char *str1, const char *str2){
    while(*str1 == *str2){
        if(*str1 =='\0')
            return 0;
        str1++, str2++;
    }
    return *str1 - *str2;
}

//************************************************************
void *memcpy(void *dst, const void *src, size_t count){
    assert(dst != NULL && src != NULL);
    char *s_dst = (char*)dst, *s_src = (char*)src;
    for(size_t i = 0; i < count; ++i){
        s_dst[i] = s_src[i];
    }
    return s_dst;
}

//************************************************************
size_t strlen(const char *str){
    const char *s;
    for(s = str; *s; ++s);
    return (s - str);
}

//************************************************************
void reverse(char *str, int s, int e){
    if(str == NULL) return;
    while(s < e){
        swap(str[s++], str[e--]);
    }
}

char* rightRotate(char *str, int k){
    if(str == NULL) return NULL;

    int len = strlen(str);
    k %= len;// if k > len
    k = len - 1 - k; // find split position
    reverse(str, 0, k);
    reverse(str, k + 1, len - 1);
    reverse(str, 0, len - 1);
    return str;
}

char* leftRotate(char *str, int k){
    if(str == NULL) return NULL;
    int len = strlen(str);
    k %= len;
    reverse(str, 0, k - 1);
    reverse(str, k, len - 1);
    reverse(str, 0, len - 1);
    return str;
}
//************************************************************
int longest_palindrome(char *str){
    if(str == NULL) return 0;
    const int len = strlen(str);
    int max_len = 0;
    for(int i = 0; i < len; ++i){
        int hui_len = 1;
        int l = i - 1, r = i + 1;
        while(l >= 0 && r < len && str[l] == str[r]){
            l--, r++;
        }
        hui_len = r - l + 1 - 2;
        max_len = max(hui_len, max_len);
    }
    return max_len;
}

class String{
    friend istream& operator>> (istream &, string &);
    friend ostream& operator<< (ostream &, string &);
public:
    String(const char *str = NULL);
    String(const String &other);
    ~String(){ delete[] m_data; }

    String& operator=(const String &other);
    String operator+(const String &other) const;//return value can't be a reference of itself
    bool operator==(const String &other);
    char& operator[](unsigned int);

    size_t size(){ return strlen(m_data); }
private:
    char *m_data;
};

inline String::String(const char *str){//because default param is given, this becomes a default cons
    if(str == NULL) m_data = NULL;
    else{
        m_data = new char[strlen(str) + 1];
        strcpy(m_data, str);
    }
}

//copy cons, other can't be itself! No need to delete old memory
inline String::String(const String &other){
    if(other.m_data == NULL){
        m_data = NULL;
    }else{
        m_data = new char[strlen(other.m_data) + 1];
        strcpy(m_data, other.m_data);
    }
}

inline String& String::operator=(const String &other){
    if(&other != this){
        delete[] m_data;
        if(other.m_data == NULL){
            m_data = NULL;
        }else{
            m_data = new char[strlen(other.m_data) + 1];
            strcpy(m_data, other.m_data);
        }
    }
    return *this;
}

inline String String::operator+(const String &other) const{
    String newString;
    if(other.m_data == NULL){
        newString = *this;
    }else if(m_data == NULL){
        newString = other;
    }else{
        newString.m_data = new char[strlen(m_data) + strlen(other.m_data) + 1];
        strcpy(newString.m_data, m_data);
        strcat(newString.m_data, other.m_data);
    }
    return newString;
}

inline bool String::operator==(const String &other){
    if(strlen(m_data) != strlen(other.m_data)){
        return false;
    }
    else {
        return (strcmp(m_data, other.m_data) == 0) ? true : false;
    }
}

inline char& String::operator[](unsigned int e){
    if(e >= 0 && e <= strlen(m_data)){
        return m_data[e];
    }
}

ostream& operator<<(ostream &os, String &str){//this method must be friend function, not member function
    os<< str.m_data;
    return os;
}

istream& operator>>(istream &is, String &str){
    char tmp[255];
    is>>setw(255)>>tmp;
    str = tmp;
    return is;
}

int main()
{
    char str[] = "abcaaabaabcabc";
    cout<<longest_palindrome(str)<<endl;
    return 0;
}
