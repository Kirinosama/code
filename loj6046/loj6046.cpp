#include <cstdlib>
#include <cstdio>
#include <cstring>
#include <iostream>
#include <algorithm>
#include <vector>
#include <cmath>
using namespace std;

#define REG register
#define MAXN 100010
#define MAXM 200010
#define ii pair<int,int>
#define INF 0x3f3f3f3f
typedef long long ll;

struct edge{
	int x,y,z;
}E[MAXM];

int n,m,len,val,fa[MAXN],a[MAXN],sqr;
int last[MAXN],ne[MAXM],edge_cnt,ans;
int dis[MAXN],tail[MAXN],cnt,id[MAXN];
int add[MAXN],maxdis,mindis;
vector <int> v[MAXN];

inline void add_edge(int x,int y,int z){
	E[++edge_cnt]=(edge){x,y,z};
	ne[edge_cnt]=last[x];
	last[x]=edge_cnt;
}

inline void dfs(int x){
	id[x]=++cnt;
	for(REG int i=last[x];i;i=ne[i]){
		int y=E[i].y;
		dis[y]=dis[x]+E[i].z;
		dfs(y);
	}
	tail[x]=cnt;
}

inline void init(){
	sqr=sqrt(n);
	for(REG int i=1;i<=n;i++)
		a[id[i]]=dis[i];
	for(REG int i=1;i<=n;i++){
		maxdis=max(maxdis,dis[i]);
		mindis=min(mindis,dis[i]);
		v[i/sqr].push_back(a[i]);
	}
	for(REG int i=1/sqr;i<=n/sqr;i++)
		sort(v[i].begin(),v[i].end());
}

inline int cal(int l,int r,int k){
	int L=l/sqr,R=r/sqr,sum=0;
	for(REG int i=l;i<=min(r,(L+1)*sqr-1);i++)
		if(a[i]+add[L]<=k) sum++;
	if(L!=R)
		for(REG int i=R*sqr;i<=r;i++)
			if(a[i]+add[R]<=k) sum++;
	for(REG int i=L+1;i<R;i++)
		sum+=upper_bound(v[i].begin(),v[i].end(),k-add[i])-v[i].begin();
	return sum;
}

inline void query(int l,int r,int k){
	int L=mindis,R=maxdis;
	if(r-l+1<k){
		printf("-1\n");
		return;
	}
	while(L<=R){
		int mid=(L+R)>>1;
		if(cal(l,r,mid)>=k) ans=mid,R=mid-1;
		else L=mid+1;
	}
	printf("%d\n",ans);
}

inline void update(int l,int r,int k){
	int L=l/sqr,R=r/sqr;
	maxdis+=max(0,k),mindis+=min(0,k);
	for(REG int i=l;i<=min(r,(L+1)*sqr-1);i++){
		v[L].erase(lower_bound(v[L].begin(),v[L].end(),a[i]));
		a[i]+=k;
		v[L].insert(lower_bound(v[L].begin(),v[L].end(),a[i]),a[i]);
	}
	if(L!=R)
		for(REG int i=R*sqr;i<=r;i++){
			v[R].erase(lower_bound(v[R].begin(),v[R].end(),a[i]));
			a[i]+=k;
			v[R].insert(lower_bound(v[R].begin(),v[R].end(),a[i]),a[i]);
		}
	for(REG int i=L+1;i<R;i++)
		add[i]+=k;
}

inline void solve(){
	int opt,x,k;
	scanf("%d %d %d",&opt,&x,&k);
	switch(opt){
		case 1:
			query(id[x],tail[x],k);
			break;
		case 2:
			update(id[x],tail[x],k);
	}
}

int main(){
    freopen("loj6046.in","r",stdin);
    freopen("loj6046.out","w",stdout);
    scanf("%d %d %d",&n,&m,&len);
    fa[1]=1;maxdis=-INF,mindis=INF;
    for(REG int i=2;i<=n;i++){
    	scanf("%d %d",&fa[i],&val);
    	add_edge(fa[i],i,val);
    }
    dfs(1);
   	init();
   	while(m--)
   		solve();
    return 0;
}