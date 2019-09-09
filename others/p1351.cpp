#include <bits/stdc++.h>
using namespace std;

const int Mod=10007;
int a[200010],Max,sum,n;
vector <int> to[200010];

void solve(int x){
	int tot=0,max1=0,max2=0;
	for(int i=0;i<to[x].size();i++){
		int y=a[to[x][i]];
		sum=(sum+y*tot)%Mod,tot=(tot+y)%Mod;
		if(y>=max1) max2=max1,max1=y;
		else if(y>max2) max2=y;
	}
	Max=max(Max,max1*max2);
}

int main(){
	freopen("input","r",stdin);
	cin>>n;
	for(int i=1;i<n;i++){
		static int x,y;
		scanf("%d%d",&x,&y);
		to[x].push_back(y);
		to[y].push_back(x);
	}
	for(int i=1;i<=n;i++)
		scanf("%d",&a[i]);
	for(int i=1;i<=n;i++)
		solve(i);
	cout<<Max<<' '<<(sum*2)%Mod;
	return 0;
}
