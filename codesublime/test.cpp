#include <cstdlib>
#include <cstdio>
#include <vector>
#include <algorithm>

#define alpha 0.75
#define MAXN 300000

const int INF=0x7f7f7f7f;

struct node
{
	int data;
	int size;//子树存在节点个数
	int cnt;//该节点元素个数
	int exist_element;//子树元素个数
	bool exist;//是否存在
	node *l;
	node *r;
	
	bool is_bad()
	{	
		return (l->size>size*alpha+5 || r->size>size*alpha+5);
	}

	void maintain()
	{
		if(cnt==0)
			exist=false;
		size=l->size+r->size+exist;
		exist_element=l->exist_element+r->exist_element+cnt;
	}
}t[MAXN];

struct node mem_pool[MAXN];
struct node *bc[MAXN];
struct node *tail;
struct node *null;
struct node *root=NULL;
int bc_cnt,n;

std::vector <node*> v;

void init()
{
	tail=mem_pool;
	bc_cnt=0;
	null=tail++;
	null->l=null->r=NULL;
	null->exist_element=0;
	null->cnt=0;
	null->data=null->size=0;
	root=null;
}

node * newnode(int k)
{
	node *p=(bc_cnt) ? bc[bc_cnt--] : tail++;
	p->data=k;
	p->cnt=1;
	p->exist_element=1;
	p->exist=true;
	p->size=1;
	p->l=p->r=null;
	return p;
}

node ** insert(node ** p,int k)
{
	if(*p==null)
	{
		*p=newnode(k);
		return &null;
	}
	else
	{
		node ** res=&null; 
		if((*p)->data==k)
		{
			(*p)->cnt ++;

		} else {
			res= insert( k<=(*p)->data ? &((*p)->l) : &((*p)->r),k );
		}
		(*p)->maintain();
		//if((*p)->is_bad())
		//	res=p;
		return res;
	}
}

void travel(node *p,std::vector<node*>&v)
{
	if(p==null)
		return;
	travel(p->l,v);
	if(p->exist)
		v.push_back(p);
	travel(p->r,v);
}

node * divide(std::vector <node*> &v,int l,int r)
{
	if(l>=r)
		return null;
	int mid=(l+r)/2;
	v[mid]->l=divide(v,0,mid);
	v[mid]->r=divide(v,mid+1,r);
	v[mid]->maintain();
	return v[mid];
}

void rebuild(node *& p)
{
	v.clear();
	travel(p,v);
	p=divide(v,0,v.size());
}


void add(int k)
{
	node ** res= insert(&root,k);
	if(*res!=null)
		rebuild(*res);
}

void del(node *p,int k)
{
	if(p->data==k)
	{
		p->cnt--;
		p->maintain();
		return;
	}	
	else
	{
		if(k<p->data)
			del(p->l,k);
		else
			del(p->r,k);
		p->maintain();
	}
}

int rank(node * p,int k)
{
	if(p==null)
		return 0;
	else if(p->data<=k)
		return p->l->exist_element+p->cnt+rank(p->r,k);
	else
		return rank(p->l,k);
}

int which_rank(node *p,int k)
{
	int lcnt=p->l->exist_element;
	if(k>lcnt && k<=lcnt+p->cnt)
		return p->data;
	else if(k<=lcnt)
		return which_rank(p->l,k);
	else
		return which_rank(p->r,k-lcnt-p->cnt);
}

int ask_pre(node * p,int k)
{
	if(p==null)
		return 0;
	if(p->data>=k)
		return ask_pre(p->l,k);
	else if(p->exist)
		return std::max(p->data,ask_pre(p->r,k));
	else 
		return ask_pre(p->r,k);
}

int ask_suc(node * p,int k)
{
	if(p==null)
		return INF;
	if(p->data<=k)
		return ask_suc(p->r,k);
	else if(p->exist)
		return std::min(p->data,ask_suc(p->l,k));
	else return ask_suc(p->l,k);
}

void solve()
{
	int c,k;
	scanf("%d %d",&c,&k);
	if(c==1)
		add(k);
	if(c==2)
	 	del(root,k);
	if(c==3)
	 	printf("%d\n",rank(root,k-1)+1);
	if(c==4)
		printf("%d\n",which_rank(root,k));
	if(c==5)
		printf("%d\n",ask_pre(root,k));
	if(c==6)
		printf("%d\n",ask_suc(root,k));
}

void make(node *p)
{
	if(p==null)
		return;
	make(p->l);
	printf("%d %d\n",p->data,p->cnt);
	make(p->r);
}

void make1(node * p,int k)
{
	if(p==null)
		return;
	printf("%d ",p->data);
	if(k<p->data)
		make1(p->l,k);
	else if(k>p->data)
		make1(p->r,k);
	else
		return;
}

int main()
{
	init();
	freopen("input","r",stdin);
	freopen("output","w",stdout);
	scanf("%d",&n);
	for(int i=1;i<=n;i++)
		solve();
	//make(root);
	//make1(root,496713);
	return 0;
}