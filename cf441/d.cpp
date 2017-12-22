#include <cstdlib>
#include <cstdio>
#include <cstring>
#include <iostream>
#include <algorithm>
using namespace std;

#define MAXN 300010

int fa[MAXN],x,n,cnt;

int find(int x){
	if(fa[x]==-1) return -1;
	else if(fa[x]==x) return x;
	else return fa[x]=find(fa[x]);
}

void solve(){
	int sum;
	int bg=find(n);
	if(bg==-1) sum=0;
	else sum=n-bg+1;
	cout<<cnt-sum+1<<' ';
}

void merge(int x,int y){
	int tx=find(x);
	int ty=find(y);
	if(tx<ty) fa[ty]=tx;
	else fa[tx]=ty;	
}

void make(int x){
	if(fa[x]==-1) fa[x]=x;
	if(x+1<=n && fa[x+1]!=-1) merge(x,x+1);
	if(x-1>=1 && fa[x-1]!=-1) merge(x,x-1);
}

int main()
{
	freopen("input","r",stdin);
	cin>>n;
	memset(fa,-1,sizeof(fa));
	solve();
	for(int i=1;i<=n;i++){
		scanf("%d",&x);cnt++;
		make(x);
		solve();
	}
	return 0;
}