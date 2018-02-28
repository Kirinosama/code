#include <cstdlib>
#include <cstdio>
#include <cstring>
#include <iostream>
#include <algorithm>
#include <cmath>
using namespace std;

#define Mod 1004535809
#define MAXM 8010
#define ii pair<int,int>
#define INF 0x3f3f3f3f
typedef long long ll;

int ans,num[8010],s,n,m,X;

void dfs(int x,int mul){
	if(x>n){
		if(mul==X) ans++;
		return;
	}
	for(int i=1;i<=s;i++)
		dfs(x+1,(mul*num[i])%m);
}

int main(){
	freopen("bzoj3994.in","r",stdin);
	cin>>n>>m>>X>>s;
	for(int i=1;i<=s;i++)
		scanf("%d",&num[i]);
	dfs(1,1);
	cout<<ans;
	return 0;
}