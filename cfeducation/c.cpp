#include <cstdlib>
#include <cstdio>
#include <cstring>
#include <iostream>
#include <algorithm>
#include <map>
using namespace std;

struct node
{
	int x,y;
	bool operator < (node a)
	const{
		if(x==a.x) return y<a.y;
		else return x<a.x;	
	}
}p[110];

typedef long long ll;
ll k,ans1,ans2;
map <node,int> mp;
int a[5][5],b[5][5];
int cnt,st,ed;

void make(int x,int y)
{
	if(x==1 && y==3) ans1++;
	if(x==2 && y==1) ans1++;
	if(x==3 && y==2) ans1++;
	if(y==1 && x==3) ans2++;
	if(y==2 && x==1) ans2++;
	if(y==3 && x==2) ans2++;
}

void solve()
{
	ll len=(ll)ed-st+1;
	ll round=(ll)(k-st+1)/len;
	ll rem=k-(st-1+round*len);
	for(int i=1;i<st;i++)
		make(p[i].x,p[i].y);
	for(int i=1;i<=rem;i++)
		make(p[st+i-1].x,p[st+i-1].y);
	ll cur1=ans1,cur2=ans2;
	for(int i=st;i<=ed;i++)
		make(p[i].x,p[i].y);
	cur1+=(ans1-cur1)*round;
	cur2+=(ans2-cur2)*round;
	cout<<cur1<<' '<<cur2;
}

int main()
{
	freopen("input","r",stdin);
	cin>>k>>p[1].x>>p[1].y;
	for(int i=1;i<=3;i++)
		for(int j=1;j<=3;j++)
			scanf("%d",&a[i][j]);
	for(int i=1;i<=3;i++)
		for(int j=1;j<=3;j++)
			scanf("%d",&b[i][j]);
	mp[p[1]]=1;
	cnt=1;
	while(1)
	{
		int tx=a[p[cnt].x][p[cnt].y];
		int ty=b[p[cnt].x][p[cnt].y];
		p[++cnt]=(node){tx,ty};
		if(!mp[p[cnt]]) mp[p[cnt]]=cnt;
		else 
		{
			st=mp[p[cnt]];
			ed=cnt-1;
			break;
		}
	}
	if(k<=ed)
		for(int i=1;i<=k;i++)
		{
			make(p[i].x,p[i].y);
			cout<<ans1<<' '<<ans2;
			return 0;
		}
	else
		solve();
	return 0;
}
