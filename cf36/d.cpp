#include <cstdlib>
#include <cstdio>
#include <cstring>
#include <iostream>
#include <algorithm>
#include <stack>
using namespace std;

#define MAXN 510
#define ii pair<int,int>
#define INF 0x3f3f3f3f
typedef long long ll;

int dfn[MAXN],low[MAXN],dis[MAXN][MAXN];
int ti,ans1,n,m,fam[MAXN],cnt,cnt1,size[MAXN];
ii ans2;
stack <int> s;

void dfs(int x){
	dfn[x]=low[x]=++ti;s.push(x);
	for(int i=1;i<=n;i++){
		if(!dis[x][i]) continue;
		if(!dfn[i]){
			dfs(i);
			low[x]=min(low[x],low[i]);
			if(low[x]<=dfn[x] && x>ans1)
				ans1=x,ans2=ii(x,i);
		}
		else if(!fam[i]){
			low[x]=min(low[x],dfn[i]);
		}
	}
	if(dfn[x]==low[x]){
		cnt++;
		while(s.top()!=x)
			fam[s.top()]=cnt,s.pop(),size[cnt]++;
		fam[s.top()]=cnt,s.pop(),size[cnt]++;
		if(size[cnt]>1) cnt1++;
	}
}

int main(){
    freopen("cf36.in","r",stdin);
    scanf("%d %d",&n,&m);
  	for(int i=1;i<=m;i++){
  		static int x,y;
  		scanf("%d %d",&x,&y);
  		dis[x][y]=1;
  	}
  	for(int i=1;i<=n;i++)
  		if(!dfn[i]) dfs(i);
  	if(cnt1==0){
  		printf("YES");
  		return 0;
  	}
  	if(cnt1>1){
  		printf("NO");
  		return 0;
  	}
  	dis[ans2.first][ans2.second]=0;
  	cnt=cnt1=ti=0;
  	memset(size,0,sizeof(size));
  	memset(fam,0,sizeof(fam));
  	memset(dfn,0,sizeof(dfn));
  	memset(low,0,sizeof(low));
  	for(int i=1;i<=n;i++)
  		if(!dfn[i]) dfs(i);
  	if(cnt1) printf("NO");
  	else printf("YES");
    return 0;
}