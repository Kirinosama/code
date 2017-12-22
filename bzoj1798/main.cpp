#include <cstdlib>
#include <cstdio>

#define MAXN 100010

struct  node 
{
	int l,r;
	node *ls;
	node *rs;
	int len;
	int add_tag;
	int mul_tag;
};

node *root;
node *tail;
node *null;
node mem_pool[MAXN*8];

int n,m,MOD,sum[MAXN],a[MAXN],ans;

void init()
{
	tail=mem_pool;
	null=tail++;
	null->ls=null->rs=null;
	null->add_tag=null->mul_tag=null->r=null->l=0;
	root=null;
}

void build(node *& p,int l,int r)
{
	if(p==null)
		p=tail++;
	p->l=l;p->r=r;
	p->ls=p->rs=null;
	p->add_tag=0;
	p->mul_tag=1;
	p->len=sum[r]-sum[l-1];
	if(l==r)
		return;
	int mid=(l+r)/2;
	build(p->ls,l,mid);
	build(p->rs,mid+1,r);
}

void pre_make()
{
	init();
	build(root,1,n);
}

void push_down(node *&p)
{
	p->ls->add_tag+=p->add_tag;
	p->rs->add_tag+=p->add_tag;
	p->ls->mul_tag*=p->mul_tag;
	p->rs->mul_tag*=p->mul_tag;
	p->mul_tag=1;p->add_tag=0;
}

void mul(node *& p,int l,int r,int k)
{
	if(p->l>=l && p->r<=r)
	{
		p->add_tag*=k;
		p->mul_tag*=k;
	}
	if(p->l>r || p->r<l)
		return;
	if(l==r)
		return;
	push_down(p);
	mul(p->ls,l,r,k);
	mul(p->rs,l,r,k);
}

void add(node *& p,int l,int r,int k)
{
	if(p->l>=l && p->r<=r)
	{
		p->add_tag+=k;
	}
	if(p->l>r || p->r<l)
		return;
	if(l==r)
		return;
	push_down(p);
	add(p->ls,l,r,k);
	add(p->rs,l,r,k);
}

void ask(node *p,int l,int r)
{
	if(p->l>=l && p->r<=r)
	{
		ans=ans+p->len*p->mul_tag+p->add_tag;
	}
	if(p->l>r || p->r<l)
		return;
	if(p->l==p->r)
		return;
	ask(p->ls,l,r);
	ask(p->rs,l,r);
}

void solve()
{
	int c,ll,rr,k;
	scanf("%d%d%d",&c,&ll,&rr);
	if(c==1)
	{
		scanf("%d",&k);
		mul(root,ll,rr,k);
	}
	if(c==2)
	{
		scanf("%d",&k);
		add(root,ll,rr,k);
	}
	if(c==3)
	{
		ans=0;
		ask(root,ll,rr);
		printf("%d\n",ans);
	}
}

int main()
{
	freopen("input","r",stdin);
	scanf("%d %d",&n,&MOD);
	for(int i=1;i<=n;i++)
	{
		scanf("%d",&a[i]);
		sum[i]=a[i]+sum[i-1];
	｝
	pre_make();
	scanf("%d",&m);
	for(int i=1;i<=m;i++)
		solve();
	return 0;
}