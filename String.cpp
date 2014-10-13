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

//stl 中 string的源代码, stl 中string 是小写的
class String{
private:
    unsigned len;
    char *pbuf;
public:
    String() : len(0), pbuf(0){}
    String(const String&);
    String& operator=(const String&);
    ~String();

    String(const char * str);
    String& operator=(const char *s);

    const char& operator[](unsigned idx) const;
    char& operator[](unsigned idx);

    bool operator==(const String &other);
    String operator+(const String &other) const; // return value, not reference

    const char* c_str() const;
    unsigned length() const;
    unsigned size() const;
    friend ostream& operator<<(ostream &os, const String &s);
    friend istream& operator>>(istream &is, String &s);
};

String::String(const char *str) : len(0), pbuf(0){
    *this = str;
}

String::String(const String &s) : len(0), pbuf(0){
    *this = s;
}

String::~String(){
    if(pbuf != 0){
        delete[] pbuf;
        pbuf = 0;
    }
}
//this is not the best, use "copy and swap" is better to avoid exception in new operator
String& String::operator=(const char *s){
    this->~String();
    len = strlen(s);
    pbuf = strcpy(new char[len + 1], s);
    return *this;
}

String& String::operator=(const String &s){
    if(&s == this)
        return *this;
    this->~String();
    len = s.len;
    pbuf = strcpy(new char[len + 1], s.pbuf);
    return *this;
}

const char& String::operator[](unsigned idx) const{
    return pbuf[idx];
}

char& String::operator[](unsigned idx){
    return pbuf[idx];
}

String String::operator+(const String &other) const{
    String newString;
    if(other.pbuf == NULL){
        newString = *this;
    }else if(this->pbuf == NULL){
        newString = other;
    }else{
        newString.pbuf = new char[strlen(pbuf) + strlen(other.pbuf) + 1];
        strcpy(newString.pbuf, pbuf);
        strcat(newString.pbuf, other.pbuf);
    }
    return newString;
}

bool String::operator==(const String &other){
    if(strlen(pbuf) != strlen(other.pbuf)) return false;
    else return (strcmp(pbuf, other.pbuf) == 0 ? true : false);
}

const char* String::c_str() const{
    return pbuf;
}

unsigned String::length() const{
    return len;
}

unsigned String::size() const{
    return len;
}

ostream& operator<<(ostream &os, const String &s){
    os<<s.c_str();
    return os;
}

istream& operator>>(istream &is, String &s){
    //cout<<"here: " <<endl;
    char temp[256];
    is>>setw(256)>>temp;
    s = temp;
    return is;
}

int main()
{
    String s1 = "hello";
    String s2 = "hello";
    cout<<(s1 == s2) <<endl;
    return 0;
}
