#include <cstdlib>
#include <cstdio>
#include <cstring>
#include <iostream>
#include <algorithm>
#include <queue>
using namespace std;

int n,m,ans1,ans2;
int a[210];

struct bottle{
	int x,y;
}b[210];

bool cmp(const bottle &a,const bottle &b){
	return a.y<b.y;
}

void init(){
	ans1=ans2=0;
	for(int i=1;i<=n;i++)
		scanf("%d",&a[i]);
	for(int i=1;i<=m;i++)
		scanf("%d %d",&b[i].x,&b[i].y);
}

void make(int v){
	for(int i=1;i<=m;i++)
		if(b[i].y>=v && b[i].x){
			ans1++,ans2+=v;
			b[i].x--;
			break;
		}
}

void solve(){
	sort(a+1,a+1+n);
	sort(b+1,b+1+m,cmp);
	for(int i=n;i>=1;i--)
		make(a[i]);
	cout<<ans1<<' '<<ans2<<endl;
}

int main(){
	freopen("ball.in","r",stdin);
	freopen("ball.out","w",stdout);
	while(1){
		scanf("%d %d",&n,&m);
		if(!n && !m) break;
		init();
		solve();
	}
	return 0;
}
