#include <cstdlib>
#include <cstdio>
#include <cstring>
#include <iostream>
#include <algorithm>
using namespace std;

#define MAXN 100010
#define MAXM 10000010
typedef long long ll;
ll ans;
int n,m,num,a[MAXN],pos[MAXN],cnt1,cnt2;
int ls[MAXM],rs[MAXM],cnt[MAXM],root[MAXN];
int addnode[MAXN],minusnode[MAXN];

int lowbit(int x){
	return x&-x;
}

void update(int &x,int l,int r,int pos,int k){
	if(!x) x=++num;
	cnt[x]+=k;
	if(l!=r){
		int mid=(l+r)>>1;
		if(pos<=mid) update(ls[x],l,mid,pos,k);
		else update(rs[x],mid+1,r,pos,k);
	}
}

int Less(int L,int R,int x){
	cnt1=cnt2=0;
	if(L>R || x<1) return 0;
	for(int i=R;i;i-=lowbit(i))addnode[++cnt1]=root[i];
	for(int i=L-1;i;i-=lowbit(i))minusnode[++cnt2]=root[i];
	int l=1,r=n,res=0;
	while(l!=r){
		int mid=(l+r)>>1;
		if(x<=mid){
			for(int i=1;i<=cnt1;i++)addnode[i]=ls[addnode[i]];
			for(int i=1;i<=cnt2;i++)minusnode[i]=ls[minusnode[i]];
			r=mid;
		}else{
			for(int i=1;i<=cnt1;i++)res+=cnt[ls[addnode[i]]];
			for(int i=1;i<=cnt2;i++)res-=cnt[ls[minusnode[i]]];
			for(int i=1;i<=cnt1;i++)addnode[i]=rs[addnode[i]];
			for(int i=1;i<=cnt2;i++)minusnode[i]=rs[minusnode[i]];
			l=mid+1;
		}
	}
	for(int i=1;i<=cnt1;i++)res+=cnt[addnode[i]];
	for(int i=1;i<=cnt2;i++)res-=cnt[minusnode[i]];
	return res;
}

int More(int L,int R,int x){
	cnt1=cnt2=0;
	if(L>R || x>n) return 0;
	for(int i=R;i;i-=lowbit(i))addnode[++cnt1]=root[i];
	for(int i=L-1;i;i-=lowbit(i))minusnode[++cnt2]=root[i];
	int l=1,r=n,res=0;
	while(l!=r){
		int mid=(l+r)>>1;
		if(x>=mid+1){
			for(int i=1;i<=cnt1;i++)addnode[i]=rs[addnode[i]];
			for(int i=1;i<=cnt2;i++)minusnode[i]=rs[minusnode[i]];
			l=mid+1;
		}else{
			for(int i=1;i<=cnt1;i++)res+=cnt[rs[addnode[i]]];
			for(int i=1;i<=cnt2;i++)res-=cnt[rs[minusnode[i]]];
			for(int i=1;i<=cnt1;i++)addnode[i]=ls[addnode[i]];
			for(int i=1;i<=cnt2;i++)minusnode[i]=ls[minusnode[i]];
			r=mid;
		}
	}
	for(int i=1;i<=cnt1;i++)res+=cnt[addnode[i]];
	for(int i=1;i<=cnt2;i++)res-=cnt[minusnode[i]];
	return res;
}

int main(){
	freopen("bzoj3295.in","r",stdin);
	cin>>n>>m;
	for(int i=1;i<=n;i++){
		scanf("%d",&a[i]);pos[a[i]]=i;
		for(int j=i;j<=n;j+=lowbit(j))
			update(root[j],1,n,a[i],1);
	}
	for(int i=1;i<=n;i++)
		ans+=Less(i+1,n,a[i]-1);
	while(m--){
		int x;cin>>x;x=pos[x];
		cout<<ans<<endl;
		ans-=More(1,x-1,a[x]+1);
		ans-=Less(x+1,n,a[x]-1);
		for(int i=x;i<=n;i+=lowbit(i))
			update(root[i],1,n,a[x],-1);
	}
	return 0;
}
