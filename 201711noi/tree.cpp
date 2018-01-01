#include <cstdlib>
#include <cstdio>
#include <cstring>
#include <iostream>
#include <algorithm>
using namespace std;

#define MAXN 100010
#define ii pair<int,int>
#define INF 0x3f3f3f3f
typedef long long ll;

int n,m,a[MAXN],sum[MAXN],father[MAXN];

void query(int x){
	printf("%d\n",sum[x]);
}

void change(int l,int r,int x){
	for(int i=l;i<=r;i++){
		for(int j=father[i];j;j=father[j])
			sum[j]-=sum[i];
	}
	for(int i=l;i<=r;i++){
		father[i]=x;
		for(int j=father[i];j;j=father[j])
			sum[j]+=sum[i];
	}
}

void update(int x,int v){
	for(int i=x;i;i=father[i])
		sum[i]+=v-a[x];
	a[x]=v;
}

void solve(){
	int type,x,l,r,v;
	scanf("%d %d",&type,&x);
	switch(type){
		case 0:
			scanf("%d %d",&l,&r);
			change(l,r,x);break;
		case 1:
			scanf("%d",&v);
			update(x,v);break;
		case 2:
			query(x);
	}
}

void premake(){
	for(int i=2;i<=n;i++){
		sum[i]=a[i],sum[1]+=a[i];
		father[i]=1;
	}
	father[1]=0;
	sum[1]+=a[1];
}

int main(){
    freopen("tree.in","r",stdin);
    freopen("tree.out","w",stdout);
    cin>>n>>m;
    for(int i=1;i<=n;i++)
    	scanf("%d",&a[i]);
    premake();
    while(m--)
    	solve();
    return 0;
}