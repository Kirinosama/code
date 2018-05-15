#include<iostream>
#include<cstdio>
#include<cstring>
#include<cstdlib>
#include<cmath>
#include<algorithm>
#define ll long long
#define inf 1000000000
using namespace std;
inline ll read()
{
	ll x=0,f=1;char ch=getchar();
	while(ch<'0'||ch>'9'){if(ch=='-')f=-1;ch=getchar();}
	while(ch>='0'&&ch<='9'){x=x*10+ch-'0';ch=getchar();}
	return x*f;
}
int n,c,m,block;
int a[100005],belong[100005];
int tmp[100005];
struct data{int l,r,ans,id;}q[100005];
inline bool operator<(data a,data b)
{
	return (belong[a.l]<belong[b.l])||(belong[a.l]==belong[b.l]&&a.r<b.r);
}
inline bool cmp(data a,data b)
{
	return a.id<b.id;
}
void solve()
{
	int l=0,r=0;
	int ans=0;
	for(int i=1;i<=m;i++)
	{
		while(r<q[i].r)
		{
			r++;
	 	    tmp[a[r]]++;
	        if(tmp[a[r]]%2==0)ans++;
	        if(tmp[a[r]]%2==1&&tmp[a[r]]!=1)ans--;
	 	}
	 	while(l>q[i].l)
	 	{
	 		l--;
	 		tmp[a[l]]++;
	        if(tmp[a[l]]%2==0)ans++;
	        if(tmp[a[l]]%2==1&&tmp[a[l]]!=1)ans--;
	 	}
		while(l<q[i].l)
		{
			tmp[a[l]]--;
			if(tmp[a[l]]%2==0&&tmp[a[l]]!=0)ans++;
			if(tmp[a[l]]%2==1)ans--;
			l++;
		}
	 	while(r>q[i].r)
	 	{
	        tmp[a[r]]--;
			if(tmp[a[r]]%2==0&&tmp[a[r]]!=0)ans++;
			if(tmp[a[r]]%2==1)ans--;
			r--;
	 	}
	 	q[i].ans=ans;
	}
}
int main()
{
	freopen("harem4.in","r",stdin);
	freopen("harem4.out","w",stdout);
	n=read();c=read();m=read();
	block=(int)sqrt((double)n);
	for(int i=1;i<=n;i++)belong[i]=(i-1)/block+1;
	for(int i=1;i<=n;i++)a[i]=read();
	for(int i=1;i<=m;i++)
	    q[i].l=read(),q[i].r=read(),q[i].id=i;
	sort(q+1,q+m+1);
	solve();
	sort(q+1,q+m+1,cmp);
	for(int i=1;i<=m;i++)
	    printf("%d\n",q[i].ans);
	return 0;
}

