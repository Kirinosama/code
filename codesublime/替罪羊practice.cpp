#include <cstdlib>
#include <cstdio>
#include <vector>
using namespace std;

#define alpha 0.75
#define MAXN 100010

struct node
{
	int data;
	int size;
	int all;
	bool exist;
	node *l;
	node *r;
	
	bool is_bad()
	{	
		return (l->size>size*alpha+5 || r->size>size*alpha+5);
	}

	void maintain()
	{
		size=l->size+r->size+exist;
		all=l->all+r->all+1;
	}
}t[MAXN];

struct node mem_pool[MAXN];
struct node *bc[MAXN];
struct node *tail;
struct node *null=NULL;
struct node *root=NULL;
int bc_cnt,n;

vector <node*> v;

void init()
{
	tail=mem_pool;
	bc_cnt=0;
}

node* newnode(int k)
{
	node* p=(bc_cnt)?(bc[bc_cnt--]):(tail++);
	p->data=k;
	p->l=p->r=NULL;
	p->size=p->all=1;
	p->exist=true;
	return p;
}

void travel(node* p,vector <node *> &v)
{
	if(p==null)
		return;
	travel(p->l,v);
	if(p->exist)
		v.push_back(p);
	travel(p->r,v);
}

node* divide (vector<node*> &v,int l,int r)
{
	if(l>=r)
		return null;
	int mid=(l+r)/2;
	v[mid]->l=divide(v,l,mid);
	v[mid]->r=divide(v,mid+1,r);
	v[mid]->maintain();
	return v[mid];
}

void rebuild(node **p)
{
	v.clear(); travel(*p,v);
	*p=divide(v,0,v.size());
}

node** insert(node **p,int k)
{
	if(p==null)
	{
		p=newnode(k);
			return &null;
	}
	else
	{
		p->size++;p->all++;
		node **res=insert((k<=p->data)?(p->l):(p->r),k);
		if(p->is_bad())
			res=&p;
		return res;
	}
}

void add(node* root,int k)
{
	node ** res=insert(root,k);
		if(*res!=null)
			rebuild(*res);
}

void solve()
{
	int c,k;
	scanf("%d %d",&c,&k);
	if(c==1)
		add(root,k);
	// if(c==2)
	// 	del(root,k);
	// if(c==3)
	// 	printf("%d\n",rank(k));
}

int main()
{
	init();
	freopen("input","r",stdin);
	scanf("%d",&n);
	for(int i=1;i<=n;i++)
		solve();
	printf("%d",root->data);
	return 0;
}