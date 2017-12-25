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
	cnt=0;
	for(int i=1;i<=l;i++){
		if(!ne[i]){
			v[++cnt].clear();v[cnt].push_back(0);last[i]=cnt;
		}
		else{
			v[last[ne[i]]].push_back(ne[i]);last[i]=last[ne[i]];
		}
		int t=last[i];
		ll pos=upper_bound(v[t].begin(),v[t].end(),i/2)-v[t].begin();
		ans=(ans*pos)%MOD;
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
