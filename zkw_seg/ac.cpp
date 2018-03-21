#include<iostream>
#include<cstdio>
#include<cstring>
#include<cstdlib>
#include<algorithm>
#include<cmath>
#include<map>
#include<set>
#include<vector>
#include<queue>
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
int n,m;
struct seg{int l,r,v;}t[3000005];
void build(int k,int l,int r)
{
	t[k].l=l;t[k].r=r;
	if(l==r)return;
	int mid=(l+r)>>1;
	build(k<<1,l,mid);
	build(k<<1|1,mid+1,r);
}
int mn(int k)
{
	if(!t[k].v)return -1;
	int l=t[k].l,r=t[k].r;
	if(l==r)return l;
	if(t[k<<1].v)return mn(k<<1);
	else return mn(k<<1|1);
}
int mx(int k)
{
	if(!t[k].v)return -1;
	int l=t[k].l,r=t[k].r;
	if(l==r)return l;
	if(t[k<<1|1].v)return mx(k<<1|1);
	else return mx(k<<1);
}
void insert(int k,int val)
{
	int l=t[k].l,r=t[k].r;
	if(l==r){t[k].v=1;return;}
	int mid=(l+r)>>1;
	if(val<=mid)insert(k<<1,val);
	else insert(k<<1|1,val);
	t[k].v=t[k<<1].v+t[k<<1|1].v;
}
int find(int k,int val)
{
	int l=t[k].l,r=t[k].r;
	if(l==r)
	{
		if(t[k].v)return 1;
		return -1;
	}
	int mid=(l+r)>>1;
	if(val<=mid)return find(k<<1,val);
	else return find(k<<1|1,val);
}
void del(int k,int val)
{
	int l=t[k].l,r=t[k].r;
	if(l==r){t[k].v=0;return;}
	int mid=(l+r)>>1;
	if(val<=mid)del(k<<1,val);
	else del(k<<1|1,val);
	t[k].v=t[k<<1].v+t[k<<1|1].v;
}
int findpr(int k,int val)
{
	if(val<0)return -1;
	if(!t[k].v)return -1;
	int l=t[k].l,r=t[k].r;
	if(l==r)return l;
	int mid=(l+r)>>1;
	if(val<=mid)return findpr(k<<1,val);
	else 
	{
		int t=findpr(k<<1|1,val);
		if(t==-1)return mx(k<<1);
		else return t;
	}
}
int findsu(int k,int val)
{
	if(!t[k].v)return -1;
	int l=t[k].l,r=t[k].r;
	if(l==r)return l;
	int mid=(l+r)>>1;
	if(val>mid)return findsu(k<<1|1,val);
	else 
	{
		int t=findsu(k<<1,val);
		if(t==-1)return mn(k<<1|1);
		else return t;
	}
}
int main()
{
	freopen("zkw_seg.in","r",stdin);
	n=read();m=read();
	build(1,0,n);
	int opt,x;
	for(int i=1;i<=m;i++)
	{
		opt=read();
		switch(opt)
		{
		case 1:x=read();if(find(1,x)==-1)insert(1,x);break;
		case 2:x=read();if(find(1,x)==1)del(1,x);break;
		case 3:printf("%d\n",mn(1));break;
		case 4:printf("%d\n",mx(1));break;
		case 5:x=read();printf("%d\n",findpr(1,x-1));break;
		case 6:x=read();printf("%d\n",findsu(1,x+1));break;
		case 7:x=read();printf("%d\n",find(1,x));break;
		}
	}
	return 0;
}