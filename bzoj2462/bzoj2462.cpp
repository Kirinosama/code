#include <cstdio>  
#include <bitset>  
#include <cstring>  
#include <iostream>  
#include <algorithm>  
#define MAX 1100  
using namespace std;  
const unsigned int BASE1 = 10016957;  
const unsigned int BASE2 = 10016957;  
const int MO = 99999997;  
   
int m,n,ask_m,ask_n,asks;  
unsigned int hash[MAX][MAX],_hash[MAX][MAX];  
unsigned int pow1[MAX],pow2[MAX];  
   
bool set[100000000];  
   
inline unsigned int GetHash()  
{  
    for(int i = 1; i <= ask_m; ++i)  
        for(int j = 1; j <= ask_n; ++j)  
            _hash[i][j] += _hash[i - 1][j] * BASE1;  
    for(int i = 1; i <= ask_m; ++i)  
        for(int j = 1; j <= ask_n; ++j)  
            _hash[i][j] += _hash[i][j - 1] * BASE2;  
    return _hash[ask_m][ask_n];  
}  
   
int main()  
{  
    cin >> m >> n >> ask_m >> ask_n;  
    for(int i = 1; i <= m; ++i)  
        for(int j = 1; j <= n; ++j)  
            scanf("%1d",&hash[i][j]);  
    pow1[0] = pow2[0] = 1;  
    for(int i = 1; i <= 100; ++i)  
        pow1[i] = pow1[i - 1] * BASE1,pow2[i] = pow2[i - 1] * BASE2;  
    for(int i = 1; i <= m; ++i)  
        for(int j = 1; j <= n; ++j)  
            hash[i][j] += hash[i - 1][j] * BASE1;  
    for(int i = 1; i <= m; ++i)  
        for(int j = 1; j <= n; ++j)  
            hash[i][j] += hash[i][j - 1] * BASE2;  
    for(int i = ask_m; i <= m; ++i)  
        for(int j = ask_n; j <= n; ++j) {  
            unsigned int h = hash[i][j];  
            h -= hash[i - ask_m][j] * pow1[ask_m];  
            h -= hash[i][j - ask_n] * pow2[ask_n];  
            h += hash[i - ask_m][j - ask_n] * pow1[ask_m] * pow2[ask_n];  
            set[h % MO] = true;  
        }  
    for(cin >> asks; asks--;) {  
        for(int i = 1; i <= ask_m; ++i)  
            for(int j = 1; j <= ask_n; ++j)  
                scanf("%1d",&_hash[i][j]);  
        puts(set[GetHash() % MO] ? "1":"0");  
    }  
    return 0;  
}  
