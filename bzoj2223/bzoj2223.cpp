#include <cstdlib>
#include <cstdio>
#include <cstring>
#include <iostream>
#include <algorithm>
using namespace std;

#define size(x) (x?x->cnt:0)
#define ii pair<int,int>
#define INF 0x3f3f3f3f
typedef long long ll;

int n,m,lim,a[300010],cnt[10010];
bool flag;

struct node{
	node *ch[2];
	int cnt;
}*root[300010];

void build(node *&p,int l,int r){
	p=new node;
	p->cnt=0;
	p->ch[0]=p->ch[1]=NULL;
	if(l==r) return;
	int mid=(l+r)>>1;
	build(p->ch[0],l,mid);
	build(p->ch[1],mid+1,r);
}

void make(node *&p,node *q,int l,int r,int k){
	p=new node;
	p->cnt=q->cnt+1;
	p->ch[0]=p->ch[1]=NULL;
	if(l==r) return;
	int mid=(l+r)>>1;
	if(k<=mid){
		make(p->ch[0],q->ch[0],l,mid,k);
		p->ch[1]=q->ch[1];
	}
	else{
		p->ch[0]=q->ch[0];
		make(p->ch[1],q->ch[1],mid+1,r,k);
	}
}

void premake(){
	build(root[0],1,lim);
	for(int i=1;i<=n;i++)
		make(root[i],root[i-1],1,lim,a[i]);
}

void query(node *p,node *q,int l,int r,int k){
	if(l==r && p->cnt-q->cnt>=k){
		printf("yes %d\n",l);
		flag=true;
		return;
	}
	int lcnt=size(p->ch[0])-size(q->ch[0]);
	int rcnt=size(p->ch[1])-size(q->ch[1]);
	int mid=(l+r)>>1;
	if(lcnt>=k) query(p->ch[0],q->ch[0],l,mid,k);
	if(rcnt>=k) query(p->ch[1],q->ch[1],mid+1,r,k);
}

void solve(){
	int l,r;
	scanf("%d %d",&l,&r);flag=false;
	query(root[r],root[l-1],1,lim,(r-l+3)/2);
	if(!flag) printf("no\n");
}

int main(){
    freopen("bzoj2223.in","r",stdin);
    scanf("%d %d",&n,&lim);
    for(int i=1;i<=n;i++) scanf("%d",&a[i]);
    premake();
    scanf("%d",&m);
	while(m--)
		solve();
    return 0;
}