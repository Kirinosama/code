#include <cstdlib>
#include <cstdio>
#include <set>
#include <iostream>
using namespace std;

#define MAXN 100010
#define ld(x,y) ((x)+(y))
#define rd(x,y) (n+1-(x)+(y))
#define P pair<int,int>

int n,m,k,sx,sy,func;
long long ans,xx,yy,tx,ty;
char s[10];int cnt;
set <P> rd[2*MAXN];
set <P> ld[2*MAXN];

bool operator < (const P &a,const P &b)
{
	if(a.first==b.first)
		return a.second<b.second;
	else
		return a.first<b.first;
}

void read()
{
	int x,y;
	scanf("%d %d",&x,&y);
	rd[rd(x,y)].insert(P(x,y));
	ld[ld(x,y)].insert(P(x,y));
}

int main()
{
	freopen("input","r",stdin);
	cin>>n>>m>>k;
	for(int i=1;i<=k;i++)
		read();
	for(int i=0;i<=m+1;i++)
	{
		int x=0;int y=i;
		rd[rd(x,y)].insert(P(x,y));
		ld[ld(x,y)].insert(P(x,y));
		x=n+1;y=i;
		rd[rd(x,y)].insert(P(x,y));
		ld[ld(x,y)].insert(P(x,y));
	}

	for(int i=1;i<=n;i++)
	{
		int x=i;int y=0;
		rd[rd(x,y)].insert(P(x,y));
		ld[ld(x,y)].insert(P(x,y));
		x=i;y=m+1;
		rd[rd(x,y)].insert(P(x,y));
		ld[ld(x,y)].insert(P(x,y));
	}

	cin>>sx>>sy;
	scanf("%s",s);	
	func=0;
	if(s[0]=='N') func |=1;
	if(s[1]=='E') func |=2;
	int sfunc=func;

	xx=sx;yy=sy;
	int t=10;
	while(t--)
	{
		if(func==0)
	    {
	    	if(ld(xx,yy)==ld(sx,sy) && cnt && func==(sfunc^3))
	    	{
	    		if(xx<=sx)
	    		{
	    			ans+=(long long)(abs(sx-xx));
	    			cout<<ans;
	    			break;
	    		}
	    	}
	    	P pos=*(ld[ld(xx,yy)].lower_bound(P(xx,yy)));
	    	tx=pos.first-1; ty=pos.second+1;
	    	cout<<xx<<' '<<yy<<' '<<'-'<<' '<<tx<<' '<<ty<<endl;
	    	ans+=(long long)(abs(tx-xx)+1);
	    	if(ld[ld(xx,yy)-1].count(P(tx,ty-1))==ld[ld(xx,yy)+1].count(P(tx+1,ty)))
	    	{xx=tx;yy=ty;func=3;}
	    	else if(ld[ld(xx,yy)-1].count(P(tx,ty-1)))
	    	{xx=tx+1;yy=ty;func=2;}
	    	else
	    	{xx=tx;yy=ty-1;func=1;}
	    	cnt++;
	    	// cout<<ans<<endl;
	    }
	    if(func==1)
	    {
	    	if(rd(xx,yy)==rd(sx,sy) && cnt && func==(sfunc^3))
	    	{
	    		if(xx>=sx)
	    		{
	    			ans+=(long long)(abs(sx-xx));
	    			cout<<ans;
	    			break;
	    		}
	    	}
	    	P pos=*(--rd[rd(xx,yy)].lower_bound(P(xx,yy)));
	    	tx=pos.first+1; ty=pos.second+1;
	    	cout<<xx<<' '<<yy<<' '<<'-'<<' '<<tx<<' '<<ty<<endl;
	    	ans+=(long long)(abs(tx-xx)+1);
	    	if(rd[rd(xx,yy)-1].count(P(tx,ty-1))==rd[rd(xx,yy)+1].count(P(tx-1,ty)))
	    	{xx=tx;yy=ty;func=2;}
	    	else if(rd[rd(xx,yy)-1].count(P(tx,ty-1)))
	    	{xx=tx-1;yy=ty;func=3;}
	    	else
	    	{xx=tx;yy=ty-1;func=0;}
	   		 cnt++;
		    // cout<<ans<<endl;
	    }
	    if(func==2)
	    {
	    	if(rd(xx,yy)==rd(sx,sy) && cnt && func==(sfunc^3))
	    	{
	    		if(xx<=sx)
	    		{
	    			ans+=(long long)(abs(sx-xx));
	    			cout<<ans;
	    			break;
	    		}
	    	}
	    	P pos=*(rd[rd(xx,yy)].lower_bound(P(xx,yy)));
	    	tx=pos.first-1; ty=pos.second-1;
	    	cout<<xx<<' '<<yy<<' '<<'-'<<' '<<tx<<' '<<ty<<endl;
	    	ans+=(long long)(abs(tx-xx)+1);
	    	if(rd[rd(xx,yy)-1].count(P(tx+1,ty))==rd[rd(xx,yy)+1].count(P(tx,ty+1)))
	    	{xx=tx;yy=ty;func=1;}
	    	else if(rd[rd(xx,yy)-1].count(P(tx+1,ty)))
	    	{xx=tx;yy=ty+1;func=3;}
	    	else
	    	{xx=tx+1;yy=ty;func=0;}
	  		 cnt++;
	    	// cout<<ans<<endl;
	    }
	    if(func==3)
	    {
	    	if(ld(xx,yy)==ld(sx,sy) && cnt && func==(sfunc^3))
	    	{
	    		if(xx>=sx)
	    		{
	    			ans+=(long long)(abs(sx-xx));
	    			cout<<ans;
	    			break;
	    		}
	    	}
	    	P pos=*(--ld[ld(xx,yy)].lower_bound(P(xx,yy)));
	    	tx=pos.first+1; ty=pos.second-1;
	    	cout<<xx<<' '<<yy<<' '<<'-'<<' '<<tx<<' '<<ty<<endl;
	    	ans+=(long long)(abs(tx-xx)+1);
	    	if(ld[ld(xx,yy)-1].count(P(tx-1,ty))==ld[ld(xx,yy)+1].count(P(tx,ty+1)))
	    	{xx=tx;yy=ty;func=0;}
	    	else if(ld[ld(xx,yy)-1].count(P(tx-1,ty)))
	    	{xx=tx;yy=ty+1;func=2;}
	    	else
	    	{xx=tx-1;yy=ty;func=1;}
	  		  cnt++;
	    	// cout<<ans<<endl;
	    }
	}

	return 0;
}