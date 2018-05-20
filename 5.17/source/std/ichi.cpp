#include <cstdio>
#include <cstdlib>
#include <algorithm>
#include <vector>
#include <cstring>
#define SIZE 100005
#define BT 1024*128*2
#define INF 1000000000

using namespace std;
typedef long long int ll;

struct RMQ
{
	vector <int> seg;
	int mum;
	
	void init(int n)
	{
		mum=1;
		while(mum<n) mum<<=1;
		seg.resize(mum*2,INF);
	}
	void ins(int k,int x)
	{
		k+=mum-1;
		seg[k]=x;
		while(k>0)
		{
			k=(k-1)/2;
			seg[k]=min(seg[k*2+1],seg[k*2+2]);
		}
	}
	int get(int a,int b,int k,int l,int r)
	{
		if(b<=l||r<=a) return INF;
		if(a<=l&&r<=b) return seg[k];
		else
		{
			int vl=get(a,b,k*2+1,l,(l+r)/2);
			int vr=get(a,b,k*2+2,(l+r)/2,r);
			return min(vl,vr);
		}
	}
	int get(int a,int b)
	{
		return get(a,b,0,0,mum);
	}
};
struct BIT
{
	vector <ll> bit;
	
	void init(int n)
	{
		bit.resize(n+2,0);
	}
	void add(int k,int x)
	{
		k++;
		while(k<bit.size())
		{
			bit[k]+=x;
			k+=k&-k;
		}
	}
	ll get(int k)
	{
		k++;
		ll ret=0;
		while(k>0)
		{
			ret+=bit[k];
			k-=k&-k;
		}
		return ret;
	}
	ll get(int s,int t)
	{
		return get(t)-get(s-1);
	}
};
struct segtree
{
	vector <BIT> bit;
	vector < vector <int> > nd;
	int mum;
	
	void init(int n)
	{
		mum=1;
		while(mum<n) mum<<=1;
		bit.resize(mum*2);
		nd.resize(mum*2);
	}
	void ins(int k,int x)
	{
		k+=mum-1;
		nd[k].push_back(x);
		while(k>0)
		{
			k=(k-1)/2;
			nd[k].push_back(x);
		}
	}
	void build()
	{
		for(int i=0;i<mum*2;i++)
		{
			sort(nd[i].begin(),nd[i].end());
			nd[i].erase(unique(nd[i].begin(),nd[i].end()),nd[i].end());
			bit[i].init(nd[i].size());
		}
	}
	int id(int k,int x)
	{
		return lower_bound(nd[k].begin(),nd[k].end(),x)-nd[k].begin();
	}
	void add(int a,int b,int k,int l,int r,int low,int v)
	{
		if(b<=l||r<=a) return;
		if(a<=l&&r<=b) bit[k].add(id(k,low),v);
		else
		{
			add(a,b,k*2+1,l,(l+r)/2,low,v);
			add(a,b,k*2+2,(l+r)/2,r,low,v);
		}
	}
	void add(int a,int b,int low,int v)
	{
		add(a,b,0,0,mum,low,v);
	}
	ll get(int k,int x)
	{
		k+=mum-1;
		ll ret=bit[k].get(0,id(k,x));
		while(k>0)
		{
			k=(k-1)/2;
			ret+=bit[k].get(0,id(k,x));
		}
		return ret;
	}
};
struct edge
{
	int to,cost;
	edge(int to=0,int cost=0):to(to),cost(cost){}
};
vector <edge> vec[SIZE];
vector <segtree> s1;
vector <RMQ> s2;
int V[SIZE];
int nd[SIZE],par[SIZE];
int cmb[SIZE],id[SIZE],len[SIZE];
int back[SIZE];
int now_id;
int n,q;

void dfs(int v=0,int p=-1)
{
	nd[v]=1;
	for(int i=0;i<vec[v].size();i++)
	{
		edge e=vec[v][i];
		if(e.to!=p)
		{
			dfs(e.to,v);
			par[e.to]=e.cost;
			nd[v]+=nd[e.to];
		}
	}
	if(p==-1) par[v]=-1;
}
void heavy_light(int v=0,int p=-1,int bef=-1)
{
	cmb[v]=now_id;
	id[v]=len[now_id]++;
	back[v]=bef;
	bool up=true;
	for(int i=0;i<vec[v].size();i++)
	{
		edge e=vec[v][i];
		if(e.to!=p&&nd[e.to]*2>=nd[v])
		{
			up=false;
			heavy_light(e.to,v,bef);
			break;
		}
	}
	if(up)
	{
		segtree S1;
		RMQ S2;
		S1.init(len[now_id]+2);
		S2.init(len[now_id]+2);
		s1.push_back(S1);
		s2.push_back(S2);
		now_id++;
	}
	for(int i=0;i<vec[v].size();i++)
	{
		edge e=vec[v][i];
		if(e.to!=p&&nd[e.to]*2<nd[v])
		{
			heavy_light(e.to,v,v);
		}
	}
}
void bef_ins(int v)
{
	s2[cmb[v]].ins(id[v],par[v]);
}
void ins(int v)
{
	int mn=INF;
	while(v!=-1)
	{
		s1[cmb[v]].ins(id[v],mn);
		mn=min(mn,s2[cmb[v]].get(0,id[v]+1));
		v=back[v];
	}
}
void build()
{
	for(int i=0;i<n;i++) bef_ins(i);
	for(int i=0;i<n;i++) ins(i);
	for(int i=0;i<s1.size();i++) s1[i].build();
}
void query2(int v,int x,int y)
{
	int l=id[v],r=len[cmb[v]];
	while(r-l>1)
	{
		int m=(l+r)/2;
		if(s2[cmb[v]].get(id[v]+1,m+1)>=y) l=m;
		else r=m;
	}
	s1[cmb[v]].add(id[v],l+1,y,x);
}
ll query1(int v)
{
	int mn=INF;
	ll ret=V[v];
	while(v!=-1)
	{
		ret+=s1[cmb[v]].get(id[v],mn);
		mn=min(mn,s2[cmb[v]].get(0,id[v]+1));
		v=back[v];
	}
	return ret;
}
int main()
{
	freopen("ichi.in","r",stdin);
	freopen("ichi.out","w",stdout);
	int ty;
	scanf("%d %d %d",&n,&q,&ty);
	for(int i=0;i<n;i++) scanf("%d",&V[i]);
	for(int i=0;i<n-1;i++)
	{
		int a,b,w;
		scanf("%d %d %d",&a,&b,&w);a--;b--;
		vec[a].push_back(edge(b,w));
		vec[b].push_back(edge(a,w));
	}
	dfs();
	heavy_light();
	build();
	ll ans=0;
	for(int i=0;i<q;i++)
	{
		int tp;
		scanf("%d",&tp);
		if(tp==1)
		{
			int v;
			scanf("%d",&v);
			if (ty)  v=(v+ans)%n;  else  v--;
			printf("%lld\n",ans=query1(v));
		}
		else
		{
			int x,y,v;
			scanf("%d %d %d",&x,&y,&v);
			if (ty)  v=(v+ans)%n;  else  v--;
			query2(v,x,y);
		}
	}
	return 0;
}
