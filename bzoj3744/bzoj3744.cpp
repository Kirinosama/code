#include <cstdlib>
#include <cstdio>
#include <cstring>
#include <iostream>
#include <algorithm>
#include <cmath>
using namespace std;

#define ls p->ch[0]
#define rs p->ch[1]
#define MAXN 70010
#define ii pair<int,int>
#define INF 0x3f3f3f3f
typedef long long ll;

int a[MAXN],b[MAXN],lastans,n,m,cnt[300][MAXN];
int c[MAXN],sqr;

struct node{
	node *ch[2];
	int sum;
	node(){ch[0]=ch[1]=NULL,sum=0;}
}*root[MAXN];

int lowbit(int x){
	return x&-x;
}

void add(int x,int k){
	for(int i=x;i<=n;i+=lowbit(i)) c[i]+=k;
}

int getsum(int x){
	int res=0;
	for(int i=x;i;i-=lowbit(i)) res+=c[i];
	return res;
}

int cal(node *p,node *q,int l,int r,int L,int R){
	if(L>R) return 0;
	if(l>R || r<L) return 0;
	if(l>=L && r<=R) return p->sum-q->sum;
	else{
		int mid=(l+r)>>1;
		return cal(ls,q->ch[0],l,mid,L,R)+cal(rs,q->ch[1],mid+1,r,L,R);
	}
}

void solve(){
	int l,r;
	scanf("%d%d",&l,&r);
	l^=lastans;r^=lastans;lastans=0;
	if(l/sqr==r/sqr){
		for(int i=l;i<=r;i++){
			add(a[i],1);
			lastans+=i-l+1-getsum(a[i]);
		}
		for(int i=l;i<=r;i++) add(a[i],-1);
	}else{
		lastans=cnt[l/sqr+1][r];
		for(int i=l;i<(l/sqr+1)*sqr;i++) lastans+=cal(root[r],root[i],1,n,1,a[i]-1);
	}
	printf("%d\n",lastans);
}

void build(node *&p,int l,int r){
	p=new node;
	if(l==r) return;
	int mid=(l+r)>>1;
	build(ls,l,mid);build(rs,mid+1,r);
}

void make(node *&p,node *q,int l,int r,int pos){
	p=new node;p->sum=q->sum+1;
	if(l==r) return;
	int mid=(l+r)>>1;
	if(pos<=mid){
		make(ls,q->ch[0],l,mid,pos);
		rs=q->ch[1];
	}else{
		make(rs,q->ch[1],mid+1,r,pos);
		ls=q->ch[0];
	}
}

void premake(){
	for(int i=0;i<=n/sqr;i++){
		int st=i?i*sqr:1;
		for(int j=st;j<=n;j++){
			add(a[j],1);
			cnt[i][j]=cnt[i][j-1]+j-st+1-getsum(a[j]);
		}
		for(int j=st;j<=n;j++) add(a[j],-1);
	}
	build(root[0],1,n);
	for(int i=1;i<=n;i++)make(root[i],root[i-1],1,n,a[i]);
}

int main(){
    freopen("bzoj3744.in","r",stdin);
    scanf("%d",&n);sqr=(int)sqrt(n);
    for(int i=1;i<=n;i++){
    	scanf("%d",&a[i]);
    	b[i]=a[i];
    }
    sort(b+1,b+n+1);
    for(int i=1;i<=n;i++)
    	a[i]=lower_bound(b+1,b+n+1,a[i])-b;
    premake();
    scanf("%d",&m);
	while(m--)solve();
    return 0;
}