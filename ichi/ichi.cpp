#include <cstdlib>
#include <cstdio>
#include <cstring>
#include <algorithm>
#include <iostream>
#include <vector>
using namespace std;

#define MAXN 100010
#define MAXM 200010
#define INF 0x3f3f3f3f
#define ii pair<int,int>
typedef long long ll;

struct edge{
	int x,y,z;
}E[MAXM];

int last[MAXN],ne[MAXM],edge_cnt;
int n,m,ty,a[MAXN];
vector <ii> book[MAXN];
ii fa[MAXN];
ll lastans;

void add_edge(int x,int y,int z){
	E[++edge_cnt]=(edge){x,y,z};
	ne[edge_cnt]=last[x];
	last[x]=edge_cnt;
}

ll query(int x,int mindis,ll tot){
	if(!x) return tot;
	for(int i=0;i<book[x].size();i++)
		if(book[x][i].first<=mindis)
			tot+=book[x][i].second;
	return query(fa[x].first,min(mindis,fa[x].second),tot);
}
	
void solve(){
	int opt,u,v,x;
	scanf("%d",&opt);
	if(opt==1){
		scanf("%d",&x);
		if(ty) x=(x+lastans)%n+1;
		lastans=query(x,INF,a[x]);
		cout<<lastans<<endl;
	}else{
		scanf("%d%d%d",&u,&v,&x);
		if(ty) x=(x+lastans)%n+1;
		book[x].push_back(ii(v,u));
	}
}

void dfs(int x,int f){
	for(int i=last[x];i;i=ne[i])if(E[i].y!=f){
		fa[E[i].y]=ii(x,E[i].z);
		dfs(E[i].y,x);
	}
}

int main(){
	//freopen("ichi.in","r",stdin);
	//freopen("ichi.out","w",stdout);
	cin>>n>>m>>ty;
	for(int i=1;i<=n;i++)scanf("%d",&a[i]);
	for(int i=1;i<n;i++){
		int x,y,z;
		scanf("%d%d%d",&x,&y,&z);
		add_edge(x,y,z);add_edge(y,x,z);
	}
	dfs(1,0);
	while(m--)
		solve();
	return 0;
}
