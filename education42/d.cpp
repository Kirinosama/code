#include <cstdlib>
#include <cstdio>
#include <cstring>
#include <iostream>
#include <algorithm>
#include <vector>
#include <map>
using namespace std;

#define MAXN 3000010
typedef long long ll;
#define ii pair<int,int>
#define INF 0x3f3f3f3f

map <ll,ll> mp1,mp2;
vector <ll> sor;
vector <int> v[MAXN];
ll a[150010],mul[30];
int n,cnt;
ll ans[150010];

void premake(){
	sort(sor.begin(),sor.end());
	for(int i=0;i<sor.size();i++)if(!mp1[sor[i]]){
		mp1[sor[i]]=++cnt;
		mp2[cnt]=sor[i];
	}
	vector<ll>().swap(sor);
	for(int i=1;i<=n;i++)v[mp1[a[i]]].push_back(i);
}

void solve(){
	int anscnt=0;
	for(int now=1;now<=cnt;now++){
		if(v[now].size()>=2){
			int to=mp1[mp2[now]*2LL];
			for(int i=1;i<v[now].size();i+=2)
				v[to].insert(lower_bound(v[to].begin(),v[to].end(),v[now][i]),v[now][i]);
		}
		if((int)v[now].size()&1) anscnt++,ans[v[now][v[now].size()-1]]=mp2[now]; 
		vector<int>().swap(v[now]);
	}
	cout<<anscnt<<endl;
	for(int i=1;i<=n;i++)if(ans[i])
		cout<<ans[i]<<' ';
}

int main(){
	freopen("input","r",stdin);
	cin>>n;mul[0]=1;
	for(int i=1;i<=20;i++)mul[i]=mul[i-1]*2;
	for(int i=1;i<=n;i++){
		cin>>a[i];
		for(int j=0;j<=20;j++)sor.push_back(a[i]*mul[j]);
	}
	premake();
	solve();
	return 0;
}
