#include <cstdlib>
#include <cstdio>
#include <cstring>
#include <iostream>
#include <algorithm>
using namespace std;

#define MAXN 310
#define MAXM MAXN*MAXN

struct edge{
	int x,y,k;
}E[MAXM];

int n,edge_cnt,s,fa[MAXN];

bool cmp(const edge &a,const edge &b){
	return a.k<b.k;
}

int find(int x){
	return fa[x]==x ? x : fa[x]=find(fa[x]);
}

void merge(int x,int y){
	if(find(x)!=find(y))
		fa[find(x)]=find(y);
}

void kruskal(){
	int sum=0,cnt=0;
	sort(E+1,E+1+edge_cnt,cmp);
	for(int i=1;i<=edge_cnt;i++){
		int x=E[i].x,y=E[i].y;
		if(find(x)!=find(y)){
			merge(x,y);
			cnt++;sum+=E[i].k;
		}
		if(cnt==n) break;
	}
	cout<<sum;
}

int main(){
    freopen("newstart.in","r",stdin);
    freopen("newstart.out","w",stdout);
    cin>>n;s=n+1;
    for(int i=1;i<=n+1;i++) fa[i]=i;
    for(int i=1;i<=n;i++){
    	static int x;
    	scanf("%d",&x);
    	E[++edge_cnt]=(edge){s,i,x};
    }
    for(int i=1;i<=n;i++)
    	for(int j=1;j<=n;j++){
    		static int x;
    		scanf("%d",&x);
    		if(j>i) E[++edge_cnt]=(edge){i,j,x};
    	}
    kruskal();
    return 0;
}