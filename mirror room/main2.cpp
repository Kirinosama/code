#include <cstdlib>
#include <cstdio>
#include <set>
#include <stack>
#include <iostream>
using namespace std;

#define MAXN 200010
#define P pair <int,int>
#define ld(x) (ld[x.first+x.second])
#define rd(x) (rd[n+1-x.first+x.second]) 
#define rr(x) (pair<int,int>(x.first,x.second+1))
#define ll(x) (pair<int,int>(x.first,x.second-1))
#define uu(x) (pair<int,int>(x.first-1,x.second))
#define dd(x) (pair<int,int>(x.first+1,x.second))
#define exist(x) (ld(x).count(x) || x.first==0 || x.first==n+1 || x.second==0 || x.second==m+1)
#define dis(x,y) ((long long)(abs(x.first-y.first)+1))


set <P> ld[2*MAXN];
set <P> rd[2*MAXN];
stack < pair<P,P> > S;
int n,m,k,sx,sy,func,flag,sfunc;
long long ans;
char s[20];
  
bool operator < (const P &a,const P &b)
{
	if(a.first==b.first)
		return a.second<b.second;
	else
		return a.first<b.first;
}

bool operator == (const pair<P,P> &a,const pair<P,P> &b)
{
	if(a.first==b.first && a.second==b.second)
		return true;
	if(a.second==b.first && a.first==b.second)
		return true;
	return false;	
}

void read()
{
	P p;
	for(int i=1;i<=k;i++)
	{
		scanf("%d %d",&p.first,&p.second);
		ld(p).insert(p);
		rd(p).insert(p);
	}
}

P find(P now,int func)
{
	P to;
	if(func==0)
	{
		set<P>::iterator it=ld(now).lower_bound(now);
		if(it==ld(now).end())
		{
			to=P(n+1,now.first+now.second-n-1);
			if(to.second<0)
				to=P(to.first+to.second,0);
		}
		else
			to=*it;
		return rr(uu(to));
	}
	else if(func==1)
	{
		set<P>::iterator it=rd(now).lower_bound(now);
		if(it==rd(now).begin())
		{
			to=P(0,now.second-now.first);
			if(to.second<0)
				to=P(to.first-to.second,0);
		}
		else
			to=*(--it);
		return dd(rr(to));
	}
	else if(func==2)
	{
		set<P>::iterator it=rd(now).lower_bound(now);
		if(it==rd(now).end())
		{
			to=P(n+1,n+1+now.second-now.first);
			if(to.second>m+1)
				to=P(to.first-(to.second-m-1),m+1);
		}
		else
			to=*it;
		return uu(ll(to));
	}
	else
	{
		set<P>::iterator it=ld(now).lower_bound(now);
		if(it==ld(now).begin())
		{
			to=P(0,now.first+now.second);
			if(to.second>m+1)
				to=P(to.second-m-1+to.first,m+1);
		}
		else
			to=*(--it);
		return ll(dd(to));
	}
}

P flash(P to)
{
	if(func==0)
	{
		if(exist(ll(to)) == exist (dd(to)))
		{
			func=3;
			return to;
		}
		else if(exist(ll(to)))
		{
			func=2;
			return dd(to);
		}
		else
		{
			func=1;
			return ll(to);
		}
	}
	else if(func==1)
	{
		if(exist(uu(to)) == exist (ll(to)))
		{
			func=2;
			return to;
		}
		else if(exist(uu(to)))
		{
			func=0;
			return ll(to);
		}
		else
		{
			func=3;
			return uu(to);
		}
	}
	else if(func==2)
	{
		if(exist(rr(to)) == exist (dd(to)))
		{
			func=1;
			return to;
		}
		else if(exist(rr(to)))
		{
			func=0;
			return dd(to);
		}
		else
		{
			func=3;
			return rr(to);
		}
	}
	else
	{
		if(exist(rr(to)) == exist (uu(to)))
		{
			func=0;
			return to;
		}
		else if(exist(rr(to)))
		{
			func=1;
			return uu(to);
		}
		else
		{
			func=2;
			return rr(to);
		}
	}
}

long long make(pair<P,P> &b,int &flag)
{
	if(b.first.second+b.first.first==b.second.first+b.second.second && b.first.first+b.first.second==sx+sy && sfunc==func && ans)
	{
		if((sx-b.first.first)*(sx-b.second.first)<=0)
		{
			flag=1;
			if(sx==b.first.first)
				return 0;
			if(sx>b.first.first)
				b.second=rr(uu(P(sx,sy)));
			else
				b.second=ll(dd(P(sx,sy)));
			//return (long long)(dis(P(sx,sy),b.first)-1);
		}
	}
	if(b.first.second-b.first.first==b.second.second-b.second.first && b.first.second-b.first.first==sy-sx && sfunc==func && ans)
	{
		if((sx-b.first.first)*(sx-b.second.first)<=0)
		{
			flag=1;
			if(sx==b.first.first)
				return 0;
			if(sx>b.first.first)
				b.second=ll(uu(P(sx,sy)));
			else
				b.second=rr(dd(P(sx,sy)));
			//return (long long)(dis(P(sx,sy),b.first)-1);
		}
	}
	if(S.empty())
	{
		S.push(b);
		return dis(b.first,b.second);
	}
	else
	{
		pair<P,P> a=S.top();	
		if(a.second!=b.first)
		{
			S.push(b);
			return dis(b.first,b.second);
		}
		else//有重复部分
		{
			if(b.second==a.first)
			{
				S.pop();
				return 0;
			}
			if(b.second<a.first && b.second>=b.first)
			{
				S.push(b);
				return 0;
			}
			if(b.second>a.first && b.first>=b.second)
			{
				S.push(b);
				return 0;
			}
			S.push(b);
			return dis(b.second,a.first)-1;
		}
	}
}

void solve()
{
	P now(sx,sy);
	while(1)
	{
	//	printf("%d %d ",now.first,now.second);
		P to=find(now,func);
	//	printf("%d %d\n",to.first,to.second);
		pair <P,P> t (now,to);//轨迹
		ans+=make(t,flag);//更新答案
	//	cout<<ans<<' '<<func<<endl;
		now=flash(to);//反射
		if(flag)
			break;
	}
	cout<<ans;
}

int main()
{
	freopen("input","r",stdin);	
	freopen("output","w",stdout);
	cin>>n>>m>>k;
	read();
	scanf("%d %d",&sx,&sy);
	scanf("%s",s);
	if(s[0]=='N') func|=1; 
	if(s[1]=='E') func|=2;
	sfunc=func;
	solve();
	return 0;
}