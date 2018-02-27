#include <cstdlib>
#include <cstdio>
#include <cstring>
#include <iostream>
#include <algorithm>
using namespace std;

#define ii pair<int,int>
#define INF 0x3f3f3f3f
typedef long long ll;

vector <int> to[MAXN];
int n,m,q,fa[MAXN],f[MAXN];

inline int find(int x){
	return fa[x]==x?x:fa[x]=find(fa[x]);
}

void solve(){

}

int main(){
    freopen("p2195.in","r",stdin);
    cin>>n>>m>>q;
    for(int i=1;i<=n;i++) fa[i]=i;
    for(int i=1;i<=m;i++) make()
    while(q--) solve();
    return 0;
}