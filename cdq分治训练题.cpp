#include <cstdlib>
#include <cstdio>
#include <cstring>
#include <iostream>
using namespace std;

#define MAXN 100010

int cnt,n,anscnt,ans[MAXN];

struct ques
{
	int type;
	int pos;
	int ansidx;
	bool operator < (ques a)
	{
		return pos == a.pos ? type<a.type : pos<a.pos;
	}
}q[MAXN],cur[MAXN];

void cdq(int l,int r)
{
	if(l==r) return;
	int mid=(l+r)>>1;
	cdq(l,mid);
	cdq(mid+1,r);
	int P=l,Q=mid+1;
	int sum=0;
	int o=0;
	while(P<=mid && Q<=r)
	{
		if(q[P]<q[Q])
		{
			if(q[P].type==1) sum+=q[P].ansidx;
			cur[++o]=q[P++];
		}
		else 
		{
			if(q[Q].type==2) ans[q[Q].ansidx]-=sum;
			if(q[Q].type==3) ans[q[Q].ansidx]+=sum;
			cur[++o]=q[Q++];
		}
	}
	while(P<=mid)
		cur[++o]=q[P++];
	while(Q<=r)
	{
		if(q[Q].type==2) ans[q[Q].ansidx]-=sum;
		if(q[Q].type==3) ans[q[Q].ansidx]+=sum;
		cur[++o]=q[Q++];
	}
	for(int i=1;i<=o;i++) q[l+i-1]=cur[i];
}

int main()
{
	freopen("input","r",stdin);
	scanf("%d",&n);
	for(int i=1;i<=n;i++)
	{
		static int type;
		scanf("%d",&type);
		if(type==1)
		{
			static int pos,ad;
			scanf("%d %d",&pos,&ad);
			q[++cnt]=(ques){1,pos,ad};
		}
		else
		{
			static int l,r;
			scanf("%d %d",&l,&r);
			q[++cnt]=(ques){2,l-1,++anscnt};
			q[++cnt]=(ques){3,r,anscnt};
		}
	}
	cdq(1,cnt);
	for(int i=1;i<=anscnt;i++) printf("%d\n",ans[i]);
	return 0;
}

/*
	见bzoj2683
	cdq分治<<<<时间>>>> (mid时间以前对mid时间以后造成的影响)
	想办法保证顺序 使复杂度在线性时间内
*/