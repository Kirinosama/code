#include<iostream>  
#include<cstdio>  
#include<cstdlib>  
#include<cmath>  
#include<cstring>  
#include<string>  
#include<map>  
#include<algorithm>  
#include<queue>  
using namespace std;  
int n;  
int a[1000005],b[1000005];  
int e[1000005];  
queue<int>que;  
priority_queue<int>Q;  
int cnt=0,ans=0,tot=0;  
int main()  
{  
    int i,j,k,t,l;  
    scanf("%d",&n);  
    for(i=1;i<=n;i++){  
        scanf("%d",&a[i]);  
        if(a[i]==1){cnt++;b[cnt]=i;}  
        }  
    b[cnt+1]=n+1;   
    for(i=1;i<=cnt;i++){  
        if(b[i+1]-1-b[i-1]>ans){  
        for(j=b[i+1]-1;j>b[i-1];j--){  
            if(e[a[j]]==0){  
               Q.push(a[j]);  
               que.push(a[j]);  
               e[a[j]]=1;  
               tot++;  
               }  
            else{  
                 while(que.front()!=a[j]){  
                      while(!e[Q.top()])Q.pop();  
                         k=Q.top();  
                      if(k==tot)ans=max(k,ans);  
                      t=que.front();  
                      e[t]=0;tot--;que.pop();  
                      }  
                 }  
            }  
         if(tot!=0){  
            if(e[1]==1)if(Q.top()==tot)ans=max(ans,Q.top());  
            while(!que.empty()){t=que.front();e[t]=0;tot--;que.pop();}  
            while(!Q.empty())Q.pop();  
            }  
         }  
        }  
    printf("%d",ans);  
    return 0;  
}  