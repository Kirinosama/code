#include <cstdlib>
#include <cstdio>
#include <cstring>
#include <iostream>
#include <algorithm>
#include <queue>
#include <vector>
using namespace std;

/*
kd—tree 查询第k大点对距离
定义函数solve(id,l,r,c)为
利用编号id,端点lr的区间更新答案
写估值函数 表示一个区间与此点距离的最大值 判断是否可以更新答案
若无法更新答案 则不进入此区间

k个元素的堆
pq.size()<k etc
pq.size()>=k && etc etc
*/

#define MAXN 100010
#define MAXM 10010
#define ii pair<int,int>
#define lli pair<long long,int>
#define INF 0x3f3f3f3f
typedef long long ll;

struct point{
	ll x,y;
	int to;
}p[MAXN];

struct query{
	ll x,y;
	int k;
}q[MAXM];

struct cmp{
	bool operator()(const lli &a,const lli &b){
		if(a.first==b.first) return a.second<b.second;
		return a.first>b.first;
	}
};

int n,m,K;
ll X,Y;
ll minx[4*MAXN],maxx[4*MAXN],miny[4*MAXN],maxy[4*MAXN];
priority_queue <lli,vector<lli>,cmp> pq;

bool cmp0(const point &a,const point &b){
	return a.x<b.x;
}

bool cmp1(const point &a,const point &b){
	return a.y<b.y;
}

bool comp(const lli &a,const lli &b){
	if(a.first==b.first) return a.second<b.second;
	return a.first>b.first;
}

void update(int id){
	minx[id]=min(minx[id*2],minx[id*2+1]);
	maxx[id]=max(maxx[id*2],maxx[id*2+1]);
	miny[id]=min(miny[id*2],miny[id*2+1]);
	maxy[id]=max(maxy[id*2],maxy[id*2+1]);
}

void build(int id,int l,int r,int c){
	if(l==r){
		minx[id]=maxx[id]=p[l].x;
		miny[id]=maxy[id]=p[l].y;
		return;
	}
	int mid=(l+r)>>1;
	if(!c) nth_element(p+l,p+mid,p+r+1,cmp0);
	else nth_element(p+l,p+mid,p+r+1,cmp1);
	build(id*2,l,mid,c^1);
	build(id*2+1,mid+1,r,c^1);
	update(id);
}

ll dis(ll a,ll b,ll c,ll d){
	return (a-c)*(a-c)+(b-d)*(b-d);
}

void add(int cur){
	ll dist=dis(p[cur].x,p[cur].y,X,Y);
	if(pq.size()<K) pq.push(lli(dist,p[cur].to));
	else if(comp(lli(dist,p[cur].to),pq.top())) pq.pop(),pq.push(lli(dist,p[cur].to));
}

ll md(int id){
	ll res=0;
	res=max(res,dis(minx[id],miny[id],X,Y));
	res=max(res,dis(minx[id],maxy[id],X,Y));
	res=max(res,dis(maxx[id],miny[id],X,Y));
	res=max(res,dis(maxx[id],maxy[id],X,Y));
	return res;
}

void make(int id,int l,int r,int c){
	if(l==r){
		add(l);
		return;
	}
	int mid=(l+r)>>1;
	if(!c){
		if(X<=maxx[id*2]){
			make(id*2+1,mid+1,r,c^1);
			if(pq.size()<K || (pq.size()>=K && md(id*2)>=pq.top().first))
				make(id*2,l,mid,c^1);
		}
		else{
			make(id*2,l,mid,c^1);
			if(pq.size()<K || (pq.size()>=K && md(id*2+1)>=pq.top().first))
				make(id*2+1,mid+1,r,c^1);
		}
	}
	else{
		if(Y<=maxy[id*2]){
			make(id*2+1,mid+1,r,c^1);
			if(pq.size()<K || (pq.size()>=K && md(id*2)>=pq.top().first))
				make(id*2,l,mid,c^1);
		}
		else{
			make(id*2,l,mid,c^1);
			if(pq.size()<K || (pq.size()>=K && md(id*2+1)>=pq.top().first))
				make(id*2+1,mid+1,r,c^1);
		}
	}
}

void solve(query &Q){
	X=Q.x,Y=Q.y,K=Q.k;
	while(!pq.empty()) pq.pop();
	make(1,1,n,0);
	printf("%d\n",pq.top().second);
}

int main(){
    freopen("bzoj2626.in","r",stdin);
    scanf("%d",&n);
    for(int i=1;i<=n;i++){
    	scanf("%lld %lld",&p[i].x,&p[i].y);
    	p[i].to=i;
    }
    scanf("%d",&m);
    for(int i=1;i<=m;i++)
		scanf("%lld %lld %d",&q[i].x,&q[i].y,&q[i].k);
    build(1,1,n,0);
    for(int i=1;i<=m;i++)
    	solve(q[i]);
    return 0;
}