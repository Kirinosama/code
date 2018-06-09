#include <bits/stdc++.h>
using namespace std;

int n,m;

struct point{
	int x,y,v;
}p[200010];

void solve(){

}

int main(){
	freopen("input","r",stdin);
	cin>>n;
	for(int i=1;i<=n;i++)
		scanf("%d%d%d",&p[i].x,&p[i].y,&p[i].v);
	cin>>m;
	while(m--)
		solve();
	return 0;
}
