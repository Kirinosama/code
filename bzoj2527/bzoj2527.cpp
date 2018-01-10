#include <cstdlib>
#include <cstdio>
#include <cstring>
#include <iostream>
#include <algorithm>
#include <vector>
using namespace std;

#define MAXN 300010
#define ii pair<int,int>
#define INF 0x3f3f3f3f
typedef long long ll;

int l[MAXN],r[MAXN],a1[MAXN],a2[MAXN];
int n,m,k,a[MAXN],need[MAXN],ans[MAXN];
ll c[MAXN],val[MAXN];
vector <int> pos[MAXN];

int lowbit(int x){
	return x&-x;
}

void add(int x,ll k){
	for(int i=x;i<=m;i+=lowbit(i))
		c[i]+=k;
}

ll getsum(int x){
	ll sum=0;
	for(int i=x;i;i-=lowbit(i))
		sum+=c[i];
	return sum;
}

void make(int l,int r,ll k){
	if(l<=r)
		add(l,k),add(r+1,-k);
	else{
		add(l,k),add(m+1,-k);
		add(1,k),add(r+1,-k);
	}
}

void solve(int x,int y,int L,int R){
	if(L==R){
		make(l[L],r[L],val[L]);
		for(int i=x;i<=y;i++){
			ll sum=0;
			for(int j=0;j<pos[a[i]].size();j++){
				sum+=getsum(pos[a[i]][j]);
				if(sum>=need[a[i]]) break;
			}
			if(sum>=need[a[i]]) ans[a[i]]=R;
			else ans[a[i]]=-1;
		}
		make(l[L],r[L],-val[L]);
		return;
	}
	int mid=(L+R)>>1;
	for(int i=L;i<=mid;i++)
		make(l[i],r[i],val[i]);
	int cnt1=0,cnt2=0;
	for(int i=x;i<=y;i++){
		ll sum=0;
		for(int j=0;j<pos[a[i]].size();j++){
			sum+=getsum(pos[a[i]][j]);
			if(sum>=need[a[i]]) break;
		}
		if(sum<need[a[i]]) a2[++cnt2]=a[i];
		else a1[++cnt1]=a[i];
	}
	for(int i=1;i<=cnt1;i++)
		a[x+i-1]=a1[i];
	for(int i=1;i<=cnt2;i++)
		a[x+cnt1-1+i]=a2[i];
	solve(x+cnt1,y,mid+1,R);
	for(int i=L;i<=mid;i++)
		make(l[i],r[i],-val[i]);
	solve(x,x+cnt1-1,L,mid);
}

int main(){
    freopen("bzoj2527.in","r",stdin);
    scanf("%d %d",&n,&m);
    for(int i=1;i<=m;i++){
    	static int x;
    	scanf("%d",&x);
    	pos[x].push_back(i);
    }
    for(int i=1;i<=n;i++){
    	scanf("%d",&need[i]);
    	a[i]=i;
    }
   	scanf("%d",&k);
    for(int i=1;i<=k;i++)
    	scanf("%d %d %lld",&l[i],&r[i],&val[i]);
    solve(1,n,1,k);
    for(int i=1;i<=n;i++){
    	if(ans[i]==-1) printf("NIE\n");
    	else printf("%d\n",ans[i]);
    }
    return 0;
}