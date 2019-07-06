#include <bits/stdc++.h>
using namespace std;

#define MAXN 100010
#define ii pair<long long,long long>
typedef long long ll;

ll e[MAXN],sum,f[MAXN];
int n,k;

struct cmp{
	bool operator() (const ii &a,const ii &b){
		return a.second>b.second;
	}
};
priority_queue <ii,vector<ii>,cmp> Q;

int main(){
	freopen("input","r",stdin);
	cin>>n>>k;
	for(int i=1;i<=n;i++)scanf("%lld",&e[i]),sum+=e[i];
	Q.push(ii(0,0));
	for(int i=1;i<=n;i++){
		while(Q.top().first<i-k-1) Q.pop();
		f[i]=e[i]+Q.top().second;
		Q.push(ii(i,f[i]));
	}
	ll ans=0x7fffffffffffffff;
	for(int i=n;i>=max(0,n-k);i--)
		ans=min(ans,f[i]);
	cout<<sum-ans;
	return 0;
}
