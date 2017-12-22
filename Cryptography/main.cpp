#include <cstdlib>
#include <cstdio>

#define MAXN 30010

int n,m,MOD;

struct matrix
{
	int x[3][3];
	void read()
	{
		scanf("%d %d %d %d",&x[1][1],&x[1][2],&x[2][1],&x[2][2]);
	}
}A[MAXN];

matrix operator * (const matrix &a,const matrix &b)
{
	matrix c;
	c.x[1][1]=(a.x[1][1]*b.x[1][1]+a.x[1][2]*b.x[2][1])%MOD;
	c.x[1][2]=(a.x[1][1]*b.x[1][2]+a.x[1][2]*b.x[2][2])%MOD;
	c.x[2][1]=(a.x[2][1]*b.x[1][1]+a.x[2][2]*b.x[2][1])%MOD;
	c.x[2][2]=(a.x[2][1]*b.x[1][2]+a.x[2][2]*b.x[2][2])%MOD;
	return c;
} 

struct node
{
	node *ls;
	node *rs;
	int l,r;
	matrix s;
};

node * root;
node * null;
node * tail;
node mem_pool[MAXN*8];

void init()
{
	tail=mem_pool;
	null=tail++;
	null->rs=null->ls=null;
	null->l=null->r=0;
	root=null;
}

void build(node *& p,int l,int r)
{
	if(p==null)
		p=tail++;
	p->l=l;p->r=r;
	p->rs=p->ls=null;
	if(l==r)
		p->s=A[l];
	else
	{
		int mid=(l+r)/2;
		build(p->ls,l,mid);
		build(p->rs,mid+1,r);
		p->s=p->ls->s*p->rs->s;
	}
}

void premake()
{
	init();
	build(root,1,n);
}

matrix ask(node * p,int l,int r)
{
	matrix res;
	if(p->l>r || p->r<l)
	{
		res.x[1][1]=res.x[2][2]=1;
		res.x[1][2]=res.x[2][1]=0;
		return res;
	}
	if(p->l>=l && p->r<=r)
	{
		return p->s;
	}
	else
	{
		return ask(p->ls,l,r)*ask(p->rs,l,r);
	}
}

void solve()
{
	int ll,rr;
	scanf("%d %d",&ll,&rr);
	matrix ans=ask(root,ll,rr);
	printf("%d %d\n%d %d\n\n",ans.x[1][1],ans.x[1][2],ans.x[2][1],ans.x[2][2]);
}

int main()
{
	freopen("input","r",stdin);
	scanf("%d %d %d",&MOD,&n,&m);
	for(int i=1;i<=n;i++)
		A[i].read();
	premake();
	while(m--)
		solve();
	return 0;
}