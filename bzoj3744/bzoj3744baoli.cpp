#include <cstdlib>
#include <cstdio>
#include <cstring>
#include <iostream>
#include <algorithm>
using namespace std;

#define ls p->ch[0]
#define rs p->ch[1]
#define MAXN 50010
#define ii pair<int,int>
#define INF 0x3f3f3f3f
typedef long long ll;

int n,m,lastans,a[MAXN],b[MAXN],c[MAXN],sum[MAXN];

struct node{
	node *ch[2];
	int cnt;
	node(){ch[0]=ch[1]=NULL,cnt=0;}
	void maintain(){
		cnt=ch[0]->cnt+ch[1]->cnt;
	}
}*root[MAXN];

int lowbit(int x){
	return x&-x;
}

void add(int x,int k){
	for(int i=x;i<=n;i+=lowbit(i)) c[i]+=k;
}

int getsum(int x){
	int res=0;
	for(int i=x;i;i-=lowbit(i))
		res+=c[i];
	return res;
}

int cal(node *p,node *q,node *P,node *Q,int l,int r){
	if(l==r) return 0;
	int mid=(l+r)>>1;
	int lcnt=p->ch[1]->cnt-q->ch[1]->cnt;
	int rcnt=P->ch[0]->cnt-Q->ch[0]->cnt;
	return lcnt*rcnt+cal(p->ch[0],q->ch[0],P->ch[0],Q->ch[0],l,mid)+cal(p->ch[1],q->ch[1],P->ch[1],Q->ch[1],mid+1,r);
}

void solve(int l,int r){
	int res=sum[r]-sum[l-1];
	if(l!=1) res-=cal(root[l-1],root[0],root[r],root[l-1],1,n);
	lastans=res;
	printf("%d\n",res);
}

void build(node *&p,int l,int r){
	p=new node;
	if(l==r) return;
	int mid=(l+r)>>1;
	build(ls,l,mid);build(rs,mid+1,r);
}

void make(node *&p,node *q,int l,int r,int pos){
	p=new node;p->cnt=q->cnt+1;
	if(l==r) return;
	int mid=(l+r)>>1;
	if(pos<=mid){
		rs=q->ch[1];
		make(ls,q->ch[0],l,mid,pos);
	}else{
		ls=q->ch[0];
		make(rs,q->ch[1],mid+1,r,pos);
	}
}

void premake(){
	for(int i=1;i<=n;i++)b[i]=a[i];
	sort(b+1,b+n+1);
	for(int i=1;i<=n;i++){
		a[i]=lower_bound(b+1,b+n+1,a[i])-b;add(a[i],1);
		sum[i]=sum[i-1]+i-getsum(a[i]);
	}
	build(root[0],1,n);
	for(int i=1;i<=n;i++) make(root[i],root[i-1],1,n,a[i]);
}

int main(){
    freopen("bzoj3744.in","r",stdin);
    scanf("%d",&n);
    for(int i=1;i<=n;i++)scanf("%d",&a[i]);
    premake();
    scanf("%d",&m);
	while(m--){
		int x,y;
		scanf("%d%d",&x,&y);
		x^=lastans,y^=lastans;
		solve(x,y);
	}
    return 0;
}