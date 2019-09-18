#include <bits/stdc++.h>
using namespace std;

#define MAXN 1010

int used[MAXN],belong[MAXN];
vector <int> to[MAXN];
int n,m,e;

bool find(int x)
	for(int i=0;i<to[x].size();i++){
		int v=to[x][i];
		if(used[v]) continue;
		used[v]=1;
		if(!belong[v] || find(belong[v])){
			belong[v]=x;
			return true;
		}
	}
	return false;
}

int main(){
	freopen("input","r",stdin);
	cin>>n>>m>>e;
	for(int i=1;i<=e;i++){
		static int x,y;
		scanf("%d%d",&x,&y);
		if(x>n || y>m) continue;
		to[x].push_back(y);
	}
	int ans=0;
	for(int i=1;i<=n;i++){
		memset(used,0,sizeof(used));
		if(find(i)) ans++;
	}
	cout<<ans;
	return 0;
}
