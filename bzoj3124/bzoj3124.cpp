#include <cstdlib>
#include <cstdio>
#include <cstring>
#include <iostream>
#include <algorithm>
using namespace std;

#define MAXN 200010
#define MAXM 2*MAXN
#define ii pair<int,int>
#define INF 0x3f3f3f3f
typedef long long ll;

int n,last[MAXN],ne[MAXM],pre[MAXN],edge_cnt,p,q,s[MAXN],cnt;
ll dis[MAXN],Dis1[MAXN],Dis2[MAXN];
bool book[MAXN];

struct edge{
	int x,y;
	ll z;
}E[MAXM];

inline int read(){
	ll x=0;int w=0;char ch;
	while(ch<'0' || ch>'9') w|=(ch=='-'),ch=getchar();
	while(ch>='0' && ch<='9') x=(x<<1)+(x<<3)+(ch^48),ch=getchar();
	return w?-x:x;
}

void add_edge(int x,int y,ll z){
	E[++edge_cnt]=(edge){x,y,z};
	ne[edge_cnt]=last[x];
	last[x]=edge_cnt;
}

void dfs(int x,int f,int &tmp){
	if(dis[x]>dis[tmp]) tmp=x;
	for(int i=last[x];i;i=ne[i]){
		int y=E[i].y;
		if(y==f) continue;
		dis[y]=dis[x]+E[i].z;
		pre[y]=i,dfs(y,x,tmp);
	}
}

void ddfs(int x,int f,ll cur,int &tmp){
	if(cur>tmp) tmp=cur;
	for(int i=last[x];i;i=ne[i]){
		int y=E[i].y;
		if(y==f || book[y]) continue;
		ddfs(y,x,cur+E[i].z,tmp);
	}
}

int main(){
    freopen("bzoj3124.in","r",stdin);
    n=read();
    for(int i=1;i<n;i++){
    	int x=read(),y=read();ll z=read();
    	add_edge(x,y,z);add_edge(y,x,z);
    }
    dfs(1,1,p);
    memset(dis,0,sizeof(dis));
    dfs(p,p,q);
    for(int i=q;;i=E[pre[i]].x){
    	s[++cnt]=i;book[i]=true;
    	if(i==p) break;
    }ll len1=dis[q],len2=0;
    cout<<len1<<endl;
    for(int i=q;;i=E[pre[i]].x){
    	Dis1[i]=len1,Dis2[i]=len2;
    	len1-=E[pre[i]].z,len2+=E[pre[i]].z;
    	if(i==p) break;
    }
    int l=1,r=cnt;
    for(int i=1;i<=cnt;i++){
    	int maxlen=-1;
    	ddfs(s[i],s[i],0,maxlen);
    	if(maxlen>=Dis2[s[i]]) l=i;
    	if(maxlen>=Dis1[s[i]]){
    		r=i;break;
    	}
    }
    printf("%d",r-l);
    return 0;
}