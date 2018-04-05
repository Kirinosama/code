#include <cstdlib>
#include <cstdio>
#include <cstring>
#include <iostream>
#include <algorithm>
#include <stack>
#include <vector>
using namespace std;

#define MAXN 100010
#define MAXM 200010
#define ii pair<int,int>
#define INF 0x3f3f3f3f
typedef long long ll;

struct edge{
	int x,y;
}E[MAXM];

stack <int> s;
vector <int> bcc[MAXM];
int edge_cnt,last[MAXN],ne[MAXM];
int n,m,dfn[MAXN],low[MAXN],bccno[MAXN],bcccnt,ti;

void add_edge(int x,int y){
	E[++edge_cnt]=(edge){x,y};
	ne[edge_cnt]=last[x];
	last[x]=edge_cnt;
}

void tarjan(int x,int pre){
	dfn[x]=low[x]=++ti;
	for(int i=last[x];i;i=ne[i])if(i!=(pre^1)){
		int y=E[i].y;
		if(!dfn[y]){
			s.push(i);tarjan(y,i);
			low[x]=min(low[x],low[y]);
			if(low[y]>=dfn[x]){
				bcccnt++;
				while(1){
					int cur=s.top();s.pop();
					if(bccno[E[cur].x]!=bcccnt) bcc[bcccnt].push_back(E[cur].x),bccno[E[cur].x]=bcccnt;
					if(bccno[E[cur].y]!=bcccnt) bcc[bcccnt].push_back(E[cur].y),bccno[E[cur].y]=bcccnt;
					if(cur==i) break;
				}
			}
		}else if(dfn[y]<dfn[x]){
			s.push(i);
			low[x]=min(low[x],dfn[y]);
		}
	}
}

int main(){
    freopen("tarjan_bcc.in","r",stdin);
    cin>>n>>m;edge_cnt=1;
    for(int i=1;i<=m;i++){
    	int x,y;
    	scanf("%d%d",&x,&y);
    	add_edge(x,y);add_edge(y,x);
    }
    tarjan(1,-1);
    for(int i=1;i<=bcccnt;i++){
    	for(int j=0;j<bcc[i].size();j++)
    		printf("%d ",bcc[i][j]);
    	cout<<endl;
    }
    return 0;
}
