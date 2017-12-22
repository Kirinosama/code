#include <cstdlib>
#include <cstdio>
#include <cstring>
#include <iostream>
#include <algorithm>
#include <vector>
#include <queue>
using namespace std;
//poj 1201

#define MAXN 100010
#define P pair<int,int>

int n,Max,Min,dis[MAXN];
bool instack[MAXN];
vector <P> to[MAXN];

void spfa(){
	queue <int> Q;
	for(int i=Min;i<=Max;i++)
		dis[i]=-1e9;
	dis[Min]=0;Q.push(Min);instack[Min]=true;
	while(!Q.empty()){
		int cur=Q.front();Q.pop();instack[cur]=false;
		for(int i=0;i<to[cur].size();i++){
			int v=to[cur][i].first;
			if(dis[v]<dis[cur]+to[cur][i].second)
			{
				dis[v]=dis[cur]+to[cur][i].second;
				if(!instack[v]) instack[v]=true,Q.push(v);
			}
		}
	}
	printf("%d",dis[Max]);
}

int main()
{
    freopen("cfys.in","r",stdin);
    cin>>n;
    for(int i=1;i<=n;i++){
    	static int x,y,z;
    	scanf("%d %d %d",&x,&y,&z);
    	x++;y++;
    	to[x-1].push_back(P(y,z));
    	Min=min(Min,x-1);
    	Max=max(Max,y);
    }
    for(int i=Min;i<=Max;i++){
    	to[i-1].push_back(P(i,0));
    	to[i].push_back(P(i-1,-1));
    }
    spfa();
    return 0;
}