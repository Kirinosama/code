#include <cstdlib>
#include <cstdio>
#include <cstring>
#include <iostream>
#include <algorithm>
using namespace std;

#define MAXN 50010
#define ii pair<int,int>
#define INF 0x3f3f3f3f
typedef long long ll;

int n,a[MAXN],b[MAXN],f[MAXN],c[MAXN],pos[MAXN];

int lowbit(int x){
	return x&-x;
}

void update(int x,int k){
	for(int i=x;i<=n;i+=lowbit(i))
		c[i]=max(c[i],k);
}

int getmax(int x){
	int Max=0;
	for(int i=x;i;i-=lowbit(i))
		Max=max(Max,c[i]);
	return Max;
}

int main(){
    freopen("formation.in","r",stdin);
    freopen("formation.out","w",stdout);
    cin>>n;int ans=0;
    for(int i=1;i<=n;i++)scanf("%d",&a[i]);
    for(int i=1;i<=n;i++)scanf("%d",&b[i]),pos[b[i]]=i;
    for(int i=1;i<=n;i++){
    	f[i]=getmax(pos[a[i]])+1;
    	update(pos[a[i]],f[i]);
    	ans=max(ans,f[i]);
    }
    cout<<ans;
    return 0;
}