#include <cstdlib>
#include <cstdio>
#include <cstring>
#include <iostream>
#include <algorithm>
#include <queue>
#include <vector>
using namespace std;

#define MAXN 1010
#define MAXM 10010
#define ii pair<int,int>

struct edge{
	int x,y,z;
}E[MAXM];

struct node{
	int x,a,b;
	node(int x_,int a_,int b_){
		x=x_,a=a_,b=b_;
	}
	bool operator < (const node &x)const{
		return a+b>x.a+x.b;
	}
};

int last[MAXN],ne[MAXM],edge_cnt,n,m,k;
int dis[MAXN],ans[MAXN],cnt;
bool instack[MAXN];
vector <ii> to[MAXN];

void add(int x,int y,int z){
	E[++edge_cnt]=(edge){x,y,z};
	ne[edge_cnt]=last[x];
	last[x]=edge_cnt;
}

void spfa(){
	queue <int> Q;
	memset(dis,0x3f,sizeof(dis));
	memset(instack,0,sizeof(instack));
	Q.push(1);instack[1]=true;dis[1]=0;
	while(!Q.empty()){
		int cur=Q.front();Q.pop();instack[cur]=false;
		for(int i=0;i<to[cur].size();i++){
			int y=to[cur][i].first;
			if(dis[y]>dis[cur]+to[cur][i].second){
				dis[y]=dis[cur]+to[cur][i].second;
				if(!instack[y])
					instack[y]=true,Q.push(y);
			}
		}
	}
}

void astar(){
	priority_queue <node> Q;
	Q.push(node(n,0,dis[n]));
	while(!Q.empty()){
		node cur=Q.top();Q.pop();
		if(cur.x==1){
			ans[++cnt]=cur.a;
			if(cnt==k) break;
		}
		for(int i=last[cur.x];i;i=ne[i]){
			int v=E[i].y;
			Q.push(node(v,cur.a+E[i].z,dis[v]));
		}
	}
	for(int i=1;i<=k;i++)
		cout<<(i<=cnt ? ans[i] : -1)<<endl;
}

int main(){
    freopen("bzoj_1598.in","r",stdin);
    cin>>n>>m>>k;
    for(int i=1;i<=m;i++){
    	static int x,y,z;
    	scanf("%d %d %d",&x,&y,&z);
    	add(x,y,z);to[y].push_back(ii(x,z));
    }
    spfa();
    astar();
    return 0;
}