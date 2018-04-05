#include <cstdlib>
#include <cstdio>
#include <cstring>
#include <iostream>
#include <algorithm>
#include <vector>
using namespace std;

#define MAXN 2020
vector <int> to[MAXN];

int last[MAXN],used[MAXN],ans,n,m,e;

int find(int x){
	for(int i=0;i<to[x].size();i++){
		int v=to[x][i];
		if(!used[v]){
			used[v]=1;
			if(!last[v] || find(last[v])){
				last[v]=x;
				return 1;
			}
		}
	}
	return 0;
}

int main(){
	freopen("input","r",stdin);
	cin>>n>>m>>e;
	for(int i=1;i<=e;i++){
		static int x,y;
		scanf("%d %d",&x,&y);
		if(x>n || y>m) continue;
		to[x].push_back(y);
	}
	for(int i=1;i<=n;i++){
		memset(used,0,sizeof(used));
		if(find(i)) ans++;
	}
	cout<<ans;
	return 0;
}
