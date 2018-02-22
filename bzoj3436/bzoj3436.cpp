#include <queue>  
#include <cstdio>  
#include <cstring>  
#include <iostream>  
#include <algorithm>  
#define MAX 100010  
using namespace std;  
   
int points,asks;  
int head[MAX],total;  
int next[MAX << 1],aim[MAX << 1],length[MAX << 1];  
   
int f[MAX],t[MAX];  
bool v[MAX];  
   
inline void Add(int x,int y,int len)  
{  
    next[++total] = head[x];  
    aim[total] = y;  
    length[total] = len;  
    head[x] = total;  
}  
   
bool SPFA()  
{  
    static queue<int> q;  
    memset(f,0xef,sizeof(f));  
    f[0] = 0;  
    q.push(0);  
    while(!q.empty()) {  
        int x = q.front(); q.pop();  
        v[x] = false;  
        for(int i = head[x]; i; i = next[i])  
            if(f[aim[i]] < f[x] + length[i]) {  
                f[aim[i]] = f[x] + length[i];  
                if(!v[aim[i]]) {  
                    v[aim[i]] = true;  
                    q.push(aim[i]);  
                    if(t[aim[i]] = t[x] + 1,t[aim[i]] > points)  
                        return false;  
                }  
            }  
    }  
    return true;  
}  
   
int main()  
{  
	freopen("bzoj3436.in","r",stdin);
    cin >> points >> asks;  
    for(int flag,x,y,z,i = 1; i <= asks; ++i) {  
        scanf("%d",&flag);  
        if(flag == 2) {  
            scanf("%d%d%d",&x,&y,&z);  
            Add(x,y,-z);  
        }  
        else if(flag == 1) {  
            scanf("%d%d%d",&x,&y,&z);  
            Add(y,x,z);  
        }  
        else {  
            scanf("%d%d",&x,&y);  
            Add(x,y,0);  
            Add(y,x,0);  
        }  
    }  
    for(int i = 1; i <= points; ++i)  
        Add(0,i,0);  
    if(SPFA())  puts("Yes");  
    else    puts("No");  
    return 0;  
}  

