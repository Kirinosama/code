#include <cstdlib>
#include <cstdio>
#include <algorithm>
#include <iostream>
using namespace std;

#define MAXN 100010
#define P pair<int,int>
#define ld(x) (x.first+x.second)
#define rd(x) (n+1-x.first+x.second) 
#define rr(x) (pair<int,int>(x.first,x.second+1))
#define ll(x) (pair<int,int>(x.first,x.second-1))
#define uu(x) (pair<int,int>(x.first-1,x.second))
#define dd(x) (pair<int,int>(x.first+1,x.second))
#define dis(x,y) ((long long)(abs(x.first-y.first)+1))

int n,m,k,func,sfunc,sx,sy,cnt,flag;
long long ans;
P ld[MAXN*6],rd[MAXN*6];
int rd_end[3*MAXN],ld_start[3*MAXN],ld_end[2*MAXN],rd_start[2*MAXN];
char s[10];

bool operator < (const P &a,const P &b)
{
	if(a.first==b.first)
		return a.second<b.second;
	else
		return a.first<b.first;	
}

bool cmp1(const P &a,const P &b)
{
	if(a.first+a.second==b.first+b.second)
		return a.first<b.first;
	else
		return a.first+a.second<b.first+b.second;
}

bool cmp2(const P &a,const P &b)
{
	if(a.second-a.first==b.second-b.first)
		return a.first<b.first;
	else
		return a.second-a.first<b.second-b.first;
}


void add(int x,int y)
{
	ld[++cnt]=P(x,y);
	rd[cnt]=P(x,y);	
}

void read()
{
	int x,y;
	scanf("%d %d %d",&n,&m,&k);
	for(int i=1;i<=k;i++)
	{
		scanf("%d %d",&x,&y);	
		add(x,y);
	}
	for(int i=0;i<=m+1;i++)
	{
		add(0,i);
		add(n+1,i);	
	}
	for(int i=1;i<=n;i++)
	{
		add(i,0);
		add(i,m+1);	
	}
	sort(ld+1,ld+cnt+1,cmp1);
	sort(rd+1,rd+cnt+1,cmp2);
	
	for(int i=1;i<=cnt;i++)
	{
		if(ld(ld[i])!=ld(ld[i-1]))
		ld_start[ld(ld[i])]=i;
		ld_end[ld(ld[i-1])]=i-1;	
	}
	ld_start[ld(ld[1])]=1;
	ld_end[ld(ld[cnt])]=cnt;
	for(int i=1;i<=cnt;i++)
	{
		if(rd(rd[i])!=rd(rd[i-1]))
		rd_start[rd(rd[i])]=i;
		rd_end[rd(rd[i-1])]=i-1;	
	}
	rd_start[rd(rd[1])]=1;
	rd_end[rd(rd[cnt])]=cnt;
	scanf("%d %d",&sx,&sy);
	scanf("%s",s);
	if(s[0]=='N') func|=1; 
	if(s[1]=='E') func|=2;
	sfunc=func;
}

void print()
{
	// for(int i=1;i<=cnt;i++)
	// 	printf("%d %d\n",ld[i].first,ld[i].second);
	// for(int i=1;i<=cnt;i++)
	// 	printf("%d %d\n",rd[i].first,rd[i].second);
	// for(int i=0;i<=8;i++)
	// {
	// 	printf("rd[%d]:%d %d\n",i,rd_start[i],rd_end[i]);		
	// }	
}

P find(P now)
{
	P to;
	int l,r,mid;
	P res;
	if(func==0)
	{
		l=ld_start[ld(now)];
		r=ld_end[ld(now)];
		while(l<r)
		{
			mid=(l+r)/2;
			if(ld[mid]<=now)
				l=mid+1;
			else
				r=mid;	
		}
		res=rr(uu(ld[l]));
	}	
	if(func==1)
	{
		l=rd_start[rd(now)];
		r=rd_end[rd(now)];
		while(l<r)
		{
			mid=(l+r)/2+1;
			if(rd[mid]>=now)
				r=mid-1;
			else
				l=mid;	
		}
		res=rr(dd(rd[l]));
	}	
	if(func==2)
	{
		l=rd_start[rd(now)];
		r=rd_end[rd(now)];
		while(l<r)
		{
			mid=(l+r)/2;
			if(rd[mid]<=now)
				l=mid+1;
			else
				r=mid;	
		}
		res=ll(uu(rd[l]));
	}	
	if(func==3)
	{
		l=ld_start[ld(now)];
		r=ld_end[ld(now)];
		while(l<r)
		{
			mid=(l+r)/2+1;
			if(ld[mid]>=now)
				r=mid-1;
			else
				l=mid;	
		}
		res=ll(dd(ld[l]));
	}
	if(ld(res)==ld(P(sx,sy))==ld(now) || rd(res)==rd(P(sx,sy))==rd(now))	
	{
		if((sx-res.first)*(sx-now.first)<=0)
		{
			flag=1;
			if(res==P(sx,sy))
			{
				return P(-1,-1);	
			}
			else
			{
				if(func==0)
				return rr(uu(P(sx,sy)));
				if(func==1)
				return uu(dd(P(sx,sy)));
				if(func==2)
				return ll(uu(P(sx,sy)));
				if(func==3)
				return ll(dd(P(sx,sy)));	
			}
		}	
	}
	return res;
}

void update(pair <P,P> &t)
{
	if(S.empty)
	{
		S.push(t);
		ans+=dis(t.first,t.second);
		return;	
	}
	else
	{
		if(S.top().second!=t.first)
		{
			S.push(t);
			ans+=dis(t.first,t.second);
			return;	
		}	
		else
		{
			if((t.second-S.top().first)*(t.second-S.top().second)<0)
			{
				S.push(t);
				return;
			}	
			else if(t.second==S.top().first)
			{
				S.pop();
				return;	
			}
			else
			{
				ans+=(long long)dis((S.top().first,t.second))-1;	
				S.push(t);
			}
		}
	}
}

void flash(P &to)
{
	if(func==0)
	{
		if(to)	
	}
}

void solve()
{
	P now=P(sx,sy);	
	while(!flag)
	{
		P to=find(now);
		pair <P,P> t(now,to);
		update(t);
		flash(to);
	}
	cout<<ans;
}

int main()
{	
	freopen("input","r",stdin);
	freopen("output","w",stdout);
	read();
	solve();
	//print();
	
	return 0;	
}