#include <cstdlib>
#include <cstdio>
#include <cstring>
#include <iostream>
#include <algorithm>
using namespace std;

#define MAXN 1010
#define MAXM 2*MAXN
#define ii pair<int,int>
#define INF 0x3f3f3f3f
typedef long long ll;

struct edge{
	int x,y;
}E[MAXM];

int top,n,b,last[MAXN],ne[MAXM],edge_cnt;
int root[MAXN],vis[MAXN],s[MAXN*10],fam_cnt,fam[MAXN];

inline int read(){
	int x=0,w=0;char ch;
	while(ch<'0' || ch>'9')
		w|=(ch=='-'),ch=getchar();
	while(ch>='0' && ch<='9')
		x=(x<<1)+(x<<3)+(ch^48),ch=getchar();
	return w?-x:x;
}

void add(int x,int y){
	E[++edge_cnt]=(edge){x,y};
	ne[edge_cnt]=last[x];
	last[x]=edge_cnt;
}

void dfs(int x){
	int cur=top;vis[x]=1;
	for(int i=last[x];i;i=ne[i]){
		int y=E[i].y;
		if(vis[y]) continue;
		dfs(y);
		if(top-cur>=b){
			fam_cnt++;root[fam_cnt]=x;
			for(int &j=top;j!=cur;j--)
				fam[s[j]]=fam_cnt;
		}
	}
	s[++top]=x;
}

int main(){
    freopen("bzoj1086.in","r",stdin);
    cin>>n>>b;
    for(int i=1;i<n;i++){
    	int x=read(),y=read();
    	add(x,y);add(y,x);
    }
    dfs(1);
    while(top)
    	fam[s[top--]]=fam_cnt;
    if(!fam_cnt){
    	cout<<0;return 0;
    }
    else{
    	cout<<fam_cnt<<endl;
   		for(int i=1;i<=n;i++)
   			printf("%d ",fam[i]);
   		cout<<endl;
   		for(int i=1;i<=fam_cnt;i++)
   			printf("%d ",root[i]);
    }
    return 0;
}