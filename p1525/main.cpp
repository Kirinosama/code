#include <cstdlib>
#include <cstdio>
#include <cstring>
#include <iostream>
#include <algorithm>
using namespace std;

#define MAXN 40010
#define MAXM 100010

struct data{
	int l,r,k;
	bool operator < (const data &a)const{
		return k>a.k;
	}
}p[MAXM];

int n,m,fa[MAXN];

int find(int x){
	return fa[x]==x ? x : fa[x]=find(fa[x]);
}

void merge(int x,int y){
	int fx=find(x),fy=find(y);
	if(fx!=fy) fa[fx]=fy;
}

int main(){
	freopen("input","r",stdin);
	cin>>n>>m;
	for(int i=1;i<=m;i++)
		scanf("%d %d %d",&p[i].l,&p[i].r,&p[i].k);
	sort(p+1,p+1+m);
	for(int i=1;i<=2*n;i++) fa[i]=i;
	for(int i=1;i<=m;i++){
		if(find(p[i].l)==find(p[i].r)){
			cout<<p[i].k;return 0;
		}
		else{
			merge(p[i].l,p[i].r+n);
			merge(p[i].l+n,p[i].r);
		}
	}
	cout<<0;
	return 0;
}