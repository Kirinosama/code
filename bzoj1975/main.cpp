#include <cstdlib>
#include <cstdio>
#include <cstring>
#include <iostream>
#include <vector>
#include <queue>
using namespace std;

#define MAXN 5010

vector <pair<int,double> > e[MAXN];
vector <pair<int,double> > e1[MAXN];
double dist[MAXN],k;
bool instack[MAXN];
int n,m;

struct pri_queue
{
	struct node
	{
		int x;
		double d,dd;
	}t[MAXN*500],null;

	int cnt;

	node top(){	return t[1];}
	int empty(){	return cnt ? 0 : 1;}
	void up(int x)
	{
		if(x==1) return;
		if(t[x].dd<t[x>>1].dd)
		{
			swap(t[x],t[x>>1]);
			up(x>>1);
		}
	}
	void down(int x)
	{
		x<<=1;
		if(x>cnt) return;
		if(x<cnt && t[x+1].dd<t[x].dd) x++;
		if(t[x].dd<t[x>>1].dd) 
		{
			swap(t[x>>1],t[x]);
			down(x);
		}
	}
	void insert(int x,double d,double dd)
	{
		t[++cnt]=(node){x,d,dd};
		up(cnt);
	}
	void pop()
	{
		t[1]=t[cnt--];
		down(1);
	}
}pq;

void spfa()
{
	queue <int> Q;
	memset(dist,0x3f,sizeof(dist));
	dist[n]=0;instack[n]=true;Q.push(n);
	while(!Q.empty())
	{
		int tp=Q.front();Q.pop();instack[tp]=false;
		for(int i=0;i<e1[tp].size();i++)
		{
			int v=e1[tp][i].first;
			if(dist[v]>dist[tp]+e1[tp][i].second)
			{
				dist[v]=dist[tp]+e1[tp][i].second;
				if(!instack[v]) 
					Q.push(v),instack[v]=true;
			}
		}
	}
}

void astar()
{
	int ans=0;
	pq.cnt=0;
	pq.insert(1,0,dist[1]);
	while(!pq.empty())
	{
		pri_queue::node tp=pq.top();pq.pop();
		if(tp.x==n) 
		{
			if(k>=tp.dd) ans++,k-=tp.dd;
			else break;
		}
		else
		{
			for(int i=0;i<e[tp.x].size();i++)
			{
				int v=e[tp.x][i].first;
				pq.insert(v,tp.d+e[tp.x][i].second,tp.d+e[tp.x][i].second+dist[v]);
			}
		}
	}
	printf("%d",ans);
}

int main()
{
	freopen("input","r",stdin);
	scanf("%d %d %lf",&n,&m,&k);
	for(int i=1;i<=m;i++)
	{
		static int x,y;
		static double v;
		scanf("%d %d %lf",&x,&y,&v);
		e[x].push_back(make_pair(y,v));
		e1[y].push_back(make_pair(x,v));
	}
	spfa();
	astar();
	return 0;
}