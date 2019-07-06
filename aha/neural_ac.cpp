#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

int n,m,k;
ll Max[510],ans,a[510];

int main(){
	freopen("neural6.in","r",stdin);
	cin>>n>>m>>k;
	for(int i=1;i<=n;i++)scanf("%lld",&a[i]);
	for(int i=1;i<=k;i++){
		static int x,y;
		static ll z;
		scanf("%d%d%lld",&x,&y,&z);
		Max[y]=max(Max[y],a[x]*z);
	}
	for(int i=1;i<=m;i++)ans+=Max[i];
	cout<<ans;
	return 0;
}
