#include <cstdlib>
#include <cstdio>
#include <cstring>
#include <iostream>
using namespace std;

#define MAXN 60
const int MOD=10000;

int n,m,s,t,k,nfish;
int dis[MAXN][MAXN];
int cant[12][MAXN];

struct square
{
	int N,M;
	int num[MAXN][MAXN];
	square operator * (square a)
	const{
		square b;
		b.N=N;b.M=a.M;
		memset(b.num,0,sizeof(b.num));
		for(int i=1;i<=b.N;i++)
			for(int j=1;j<=b.M;j++)
				for(int p=1;p<=M;p++)
				{
					b.num[i][j]+=num[i][p]*a.num[p][j];
					b.num[i][j]%=MOD;
				}
		return b;
	}
	void print()
	{
		for(int i=1;i<=N;i++)
		{
			for(int j=1;j<=M;j++)
				printf("%d ",num[i][j]);
			cout<<endl;
		}
		cout<<endl;
	}
}sq[12],per;

square pow(square x,int k)
{
	if(!k) return per;
	if(k==1) return x;
	if(k%2) return x*pow(x,k-1);
	return pow(x*x,k/2);
}

void read()
{
	scanf("%d %d %d %d %d",&n,&m,&s,&t,&k);
	s++,t++;
	for(int i=1;i<=m;i++)
	{
		static int x,y;
		scanf("%d %d",&x,&y);
		x++,y++;
		dis[x][y]=dis[y][x]=1;
	}
	scanf("%d",&nfish);
	for(int i=1;i<=nfish;i++)
	{
		static int T,to[4];
		scanf("%d",&T);
		for(int j=1;j<=T;j++){
			scanf("%d",&to[j]);
			to[j]++;
			for(int p=j-1;p<12;p+=T)
			{
				cant[p][to[j]]=1;
		//		printf("cant[%d][%d]=%d\n",p,to[j],cant[p][to[j]]);
			}
		}
	}
}

void premake()
{
	for(int i=0;i<12;i++)
	{
		sq[i].N=sq[i].M=n;
		for(int j=1;j<=n;j++)
			for(int p=1;p<=n;p++)
			{
				if(dis[j][p]==1 && !cant[(i+1)%12][p])
					sq[i].num[j][p]=1;
				else sq[i].num[j][p]=0;
			}
	//	sq[i].print();
	}
}

void solve()
{
	square st;
	st.N=1,st.M=n;per.N=n;per.M=n;
	memset(st.num,0,sizeof(st.num));
	memset(per.num,0,sizeof(per.num));
	st.num[1][s]=1;
	for(int i=1;i<=n;i++)
		per.num[i][i]=1;
	int turns=k/12;int rem=k%12;
	for(int i=0;i<12;i++)
		st=st*pow(sq[i],turns);
	for(int i=0;i<rem;i++)
		st=st*sq[i];
	printf("%d",st.num[1][t]);
}

int main()
{
	freopen("input","r",stdin);
//	freopen("output","w",stdout);
	read();
	premake();
	solve();
}