#include <cstdlib>
#include <cstdio>
#include <cstring>
#include <iostream>
#include <algorithm>
#include <vector>
using namespace std;

#define MAXN 100010
#define ii pair<int,int>
#define INF 0x3f3f3f3f
typedef long long ll;

vector <int> to[MAXN];
int rt,n,s,anc[MAXN][25],a[MAXN],dep[MAXN],ans;

void dfs(int x){
	for(int i=1;i<=20;i++)
		anc[x][i]=anc[anc[x][i-1]][i-1];
	for(int i=0;i<to[x].size();i++)
		if(to[x][i]!=anc[x][0])
			dep[to[x][i]]=dep[x]+a[to[x][i]],dfs(to[x][i]);
}

void solve(int x){
	if(dep[x]==s){
		ans++;return;
	}
	int cur=dep[x];
	for(int i=20;i>=0;i--){
		if(cur-dep[anc[x][i]]<=s){
			if(cur-dep[anc[x][i]]==s){
				ans++;return;
			}
			x=anc[x][i];
		}
	}
}

int main(){
    freopen("bzoj2783.in","r",stdin);
    cin>>n>>s;
    for(int i=1;i<=n;i++)scanf("%d",&a[i]);
    for(int i=1;i<n;i++){
    	static int x,y;
    	scanf("%d %d",&x,&y);
    	to[x].push_back(y);
    	anc[y][0]=x;
    }
    for(int i=1;i<=n;i++)if(!anc[i][0])rt=i;
    dep[rt]=a[rt];dfs(rt);
	for(int i=1;i<=n;i++)
		solve(i);
	cout<<ans;
    return 0;
}