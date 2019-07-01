#include <bits/stdc++.h>
using namespace std;

#define MAXN 1000010
#define INF 0x3f3f3f3f
#define ii pair<int,int>
typedef long long ll;

struct offer{
	int num,l,r;
	void in(){scanf("%d%d%d",&num,&l,&r);}
}c[MAXN];

int n,m,a[MAXN],Add[MAXN];

bool judge(int x){
	memset(Add,0,sizeof(Add));
	for(int i=1;i<=x;i++){
		Add[c[i].l]+=c[i].num;
		Add[c[i].r+1]-=c[i].num;
	}
	int cur=0;
	for(int i=1;i<=n;i++){
		cur+=Add[i];
		if(cur>a[i]) return true;
	}
	return false;
}

int main(){
	freopen("input","r",stdin);
	cin>>n>>m;
	for(int i=1;i<=n;i++)
		scanf("%d",&a[i]);
	for(int i=1;i<=m;i++)
		c[i].in();
	int L=1,R=n,ans=0;
	while(L<=R){
		int mid=(L+R)>>1;
		if(judge(mid)) ans=mid,R=mid-1;
		else L=mid+1;
	}
	if(ans==0) cout<<ans;
	else{
		cout<<-1<<endl<<ans;
	}
	return 0;
}
