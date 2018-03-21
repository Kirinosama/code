#include <cstdlib>
#include <cstdio>
#include <cstring>
#include <iostream>
#include <algorithm>
#include <vector>
using namespace std;

#define MAXN 1000010

typedef long long ll;
const ll MOD=1000000007;

vector <int> v[MAXN];
string s;
int pre[MAXN][25];
int ne[MAXN],n,cnt,last[MAXN];

void solve(){
	cin>>s;ll ans=1;
	int l=s.length();s=' '+s;
	ne[1]=0;ne[0]=-1;
	for(int i=1;i<l;i++){
		int cur=ne[i];
		while(cur!=-1 && s[cur+1]!=s[i+1]) cur=ne[cur];
		if(s[cur+1]==s[i+1]) ne[i+1]=cur+1;
		else ne[i+1]=0;
	}
	for(int i=1;i<=l;i++){
		ll res=1;
		pre[i][0]=ne[i];
		for(int j=1;j<=20;j++)
			pre[i][j]=pre[i][j-1]==0?0:pre[pre[i][j-1]][j-1];
		int cur=i;
		for(int j=20;j>=0;j--)
			if(pre[cur][j]!=0)
				res+=(1<<j),cur=pre[cur][j];
		cur=i;
		for(int j=20;j>=0;j--)
			if(pre[cur][j]>i/2)
				res-=(1<<j),cur=pre[cur][j];
		ans=(ans*res)%MOD;
	}
	printf("%lld\n",ans);
}

int main(){
	freopen("p2375.in","r",stdin);
	scanf("%d",&n);
	while(n--)
		solve();
	return 0;
}
