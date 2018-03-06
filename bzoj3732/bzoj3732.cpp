#include <cstdlib>
#include <cstdio>
#include <cstring>
#include <iostream>
#include <algorithm>
#include <vector>
using namespace std;

#define MAXN 30010
#define MAXM 30010
#define MAXQ 30010
#define ii pair<int,int>
#define INF 0x3f3f3f3f
typedef long long ll;

struct edge{
	int x,y,z;
	void in(){scanf("%d%d%d",&x,&y,&z);}	
	bool operator < (const edge &a)const{
		return z<a.z;
	}
}E[MAXM];

vector <ii> ID[MAXN];
vector <int> son[MAXN];
int fa[MAXN],n,m,q,ans[MAXQ];

int find(int x){
	return fa[x]==x?x:fa[x]=find(fa[x]);
}

void kruskal(){
	for(int k=1;k<=m;k++){
		int fx=find(E[k].x);
		int fy=find(E[k].y);
		if(fx==fy) continue;
		if(son[fx].size()>son[fy].size()) swap(fx,fy);
		for(int i=0;i<son[fx].size();i++){
			int cur=son[fx][i];
			for(int j=0;j<ID[cur].size();j++)if(!ans[ID[cur][j].second])
				if(find(ID[cur][j].first)==fy) ans[ID[cur][j].second]=E[k].z;
		}
		for(int i=0;i<son[fx].size();i++) son[fy].push_back(son[fx][i]);
		fa[fx]=fy;son[fx].clear();
	}
}

int main(){
    freopen("bzoj3732.in","r",stdin);
    scanf("%d%d%d",&n,&m,&q);
    for(int i=1;i<=n;i++)fa[i]=i,son[i].push_back(i);
    for(int i=1;i<=m;i++)E[i].in();
    for(int i=1;i<=q;i++){
    	int x,y;
    	scanf("%d%d",&x,&y);
    	ID[x].push_back(ii(y,i));
    	ID[y].push_back(ii(x,i));
    }
    sort(E+1,E+1+m);
    kruskal();
    for(int i=1;i<=q;i++) printf("%d\n",ans[i]);
    return 0;
}