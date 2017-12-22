#include<iostream>
#include<cstdio>
#include<cstring>
#include<cstdlib>
#include<algorithm>
#include<cmath>
#define pa pair<int,int>
#define inf 1000000000
#define ll long long 
using namespace std;
inline int read()
{
    int x=0,f=1;char ch=getchar();
    while(ch<'0'||ch>'9'){if(ch=='-')f=-1;ch=getchar();}
    while(ch>='0'&&ch<='9'){x=x*10+ch-'0';ch=getchar();}
    return x*f;
}
int n,ans;
int a[100015],nxt[100015],last[100015];
ll sum[100015];
bool mark[100015];
void cal(int x)
{
	int len=0,r=inf;
	for(int i=x+1;a[i]!=1&&i<=n;i++)
	    if(!mark[a[i]])mark[a[i]]=1;
		else {r=i;break;}
	for(int i=x;i;i--)
	{
		if(a[i]==1&&i!=x)break;
		len=max(len,a[i]);
		r=min(nxt[i],r);
		if(i+len-1<r&&i+len-1<=n)
		{
			if(sum[i+len-1]-sum[i-1]==(ll)len*(len+1)/2)ans=max(len,ans);
		}
	}
	for(int i=x+1;a[i]!=1&&i<=n;i++)mark[a[i]]=0;
}

void solve()
{
	memset(last,127,sizeof(last));
	for(int i=1;i<=n;i++)sum[i]=sum[i-1]+a[i];
	for(int i=n;i;i--)
	{
		nxt[i]=last[a[i]];
		last[a[i]]=i;
	}
	for(int i=1;i<=n;i++)
		if(a[i]==1)cal(i);
}
int main()
{
	n=read();
	for(int i=1;i<=n;i++)a[i]=read();
	solve();
	for(int i=1;i<=n/2;i++)swap(a[i],a[n-i+1]);
	solve();
	printf("%d\n",ans);
	return 0;
}