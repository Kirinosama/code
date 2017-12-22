#include <cstdlib>
#include <cstdio>
#include <cstring>
#include <iostream>
#include <algorithm>
using namespace std;

#define MAXN 50010
#define MAXM 50010
#define ii pair<int,int>
#define INF 0x3f3f3f3f
typedef long long ll;

int n,m,ans[MAXM],cnt;

struct query{
	int id,type,l,r;ll c;
}q[MAXM],a1[MAXM],a2[MAXM];

struct node{
	node *ch[2];
	int l,r,last;
	ll size,add_tag;
	void check(){
		if(last!=cnt){
			last=cnt;
			add_tag=size=0;
		}
	}
	void pushdown(){
		if(ch[0]){
			ch[0]->check();
			ch[0]->size+=(ll)(ch[0]->r-ch[0]->l+1)*add_tag;
			ch[0]->add_tag+=add_tag;
		}
		if(ch[1]){
			ch[1]->check();
			ch[1]->size+=(ll)(ch[1]->r-ch[1]->l+1)*add_tag;
			ch[1]->add_tag+=add_tag;
		}
		add_tag=0;
	}
	void maintain(){
		size=0;
		if(ch[0]) size+=ch[0]->size;
		if(ch[1]) size+=ch[1]->size;
	}
}*root;

void build(node *&p,int l,int r){
	p=new node;
	p->last=p->size=p->add_tag=0;
	p->l=l,p->r=r;
	p->ch[0]=p->ch[1]=NULL;
	if(l!=r){
		int mid=(l+r)>>1;
		build(p->ch[0],l,mid);
		build(p->ch[1],mid+1,r);
	}
}

void add(node *&p,int l,int r,ll k){
	p->check();
	int mid=(p->l+p->r)>>1;
	if(p->l>=l && p->r<=r){
		p->size+=(ll)(p->r-p->l+1)*k;
		p->add_tag+=k;
	}
	else if(p->l!=p->r){
		p->pushdown();
		if(l<=mid)
			add(p->ch[0],l,r,k);
		if(r>mid)
			add(p->ch[1],l,r,k);
		p->maintain();
	}
}

ll Query(node *p,int l,int r){
	if(p->last!=cnt) return 0;
	if(l>p->r || r<p->l) return 0;
	else if(p->l>=l && p->r<=r) return p->size;
	else if(p->l!=p->r){
		p->pushdown();
		int mid=(p->l+p->r)>>1;
		return Query(p->ch[0],l,r)+Query(p->ch[1],l,r);
	}
	return 0;
}

void solve(int l,int r,int L,int R){
	if(l>r) return;
	if(L==R){
		for(int i=l;i<=r;i++)
			if(q[i].type==2)
				ans[q[i].id]=L;
		return;
	}
	int mid2=(L+R)>>1;
	int len1=0,len2=0;++cnt;
	for(int i=l;i<=r;i++){
		if(q[i].type==1){
			if(q[i].c<=mid2){
				add(root,q[i].l,q[i].r,1);
				a1[++len1]=q[i];
			}
			else 
				a2[++len2]=q[i];
		}
		else{
			if(Query(root,q[i].l,q[i].r)<q[i].c){
				q[i].c-=Query(root,q[i].l,q[i].r);
				a2[++len2]=q[i];
			}
			else 
				a1[++len1]=q[i];
		}
	}
	int mid=l+len1-1;
	for(int i=l;i<=r;i++){
		if(i<=mid) q[i]=a1[i-l+1];
		else q[i]=a2[i-mid];
	}
	solve(l,mid,L,mid2);
	solve(mid+1,r,mid2+1,R);
}

int main(){
    freopen("bzoj3110.in","r",stdin);
    scanf("%d %d",&n,&m);
    build(root,1,2*n+1);
    for(int i=1;i<=m;i++){
    	scanf("%d %d %d %lld",&q[i].type,&q[i].l,&q[i].r,&q[i].c);
    	if(q[i].type ==1) q[i].c = (ll)n-q[i].c+1;
    	q[i].id=i;ans[i]=1e9;
    }
    solve(1,m,1,2*n+1);
    for(int i=1;i<=m;i++)
    	if(ans[i]!=1e9)
    		printf("%d\n",n-ans[i]+1);
    return 0;
}