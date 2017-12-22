#include <cstdlib>
#include <cstdio>
#include <cstring>
#include <iostream>
#include <algorithm>
#include <vector>
using namespace std;

#define MAXN 1010
#define ii pair<int,int>
#define INF 0x3f3f3f3f
typedef long long ll;

int k,n,m,num[MAXN],cnt[MAXN],ans,book[MAXN];
vector <int> v1[MAXN];

void dfs(int x,int w){
	if(book[x]) return;
	cnt[x]+=w;book[x]=1;
	for(int i=0;i<v1[x].size();i++)
		dfs(v1[x][i],w);
}

int main(){
    freopen("bzoj1648.in","r",stdin);
    scanf("%d %d %d",&k,&n,&m);
    for(int i=1;i<=k;i++){
    	static int x;
    	scanf("%d",&x);
    	num[x]++;
    }
    for(int i=1;i<=m;i++){
    	static int x,y;
    	scanf("%d %d",&x,&y);
    	v1[x].push_back(y);
    }
    for(int i=1;i<=n;i++){
    	memset(book,0,sizeof(book));
    	if(num[i]) dfs(i,num[i]);
    }
    for(int i=1;i<=n;i++)
    	if(cnt[i]==k) ans++;
    printf("%d",ans);
    return 0;
}