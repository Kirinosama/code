#include <cstdlib>
#include <cstdio>
#include <cstring>
#include <iostream>
#include <algorithm>
using namespace std;

#define ls p->ch[0]
#define rs p->ch[1]
#define MOD 131217
#define MAXN 300010
#define ii pair<int,int>
#define INF 0x3f3f3f3f
typedef long long ll;

struct node{
	node *ch[2];
	int cnt;
	node(){ch[0]=ch[1]=NULL,cnt=0;}
	void maintain(){cnt=ch[0]->cnt+ch[1]->cnt;}
}*root[MAXN];

int n,m,k,a[MAXN],powk;
ll Hash[MAXN];

ll gethash(int l,int r){
	ll res=Hash[r]-(Hash[l-1]*(ll)powk)%MOD;
	return res<0?res+MOD:res;
}

void make(node *&p,node *&q,int l,int r,int t){
	p=new node;
	if(l==r){
		p->cnt=q->cnt+1;return;
	}
	int mid=(l+r)>>1;
	if(t<=mid){
		p->ch[1]=q->ch[1];
		make(ls,q->ch[0],l,mid,t);
		p->maintain();
	}else{
		p->ch[0]=q->ch[0];
		make(rs,q->ch[1],mid+1,r,t);
		p->maintain();
	}
}

void build(node *&p,int l,int r){
	p=new node;
	if(l==r) return;
	int mid=(l+r)>>1;
	build(ls,l,mid);build(rs,mid+1,r);
}

void query(node *p,node *q,int l,int r,int tmp){
	if(!(p->cnt-q->cnt)){
		printf("Yes\n");
		return;
	}
	if(l==r){
		printf("No\n");
		return;
	}
	int mid=(l+r)>>1;
	if(tmp<=mid) query(p->ch[0],q->ch[0],l,mid,tmp);
	else query(p->ch[1],q->ch[1],mid+1,r,tmp);
}

void solve(){
	int l,r,x;
	ll cur=0;
	scanf("%d %d",&l,&r);
	for(int i=1;i<=k;i++){
		scanf("%d",&x);
		cur=(cur*79LL+(ll)x)%MOD;
	}
	r-=k-1;
	query(root[r],root[l-1],0,MOD-1,cur);
}

int main(){
    freopen("bzoj3207.in","r",stdin);
    freopen("out1","w",stdout);
    scanf("%d%d%d",&n,&m,&k);
    for(int i=1;i<=n;i++){
    	scanf("%d",&a[i]);
    	Hash[i]=(Hash[i-1]*79LL+(ll)a[i])%MOD;
    }
    powk=1;for(int i=1;i<=k;i++)powk=(powk*79)%MOD;
    build(root[0],0,MOD-1);
    for(int i=1;i<=n-k+1;i++) make(root[i],root[i-1],0,MOD-1,gethash(i,i+k-1));
    while(m--)	solve();
    return 0;
}