#include <iostream>  
#include <cstdio>  
#include <cstring>  
#include <cmath>  
#include <cstdlib>  
#include <algorithm>  
#define F(i,j,n) for(int i=j;i<=n;i++)  
#define D(i,j,n) for(int i=j;i>=n;i--)  
#define ll long long  
#define pa pair<int,int>  
#define maxn 200100  
#define inf 1000000000  
using namespace std;  
int a[maxn],x[maxn],y[maxn],c[maxn],sa[maxn];  
int n;  
char s[maxn];  
inline void build_sa(int n,int m)  
{  
    memset(c,0,sizeof(c));  
    F(i,0,n-1) c[x[i]=a[i]]++;  
    F(i,1,m-1) c[i]+=c[i-1];  
    D(i,n-1,0) sa[--c[x[i]]]=i;  
    for(int k=1;k<=n;k<<=1)  
    {  
        int p=0;  
        F(i,n-k,n-1) y[p++]=i;  
        F(i,0,n-1) if (sa[i]>=k) y[p++]=sa[i]-k;  
        memset(c,0,sizeof(c));  
        F(i,0,n-1) c[x[y[i]]]++;  
        F(i,1,m-1) c[i]+=c[i-1];  
        D(i,n-1,0) sa[--c[x[y[i]]]]=y[i];  
        swap(x,y);  
        p=1;x[sa[0]]=0;  
        F(i,1,n-1) x[sa[i]]=y[sa[i-1]]==y[sa[i]]&&y[sa[i-1]+k]==y[sa[i]+k]?p-1:p++;  
        if (p>=n) break;  
        m=p;  
    }  
}  
int main()  
{  
    scanf("%s",s);  
    n=strlen(s);  
    F(i,0,n-1) a[i]=a[i+n]=s[i]+1;  
    a[2*n]=0;  
    build_sa(2*n,129);  
    F(i,0,2*n-1) if (sa[i]<n)  
    {  
        int tmp=(sa[i]-1+n)%n;  
        printf("%c",s[tmp]);  
    }  
    printf("\n");  