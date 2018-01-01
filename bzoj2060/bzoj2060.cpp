#include <cstdlib>
#include <cstdio>
#include <cstring>
#include <iostream>
#include <algorithm>
#include <vector>
using namespace std;

#define MAXN 50010
#define ii pair<int,int>
#define INF 0x3f3f3f3f
typedef long long ll;

int n,x,y,f[MAXN][2];
vector <int> to[MAXN];

void dfs(int x,int fa){
	f[x][1]=1;f[x][0]=0;
	for(int i=0;i<to[x].size();i++){
		int y=to[x][i];
		if(y==fa) continue;
		dfs(y,x);
		f[x][1]+=f[y][0];
		f[x][0]+=max(f[y][1],f[y][0]);
	}
}

int main(){
    freopen("bzoj2060.in","r",stdin);
    scanf("%d",&n);
    for(int i=1;i<n;i++){
    	scanf("%d %d",&x,&y);
 		to[x].push_back(y);
 		to[y].push_back(x);
 	}
 	dfs(1,1);
 	printf("%d",max(f[1][1],f[1][0]));
    return 0;
}