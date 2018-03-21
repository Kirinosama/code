#include <cstdlib>
#include <cstdio>
#include <cstring>
#include <iostream>
#include <algorithm>
using namespace std;

#define MAXN 150010
#define MAXM 200010
#define ii pair<int,int>
#define INF 0x3f3f3f3f
typedef long long ll;

struct edge{
	int x,y,a,b;
	edge(){};
	edge(int x_,int y_,int a_,int b_){x=x_,y=y_,a=a_,b=b_;}
	void in(){scanf("%d%d%d%d",&x,&y,&a,&b);}
};

struct graph{
	int last[MAXN],ne[MAXM],edge_cnt;
	edge E[MAXM];
	void edge
}

int main(){
    freopen("bzoj3669.in","r",stdin);
    scanf("%d%d",&n,&m);
    for(int i=1;i<=m;i++)G1.E[i].in();
    return 0;
}