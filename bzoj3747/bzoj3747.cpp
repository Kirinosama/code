#include <cstdlib>
#include <cstdio>
#include <cstring>
#include <iostream>
#include <algorithm>
using namespace std;

#define MAXN 1000010
typedef long long ll;

int n,m;
int a[MAXN],w[MAXN],pre[MAXN],last[MAXN];
int ls[MAXN*4],rs[MAXN*4];
ll ans,add[MAXN*4],Max[MAXN*4];
int num,rt;

void build(int &x,int l,int r){
	x=++num;
	if(l==r) return;
	else{
		int mid=(l+r)>>1;
		build(ls[x],l,mid);
		build(rs[x],mid+1,r);
	}
}

int pushdown(int x){
	if(ls[x]) add[ls[x]]+=add[x],Max[ls[x]]+=add[x];
	if(rs[x]) add[rs[x]]+=add[x],Max[rs[x]]+=add[x];
	add[x]=0;
}

void maintain(int x){
	Max[x]=max(Max[ls[x]],Max[rs[x]]);
}

void update(int x,int l,int r,int L,int R,int k){
	if(l>R || r<L || L>R) return;
	if(l>=L && r<=R){
		add[x]+=k,Max[x]+=k;
		return;
	}else{
		int mid=(l+r)>>1;
		pushdown(x);
		update(ls[x],l,mid,L,R,k);
		update(rs[x],mid+1,r,L,R,k);
		maintain(x);
	}
}

ll getmax(int x,int l,int r,int L,int R){
	if(l>R || r<L) return 0;
	if(l>=L && r<=R) return Max[x];
	else{
		int mid=(l+r)>>1;
		pushdown(x);
		ll res=max(getmax(ls[x],l,mid,L,R),getmax(rs[x],mid+1,r,L,R));
		maintain(x);
		return res;
	}
}

int main(){
	freopen("bzoj3747.in","r",stdin);
	cin>>n>>m;
	for(int i=1;i<=n;i++){
		scanf("%d",&a[i]);
		pre[i]=last[a[i]];
		last[a[i]]=i;
	}
	for(int i=1;i<=m;i++)scanf("%d",&w[i]);
	build(rt,1,n);
	for(int i=1;i<=n;i++){
		update(rt,1,n,pre[i]+1,i,w[a[i]]);
		update(rt,1,n,pre[pre[i]]+1,pre[i],-w[a[i]]);
		ans=max(ans,getmax(rt,1,n,1,i));
	}
	cout<<ans;
	return 0;
}
