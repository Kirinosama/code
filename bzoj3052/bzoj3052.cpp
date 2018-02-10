#include <cstdlib>
#include <cstdio>
#include <cstring>
#include <iostream>
#include <algorithm>
#include <cmath>
#include <vector>
using namespace std;

#define MAXM 100010
#define MAXN 100010
#define MAXQ 100010
#define ii pair<int,int>
#define INF 0x3f3f3f3f
typedef long long ll;

inline int read(){
	char ch;int w=0,x=0;
	while(ch<'0' || ch>'9') w|=(ch=='-'),ch=getchar();
	while(ch>='0' && ch<='9') x=(x<<1)+(x<<3)+(ch^48),ch=getchar();
	return w?-x:x;
}

struct Change{
	int x,last,now;
}C[MAXQ];

struct Query{
	int x,y,t,ID;
}Q[MAXQ];

int n,m,q,v[MAXM],w[MAXN],c[MAXN],c1[MAXN],query_cnt,change_cnt;
int dfn[MAXN],ti,sqr,cnt[MAXM],vis[MAXN],dep[MAXN],anc[MAXN][25];
ll ans,anss[MAXQ];
vector <int> to[MAXN];

bool cmp(const Query &a,const Query &b){
	if(dfn[a.x]/sqr==dfn[b.x])
		return dfn[a.y]<dfn[b.y];
	return dfn[a.x]/sqr<dfn[b.x]/sqr;
}

void dfs(int x,int f){
	dfn[x]=++ti;dep[x]=dep[f]+1;anc[x][0]=f;
	for(int i=1;i<=20;i++) anc[x][i]=anc[anc[x][i-1]][i-1];
	for(int i=0;i<to[x].size();i++)if(to[x][i]!=f){
		dfs(to[x][i],x);
	}
}

void change_ans(int k,int x,int y){
	if(x<y) ans+=(ll)v[k]*(ll)w[y];
	else ans-=(ll)v[k]*(ll)w[y];
}

void change_col(int pos,int col1,int col2){
	if(vis[pos]){
		change_ans(col1,cnt[col1],cnt[col1]-1);
		change_ans(col2,cnt[col2],cnt[col2]+1);
		cnt[col1]--,cnt[col2]++;
	}
	c[pos]=col2;
}

void reverse(int x,int y){
	int pos=x;
	while(1){
		if(!vis[x]){
			change_ans(c[x],cnt[c[x]],cnt[c[x]]+1);
			cnt[c[x]]++;
		}else{
			change_ans(c[x],cnt[c[x]],cnt[c[x]]-1);
			cnt[c[x]]--;
		}vis[x]^=1;
		if(pos==y) break;
		pos=anc[pos][0];
	}
}

inline int lca(int x,int y){
	if(dep[x]<dep[y]) swap(x,y);
	for(int i=20;i>=0;i--)if(dep[x]-(1<<i)>=dep[y])
		x=anc[x][i];
	if(x==y) return x;
	for(int i=20;i>=0;i--)if(anc[x][i]!=anc[y][i])
		x=anc[x][i],y=anc[y][i];
	return anc[x][0];
}

int main(){
    freopen("bzoj3052.in","r",stdin);
    n=read(),m=read(),q=read();
    for(int i=1;i<=m;i++)v[i]=read();
    for(int i=1;i<=n;i++)w[i]=read();
    for(int i=1;i<n;i++){
    	static int x=read(),y=read();
    	to[x].push_back(y),to[y].push_back(x);
    }
    for(int i=1;i<=n;i++)c[i]=read(),c1[i]=c[i];
    while(q--){
    	static int type=read(),x=read(),y=read();
    	if(!type){
    		C[++change_cnt]=(Change){x,c1[x],y};c1[x]=y;
    	}else{
    		query_cnt++;
    		Q[query_cnt]=(Query){x,y,change_cnt,query_cnt};
    	}	
    }
    dfs(1,1);sqr=(int)sqrt(n);
    sort(Q+1,Q+1+query_cnt,cmp);
    int X=1,Y=1,t=0;
    ans=(ll)w[1]*(ll)v[c[1]];vis[1]=1;cnt[c[1]]=1;
    for(int i=1;i<=query_cnt;i++){
    	int x=Q[i].x,y=Q[i].y,T=Q[i].t;
    	int lcax=lca(x,X),lcay=lca(y,Y);
    	if(t<T){
    		for(int i=t+1;i<=T;i++) change_col(C[i].x,C[i].last,C[i].now);
    	}else{
    		for(int i=t;i>T;i--) change_col(C[i].x,C[i].now,C[i].last);
    	}
    	reverse(x,lcax);reverse(X,lcax);reverse(y,lcay);reverse(Y,lcay);
    	reverse(lca(X,Y),lca(X,Y));reverse(lca(x,y),lca(x,y));
    	anss[Q[i].ID]=ans;X=x,Y=y,t=T;
    }
    for(int i=1;i<=query_cnt;i++) printf("%lld\n",anss[i]);
    return 0;
}