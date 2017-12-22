#include <cstdlib>
#include <cstdio>
#include <cstring>
#include <iostream>
#include <algorithm>
using namespace std;

#define MAXN 800010

struct Query
{
	int type,x,y,ti,val;
	bool operator < (Query a)
	const{
		if(x==a.x && y==a.y) return type<a.type;
		if(x==a.x) return y<a.y;
		return x<a.x;
	}
}query[MAXN],cur[MAXN];

int n,c[500010],ans[MAXN],cnt,anscnt;

int lowbit(int x){
	return x&-x;
}

void add(int x,int k)
{
	for(int i=x;i<=n;i+=lowbit(i))
		c[i]+=k;
}

int getsum(int x)
{
	int res=0;
	for(int i=x;i;i-=lowbit(i)) res+=c[i];
	return res;
}

void cdq(int l,int r)
{
	if(l==r) return;
	int mid=(l+r)>>1;
	for(int i=l;i<=r;i++)
	{
		if(query[i].type==1 && query[i].ti<=mid)
			add(query[i].y,query[i].val);
		if(query[i].ti>mid)
		{
			if(query[i].type==2)
				ans[query[i].val]-=getsum(query[i].y);
			if(query[i].type==3)
				ans[query[i].val]+=getsum(query[i].y);
		}
	}
	for(int i=l;i<=r;i++)
		if(query[i].type==1 && query[i].ti<=mid)
			add(query[i].y,-query[i].val);

	int p=l,q=mid+1,o=0;
	for(int i=l;i<=r;i++)
	{
		if(query[i].ti<=mid) cur[p++]=query[i];
		else cur[q++]=query[i];
	}
	for(int i=l;i<=r;i++) query[i]=cur[i];
	cdq(l,mid);cdq(mid+1,r);
}

int main()
{
	freopen("input","r",stdin);
	scanf("%d",&n);
	while(1)
	{
		static int type;
		scanf("%d",&type);
		if(type==3) break;
		if(type==1)
		{
			static int x,y,k;
			scanf("%d %d %d",&x,&y,&k);
			cnt++;
			query[cnt]=(Query){1,x,y,cnt,k};
		}
		if(type==2)
		{
			static int x,y,xx,yy;
			scanf("%d %d %d %d",&x,&y,&xx,&yy);
			anscnt++;
			cnt++,query[cnt]=(Query){3,x-1,y-1,cnt,anscnt};
			cnt++,query[cnt]=(Query){3,xx,yy,cnt,anscnt};
			cnt++,query[cnt]=(Query){2,x-1,yy,cnt,anscnt};
			cnt++,query[cnt]=(Query){2,xx,y-1,cnt,anscnt};
		}
	}
	sort(query+1,query+cnt+1);
	cdq(1,cnt);
	for(int i=1;i<=anscnt;i++) printf("%d\n",ans[i]); 
	return 0;
}