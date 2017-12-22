#include <cstdlib>
#include <cstdio>
#include <map>
#include <algorithm>
using namespace std;

#define MAXN 5010
#define ls(x) x*2
#define rs(x) x*2+1

struct edge
{
	int l,r;
	int x;	
	bool flag;
}S[2*MAXN];

struct node
{
	int l;
	int r;
	int len;
	int cnt;
	int line;
	int lcover,rcover;
}node[MAXN*8];

map<int,int> dict;
map<int,int> op_dict;
int P[2*MAXN];
int i,n,L,ans;

bool cmp(const edge &x,const edge &y)
{
	if(x.x==y.x)
		return x.flag>y.flag;
	else
		return x.x<y.x;
}

void init()
{
	sort(P+1,P+1+2*n);
	L=unique(P+1,P+1+2*n)-P-1;
	for(int i=1;i<=L;i++)
	{
		dict[P[i]]=i;
		op_dict[i]=P[i];
	}
	sort(S+1,S+1+2*n,cmp);
	for(int i=1;i<=2*n;i++)
	{
		S[i].l=dict[S[i].l];
		S[i].r=dict[S[i].r];
	}
}

void maintain(int x)
{
	if(node[x].cnt)
		node[x].len=op_dict[node[x].r]-op_dict[node[x].l];
	else if(node[x].l==node[x].r)
		node[x].len=0;
	else
		node[x].len=node[ls(x)].len+node[rs(x)].len;

	if(node[x].cnt)
		node[x].lcover=node[x].rcover=1;
	else if(node[x].l==node[x].r)
		node[x].lcover=node[x].rcover=0;
	else 
	{
		node[x].lcover=node[ls(x)].lcover;
		node[x].rcover=node[rs(x)].rcover;
	}

	if(node[x].cnt)
		node[x].line=1;
	else if(node[x].l==node[x].r)
		node[x].line=0;
	else
		node[x].line=node[ls(x)].line+node[rs(x)].line-node[ls(x)].rcover*node[rs(x)].lcover;
}

void build(int x,int l,int r)
{
	node[x].l=l;
	node[x].r=r;
	node[x].len=0;
	node[x].cnt=0;
	node[x].lcover=node[x].rcover=0;
	node[x].line=0;
	if(l==r)
		return;
	int mid=(l+r)/2;
	build(ls(x),l,mid);
	build(rs(x),mid+1,r);
}

void insert(int x,int l,int r)
{
	//printf("insert %d~%d:%d~%d\n",node[x].l,node[x].r,l,r);
	if(node[x].l>=l && node[x].r<=r)
	{
		node[x].cnt++;
		maintain(x);
		return;
	}
	if(node[x].r<l || node[x].l>r)
		return;
	if(node[x].l!=node[x].r)
	{
		insert(ls(x),l,r);
		insert(rs(x),l,r);
		maintain(x);
		return;
	}
}

void del(int x,int l,int r)
{
	if(node[x].l>=l && node[x].r<=r)
	{
		node[x].cnt--;
		maintain(x);
		return;
	}
	if(node[x].r<l || node[x].l>r)
		return;
	if(node[x].l!=node[x].r)
	{
		del(ls(x),l,r);
		del(rs(x),l,r);
		maintain(x);
		return;
	}
}

int main()
{
	freopen("poj1177.in","r",stdin);
	scanf("%d",&n);
	for(int i=1;i<=n;i++)
	{
		int a,b,c,d;
		scanf("%d%d%d%d",&a,&b,&c,&d);
		S[i*2-1].l=b;S[i*2-1].r=d;S[i*2-1].x=a;S[i*2-1].flag=true;
		S[i*2].l=b;S[i*2].r=d;S[i*2].x=c;S[i*2].flag=false;
		P[i*2-1]=b;P[i*2]=d;
	}
	init();
	build(1,1,L);
	//for(int i=1;i<=2*n;i++)
	//	printf("%d %d\n",S[i].l,S[i].r);
	int k=1;
	while (k<=2*n)
	{
		int tmp=node[1].len;
		int pos=S[k].x;
		while(S[k].x==pos)
		{
			if(S[k].flag)
				insert(1,S[k].l,S[k].r);
			else
				del(1,S[k].l,S[k].r);
			k++;
		}
		ans+=abs(tmp-node[1].len);
		int linecnt=node[1].line;
		if(k!=2*n+1)
			ans+=linecnt*2*(S[k].x-S[k-1].x);
		//printf("在%d处,竖轴变化为%d,横轴增加%d,有%d条线段\n",pos,abs(tmp-node[1].len),linecnt*2*(S[k].x-S[k-1].x),linecnt);
	}
	printf("%d",ans);
	return 0;
}