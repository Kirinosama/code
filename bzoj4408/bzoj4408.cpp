#include<iostream>  
#include<cstdio>  
#include<cstring>  
#include<algorithm>  
#define N 100005  
#define M 2000005  
using namespace std;  
   
int n,cnt,trtot,a[N],num[N],rt[N],sum[M],ls[M],rs[M];  
int read(){  
    int x=0; char ch=getchar();  
    while (ch<'0' || ch>'9') ch=getchar();  
    while (ch>='0' && ch<='9'){ x=x*10+ch-'0'; ch=getchar(); }  
    return x;  
}  
int find(int x){  
    int l=1,r=cnt+1,mid;  
    while (l+1<r){  
        mid=(l+r)>>1;  
        if (num[mid]<=x) l=mid; else r=mid;  
    }  
    return l;  
}  
void ins(int l,int r,int x,int &y,int u,int v){  
    y=++trtot; sum[y]=sum[x]+v;  
    if (l==r) return; int mid=(l+r)>>1;  
    if (u<=mid){ rs[y]=rs[x]; ins(l,mid,ls[x],ls[y],u,v); }  
    else{ ls[y]=ls[x]; ins(mid+1,r,rs[x],rs[y],u,v); }  
}  
int qry(int x,int y,int z){  
    int l=1,r=cnt,mid,ans=0; x=rt[x-1]; y=rt[y];  
    while (l<r){  
        mid=(l+r)>>1;  
        if (z<=mid){ r=mid; x=ls[x]; y=ls[y]; }  
        else{ l=mid+1; ans+=sum[ls[y]]-sum[ls[x]]; x=rs[x]; y=rs[y]; }  
    }  
    return ans+sum[y]-sum[x];  
}  
int main(){  
    n=read(); int i,l,r,ans,t;  
    for (i=1; i<=n; i++) a[i]=num[i]=read(); n++;  
    sort(num+1,num+n+1);  
    cnt=1;  
    for (i=2; i<=n; i++)  
        if (num[i]!=num[cnt]) num[++cnt]=num[i];  
    for (i=1; i<=n; i++) a[i]=find(a[i]);  
    for (i=1; i<=n; i++) ins(1,cnt,rt[i-1],rt[i],a[i],num[a[i]]);  
    int cas=read();  
    while (cas--){  
        l=read(); r=read();  
        for (ans=1; ; ans=t+1){  
            t=qry(l,r,find(ans));  
            if (t<ans) break;  
        }  
        printf("%d\n",ans);  
    }  
    return 0;  
}  
