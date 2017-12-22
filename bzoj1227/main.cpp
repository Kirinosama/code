#include <cstdlib>
#include <cstdio>
#include <cstring>
#include <vector>
#include <queue>
#include <map>
#include <algorithm>
#include <iostream>
using namespace std;

#define MAXN 100010
#define MOD 2147483647 

struct node
{
	int x,y;
}p[MAXN];

vector <int> v;
map <int,int> mp;
int w,k,len;
int l[MAXN],r[MAXN],u[MAXN],d[MAXN];
int lcnt[MAXN],dcnt[MAXN],uu[MAXN],dd[MAXN];
int c[MAXN][20],t[MAXN],ans;

bool cmp(node a,node b)
{
	if(a.y==b.y) return a.x<b.x;
	return a.y<b.y;
}

int lowbit(int x) {return x&-x;}

int cal(int x)
{
	int sum=0;
	for(int i=x;i;i-=lowbit(i))
		sum+=t[i];
	return sum;
}

void update(int x,int k)
{
	for(int i=x;i<=len;i+=lowbit(i))
		t[i]+=k;
}

int getsum(int x,int y)
{
	if(x>y) return 0;
	if(x==0) return cal(y);
	else return cal(y)-cal(x-1);
}

void premake()
{
	for(int i=1;i<=w;i++)
		v.push_back(p[i].x),v.push_back(p[i].y);
	sort(v.begin(),v.end());
	len=unique(v.begin(),v.end())-v.begin();
	for(int i=0;i<len;i++) mp[v[i]]=i+1;
	for(int i=1;i<=w;i++)
	{
		p[i].x=mp[p[i].x],p[i].y=mp[p[i].y];
	//	printf("%d %d\n",p[i].x,p[i].y);
	}		
	sort(p+1,p+1+w,cmp);
	for(int i=1;i<=w;i++)
	{
		lcnt[p[i].y]++;dcnt[p[i].x]++;
		l[i]=lcnt[p[i].y];d[i]=dcnt[p[i].x];
	}
	for(int i=1;i<=w;i++)
		r[i]=lcnt[p[i].y]-l[i]+1,u[i]=dcnt[p[i].x]-d[i]+1;
	c[0][0]=1;c[0][1]=0;
	for(int i=1;i<=len;i++)
	{
		c[i][0]=1;
		for(int j=1;j<=k;j++) c[i][j]=c[i-1][j]+c[i-1][j-1];
	}
}

void solve(int pos)
{
	update(p[pos].x,c[u[pos]-1][k]*c[d[pos]][k]-c[u[pos]][k]*c[d[pos]-1][k]);
	if(pos>1 && p[pos].y==p[pos-1].y)
		ans+=getsum(p[pos-1].x+1,p[pos].x-1)*c[l[pos-1]][k]*c[r[pos]][k];
}

int main()
{
	freopen("input","r",stdin);
	scanf("%d %d %d",&w,&w,&w);
	for(int i=1;i<=w;i++)
		scanf("%d %d",&p[i].x,&p[i].y);
	scanf("%d",&k);
	premake();
	for(int i=1;i<=w;i++)
		solve(i);
	cout<<((ans)&MOD);
	return 0;
}