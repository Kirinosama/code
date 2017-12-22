#include <cstdlib>
#include <cstdio>
#include <algorithm>
using namespace std;

#define SIZE(x) ((x)?(x)->size:0)
#define HEIGHT(x) ((x)?(x)->height:-1)

#define MAXN 100010

const int INF=0x7f7f7f7f;

struct node 
{
    node *l;
    node *r;
    int size;
    int height;
    int data;
    int cnt;
}t[MAXN];

struct node *root=NULL;

int i,n,node_cnt;

void maintain(node* p)
{
	if(!p)
	return;
    p->height=max(HEIGHT(p->l),HEIGHT(p->r))+1;
    p->size=SIZE(p->l)+SIZE(p->r)+p->cnt;
}

node* singlerotateRR(node *p)
{
    node *p1=p->r;
    p->r=p1->l;
    p1->l=p;
    maintain(p);
    maintain(p1);
    return p1;
}

node* singlerotateLL(node *p)
{
    node *p1=p->l;
    p->l=p1->r;
    p1->r=p;
    maintain(p);
    maintain(p1);
    return p1;
}

node* doublerotateRL(node *p)
{
    p->l=singlerotateRR(p->l);
    return singlerotateLL(p);

}

node* doublerotateLR(node *p)
{
    p->r=singlerotateLL(p->r);
    return singlerotateRR(p);
}

node* insert(node *p,int k)
{
    if(!p)
    {
        p=&t[node_cnt];
        p->data=k;
        p->cnt=1;
        p->l=p->r=NULL;
    }

    else 
	{
		if(k==p->data)
   		{
       	    p->cnt++;
    	}
   
	    else
		{
			if(k<p->data)
		    {
		        p->l=insert(p->l,k);
		        if(HEIGHT(p->l) - HEIGHT(p->r) > 1)
		        {
		            if(HEIGHT(p->l->l) > HEIGHT(p->l->r))
		            	p=singlerotateLL(p);
		            else
		            	p=doublerotateRL(p);
		        }
		    }
		    else
		    {
		        p->r=insert(p->r,k);
		        if(HEIGHT(p->r) - HEIGHT(p->l) > 1)
		        {
		            if(HEIGHT(p->r->r) > HEIGHT(p->r->l))
		           	 	p=singlerotateRR(p);
		            else
		            	p=doublerotateLR(p);
		        }
		    }
		}
	}
    maintain(p);
    return p;
}

node* delBalance(node *p)
{
    if(!p)
    return p;

    if(HEIGHT(p->l)-HEIGHT(p->r)==2)
    {
        if(HEIGHT(p->l->l)>=HEIGHT(p->l->r))
        p=singlerotateLL(p);
        else
        p=doublerotateRL(p);
    }
    if(HEIGHT(p->r)-HEIGHT(p->l)==2)
    {
        if(HEIGHT(p->r->r)>=HEIGHT(p->r->l))
        p=singlerotateRR(p);
        else
        p=doublerotateLR(p);
    }
    maintain(p);
    return p;
}

node* delnode(node *p,int k)
{    
    if(!p)
    return p;

	if(p->data==k)
	{
	    if(!p->r)
	        p=p->l;
	    else
	    {
	        node* now=p->r;
	        while(now->l)
	        {
	            now=now->l;
	        }
	        p->data=now->data;
	        p->cnt=now->cnt;    
	        p->r=delnode(p->r,now->data);
	    }
		maintain(p);
		return p;
	}

	else if(k<p->data)
		p->l=delnode(p->l,k);
	else if(k>p->data)
		p->r=delnode(p->r,k);

    p=delBalance(p);

    maintain(p);
    return p;
}

node *del(node *p,int k)
{
    if(!p)
        return p;

    if(p->data==k)
    {
        p->cnt --; 
        if(p->cnt==0)
      		p=delnode(p,k);
    }

    else if(k<p->data)
        p->l=del(p->l,k);
    else if(k>p->data)
        p->r=del(p->r,k);

    maintain(p);
    return p;
}

int ask_rank(node *p,int k)
{
    if(!p)
    return 0;
    if(k>p->data)
    return ask_rank(p->r,k)+p->cnt+SIZE(p->l);
    else
    return ask_rank(p->l,k);
}

int ask_which_rank(node *p,int k)
{
    if(!p)        
    return 0;
    int lcnt=SIZE(p->l);
    if(k>lcnt && k<=lcnt+p->cnt)
    	return p->data;
    else if(k<=lcnt)
    	return ask_which_rank(p->l,k);
    else
    	return ask_which_rank(p->r,k-lcnt-p->cnt);
}

int ask_pre(node *p,int k)
{
    if(!p)
    	return 0;
    if(p->data>=k)
        return ask_pre(p->l,k); 
    else
    	return  max(p->data,ask_pre(p->r,k));
}

int ask_suc(node *p,int k)
{
    if(!p)
    	return INF;
    if(p->data<=k)
    	return ask_suc(p->r,k);
    else
    	return min(p->data,ask_suc(p->l,k));
}

void solve()
{
    int c,k;
    scanf("%d%d",&c,&k);
    if(c==1)
    {
        node_cnt++;
        root=insert(root,k);
    }
    if(c==2)
    	root=del(root,k);
    if(c==3)
   	 	printf("%d\n",ask_rank(root,k)+1);
    if(c==4)
    	printf("%d\n",ask_which_rank(root,k));
    if(c==5)
    	printf("%d\n",ask_pre(root,k));
    if(c==6)
    	printf("%d\n",ask_suc(root,k));    
}


int main()
{
    scanf("%d",&n);
    for(int i=1;i<=n;i++)
    solve();
    return 0;
}