#include <cstdlib>
#include <cstdio>
#include <cstring>
#include <iostream>
#include <algorithm>
using namespace std;

#define ls p->ch[0]
#define rs p->ch[1]
#define MAXN 100010
#define ii pair<int,int>
#define INF 0x3f3f3f3f
typedef long long ll;

ll A,B,C,book[MAXN],t[MAXN],b[MAXN];
int n,m;

struct node{
	node *ch[2];
	ll cnt,sum;
	node(){ch[0]=ch[1]=NULL,cnt=sum=0;}
}*root;

void build(node *&p,int l,int r){
	p=new node;
	if(l==r) return;
	int mid=(l+r)>>1;
	build(ls,l,mid);
	build(rs,mid+1,r);
}

void add(node *p,int l,int r,int pos){
	p->cnt++;p->sum+=pos;
	if(l==r) return;
	int mid=(l+r)>>1;
	if(pos<=mid) add(ls,l,mid,pos);
	else add(rs,mid+1,r,pos);
}

ll getsum(node *p,int l,int r,int L,int R){
	if(L>R) return 0;
	if(r<L || l>R) return 0;
	if(l>=L && r<=R) return p->sum;
	else{
		int mid=(l+r)>>1;
		return getsum(ls,l,mid,L,R)+getsum(rs,mid+1,r,L,R);
	}
}

ll getcnt(node *p,int l,int r,int L,int R){
	if(L>R) return 0;
	if(r<L || l>R) return 0;
	if(l>=L && r<=R) return p->cnt;
	else{
		int mid=(l+r)>>1;
		return getcnt(ls,l,mid,L,R)+getcnt(rs,mid+1,r,L,R);
	}
}

ll solve(ll x){
	ll res=0;
	ll sum1=getsum(root,1,100000,1,x-1);
	ll cnt1=getcnt(root,1,100000,1,x-1);
	if(cnt1==m) return 0;
	ll sum2=getsum(root,1,100000,x+1,100000);
	ll cnt2=getcnt(root,1,100000,x+1,100000);
	ll Min=min(sum2-cnt2*x,x*cnt1-sum1);
	return Min*min(A,B)+(sum2-cnt2*x-Min)*B;
}

int main(){
    freopen("bzoj4868.in","r",stdin);
    scanf("%lld%lld%lld",&A,&B,&C);
    scanf("%d%d",&n,&m);
    for(int i=1;i<=n;i++)scanf("%lld",&t[i]),book[t[i]]++;
    build(root,1,100000);
    for(int i=1;i<=m;i++){
    	scanf("%lld",&b[i]);
    	add(root,1,100000,b[i]);
    }
    if(C==1e16){
    	ll Min=1e18;
    	for(int i=1;i<=n;i++)Min=min(Min,t[i]);
    	printf("%lld\n",solve(Min));
   		return 0;
    }
    ll all=0,cnt=0;ll ans=1e18;
    for(int i=1;i<=100000;i++){
    	all+=book[i-1]*(ll)(i-1);
    	cnt+=book[i-1];
   		ans=min(ans,(cnt*ll(i)-all)*C+solve(i));
    }
    printf("%lld\n",ans);
    return 0;
}