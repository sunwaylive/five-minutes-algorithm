#include <iostream>
#include <cassert>
#include <cstdio>
#include <algorithm>
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

};


int main()
{
    char str[] = "abcaaabaabcabc";
    cout<<longest_palindrome(str)<<endl;
    return 0;
}
