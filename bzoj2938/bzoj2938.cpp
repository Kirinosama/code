#include <cstdlib>
#include <cstdio>
#include <cstring>
#include <iostream>
#include <algorithm>
#include <queue>
using namespace std;

#define MAXN 30010
#define ii pair<int,int>
#define INF 0x3f3f3f3f
typedef long long ll;

int n,danger[MAXN],to[MAXN][2],fail[MAXN],cnt;
int ins[MAXN],vis[MAXN];
string s;

void insert(string s){
	int len=s.length();int cur=0;
	for(int i=0;i<len;i++){
		if(!to[cur][s[i]-'0'])
			to[cur][s[i]-'0']=++cnt;
		cur=to[cur][s[i]-'0'];
	}
	danger[cur]=1;
}

void build_fail(){
	queue <int> Q;
	fail[0]=0;
	for(int i=0;i<2;i++)
		if(to[0][i])
			fail[to[0][i]]=0,Q.push(to[0][i]);
	while(!Q.empty()){
		int tp=Q.front();Q.pop();
		for(int i=0;i<2;i++){
			int t=to[tp][i];
			if(!t){
				to[tp][i]=to[fail[tp]][i];
				continue;
			}
			int k=fail[tp];
			while(k && !to[k][i]) k=fail[k];
			fail[t]=to[k][i];
			danger[t]|=danger[to[k][i]];
			Q.push(t);
		}
	}
}

int dfs(int x){
	ins[x]=1;
	for(int i=0;i<2;i++){
		int v=to[x][i];
		if(ins[v])return 1;
		if(vis[v]||danger[v])continue;
		vis[v]=1;
		if(dfs(v))return 1;
	}
	ins[x]=0;
	return 0;
}

int main(){
    freopen("bzoj2938.in","r",stdin);
    cin>>n;
    for(int i=1;i<=n;i++){
    	cin>>s;
    	insert(s);
    }
    build_fail();
    if(dfs(1)) cout<<"TAK";
    else cout<<"NIE";
    return 0;
}