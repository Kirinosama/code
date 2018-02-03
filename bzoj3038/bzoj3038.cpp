#include <cstdlib>
#include <cstdio>
#include <cstring>
#include <iostream>
#include <algorithm>
#include <cmath>
using namespace std;

#define MAXN 100010
#define ls p->ch[0]
#define rs p->ch[1]
#define ii pair<int,int>
#define INF 0x3f3f3f3f
typedef long long ll;

struct node{
	node *ch[2];
	ll sum,Max;
	node(){ch[0]=ch[1]=NULL;sum=Max=0;}
	void maintain(){
		sum=Max=0;
		if(ch[0])sum+=ch[0]->sum,Max=max(Max,ch[0]->Max);
		if(ch[1])sum+=ch[1]->sum,Max=max(Max,ch[1]->Max);
	}
}*root;

int n,m;
ll a[MAXN];

void build(node *&p,int l,int r){
	p=new node;
	if(l==r){
		p->Max=p->sum=a[l];
	}else{
		int mid=(l+r)>>1;
		build(ls,l,mid);build(rs,mid+1,r);
		p->maintain();
	}
}

void make_sqrt(node *p,int l,int r,int L,int R){
	if(l>R || r<L || p->Max<=1) return;
	if(l==r){
		p->Max=p->sum=(ll)sqrt(p->Max);
		return;
	}else{
		int mid=(l+r)>>1;
		make_sqrt(ls,l,mid,L,R);
		make_sqrt(rs,mid+1,r,L,R);
		p->maintain();
	}
}

ll query(node *p,int l,int r,int L,int R){
	if(l>R||r<L)return 0;
	if(l>=L && r<=R){
		return p->sum;
	}else{
		int mid=(l+r)>>1;
		return query(ls,l,mid,L,R)+query(rs,mid+1,r,L,R);
	}
}

void solve(){
	int ch,l,r;
	scanf("%d%d%d",&ch,&l,&r);
	if(l>r)swap(l,r);
	switch(ch){
		case 0:
			make_sqrt(root,1,n,l,r);
			break;
		case 1:
			printf("%lld\n",query(root,1,n,l,r));
	}
}

int main(){
    freopen("bzoj3038.in","r",stdin);
    scanf("%d",&n);
    for(int i=1;i<=n;i++)scanf("%lld",&a[i]);
    build(root,1,n);
	scanf("%d",&m);
	while(m--)solve();
    return 0;
}