#include <cstdlib>
#include <cstdio>
#include <cstring>
#include <iostream>
#include <algorithm>
using namespace std;

#define MAXN 20010
#define MAXM 2*MAXN

struct edge{
	int x,y,z;
}E[MAXM];

int edge_cnt,last[MAXN],ne[MAXM],cnt[3],maxson,ans;
int n,rem,root,vis[MAXN],son[MAXN];

void add(int x,int y,int z){
	E[++edge_cnt]=(edge){x,y,z};
	ne[edge_cnt]=last[x];
	last[x]=edge_cnt;
}

void find_root(int x,int fa){
	son[x]=0;int temp=0;
	for(int i=last[x];i;i=ne[i]){
		int y=E[i].y;
		if(vis[y] || y==fa) continue;
		find_root(y,x);
		son[x]+=son[y]+1;
		temp=max(temp,son[y]+1);
	}
	temp=max(temp,rem-son[x]-1);
	if(temp<maxson){
		maxson=temp;root=x;
	}
}

void get_dis(int x,int fa,int dis){
	cnt[dis]++;
	for(int i=last[x];i;i=ne[i]){
		int y=E[i].y;
		if(y==fa || vis[y]) continue;
		get_dis(y,x,(dis+E[i].z)%3);
	}
}

int cal(int x,int v){
	memset(cnt,0,sizeof(cnt));
	get_dis(x,x,v);
	return cnt[0]*cnt[0]+cnt[1]*cnt[2]*2; 
}

void solve(int x){
	memset(cnt,0,sizeof(cnt));
	ans+=cal(x,0);vis[x]=1;
	for(int i=last[x];i;i=ne[i]){
		if(vis[E[i].y]) continue;
		ans-=cal(E[i].y,E[i].z%3);
		rem=son[E[i].y]+1;maxson=1e9;
		find_root(E[i].y,E[i].y);solve(root);
	}
}

int gcd(int x,int y){
	if(!x) return y;
	if(!y) return x;
	return gcd(y,x%y);
}

int main(){
    freopen("bzoj_2152.in","r",stdin);
    cin>>n;rem=n;maxson=1e9;
    for(int i=1;i<n;i++){
    	static int x,y,z;
    	scanf("%d %d %d",&x,&y,&z);
    	add(x,y,z),add(y,x,z);
    }
    find_root(1,1);
    solve(root);
    int Gcd=gcd(n*n,ans);
    printf("%d/%d",ans/Gcd,n*n/Gcd);
    return 0;
}