#include <cstdlib>
#include <cstdio>
#include <cstring>
#include <iostream>
#include <algorithm>
#include <vector>
#include <queue>
using namespace std;

#define MAXN 2010
#define ii pair<int,int>
#define INF 0x3f3f3f3f
typedef long long ll;

int n,m,a[MAXN],ru[MAXN],cur[MAXN];
int ans[MAXN];
vector <int> to[MAXN];
priority_queue <ii> Q;

bool operator <(const ii &a,const ii &b){
	return a.second>b.second;
}

void solve(int x){
	while(!Q.empty()) Q.pop();
	for(int i=1;i<=n;i++){
		cur[i]=ru[i];
		if(!cur[i] && i!=x) Q.push(ii(i,a[i]));
	}
	int cnt=0;
	while(!Q.empty()){
		ii tp=Q.top();Q.pop();
		if(tp.second>cnt+1){
			printf("%d ",n-cnt);
			return;
		}cnt++;
		for(int i=0;i<to[tp.first].size();i++){
			int y=to[tp.first][i];
			cur[y]--;
			if(!cur[y] && y!=x) Q.push(ii(y,a[y]));
		}
	}
	printf("%d ",n-cnt);
}

int main(){
    freopen("bzoj2535.in","r",stdin);
    scanf("%d %d",&n,&m);
    for(int i=1;i<=n;i++){
    	scanf("%d",&a[i]);
    	a[i]=n-a[i]+1;
    }
    for(int i=1;i<=m;i++){
    	static int x,y;
    	scanf("%d %d",&x,&y);
    	to[y].push_back(x);
    	ru[x]++;
    }
	for(int i=1;i<=n;i++){
		cur[i]=ru[i];
		if(!cur[i]) Q.push(ii(i,a[i]));
	}
	int cnt=0;
	while(!Q.empty()){
		ii tp=Q.top();Q.pop();
		ans[++cnt]=tp.first;
		for(int i=0;i<to[tp.first].size();i++){
			int y=to[tp.first][i];
			cur[y]--;
			if(!cur[y]) Q.push(ii(y,a[y]));
		}
	}
	for(int i=n;i>=1;i--) printf("%d ",ans[i]);
	printf("\n");
	for(int i=1;i<=n;i++)
		solve(i);
    return 0;
}