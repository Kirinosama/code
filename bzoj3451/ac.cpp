#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<ctime>
#include<cmath>
#include<algorithm>
#include<iomanip>
#include<vector>
#include<map>
#include<set>
#include<bitset>
#include<queue>
#include<stack>
using namespace std;
#define MAXN 60010
#define MAXM 1010
#define INF 1000000000
#define MOD 1000000007
#define eps 1e-8
#define ll long long
const double pi=acos(-1);
struct vec{
	int to;
	int fro;
};
struct cl{
	double x;
	double y;
	cl(){
		
	}
	cl(double _x,double _y){
		x=_x;
		y=_y;
	}
	friend cl operator +(cl x,cl y){
		return cl(x.x+y.x,x.y+y.y);
	}
	friend cl operator -(cl x,cl y){
		return cl(x.x-y.x,x.y-y.y);
	}
	friend cl operator *(cl x,cl y){
		return cl(x.x*y.x-x.y*y.y,x.y*y.x+x.x*y.y);
	}
	friend cl operator /(cl x,double y){
		return cl(x.x/y,x.y/y);
	}
};
vec mp[MAXN];
int tai[MAXN],cnt;
int siz[MAXN],bal[MAXN];
ll ans[MAXN];
bool vis[MAXN];
int tim[MAXN];
int sum,rt,rtf;
int n;
int m;
int T;
int c[MAXN];
int L,R[MAXN];
cl a[MAXN];
double ANS;
inline void be(int x,int y){
	mp[++cnt].to=y;
	mp[cnt].fro=tai[x];
	tai[x]=cnt;
}
inline void bde(int x,int y){
	be(x,y);
	be(y,x);
}
void getrt(int x,int f){
	int i,y;
	siz[x]=1;
	bal[x]=0;
	for(i=tai[x];i;i=mp[i].fro){
		y=mp[i].to;
		if(!vis[y]&&y!=f){
			getrt(y,x);
			siz[x]+=siz[y];
			bal[x]=max(bal[x],siz[y]);
		}
	}
	bal[x]=max(bal[x],sum-siz[x]);
	if(bal[x]<bal[rt]){
		rt=x;
		rtf=f;
	}
}
void dfs(int x,int f,int d){
	int i,y;
	if(tim[d]!=T){
		c[d]=0;
	}
	c[d]++;
	tim[d]=T;
	m=max(m,d);
	for(i=tai[x];i;i=mp[i].fro){
		y=mp[i].to;
		if(y!=f&&!vis[y]){
			dfs(y,x,d+1);
		}
	}
}
void fft(cl *a,int f){
	int i,j,k;
	for(i=0;i<m;i++){
		if(i<R[i]){
			swap(a[i],a[R[i]]);
		}
	}
	for(i=1;i<m;i<<=1){
		cl wn(cos(pi/i),f*sin(pi/i));
		for(j=0;j<m;j+=(i<<1)){
			cl w(1,0);
			for(k=0;k<i;k++,w=w*wn){
				cl x=a[j+k],y=w*a[j+k+i];
				a[j+k]=x+y;
				a[j+k+i]=x-y;
			}
		}
	}
	if(f==-1){
		for(i=0;i<m;i++){
			a[i]=a[i]/m;
		}
	}
}
void cal(int f){
	int i;
	int M=m<<1;
	L=0;
	for(m=1;m<=M;m<<=1){
		L++;
	}
	for(i=0;i<m;i++){
		R[i]=R[i>>1]>>1|((i&1)<<(L-1));
	}
	for(i=0;i<m;i++){
		if(tim[i]!=T){
			c[i]=0;
		}
		a[i].x=c[i];
		a[i].y=0;
	}
	fft(a,1);
	for(i=0;i<m;i++){
		a[i]=a[i]*a[i];
	}
	fft(a,-1);
	for(i=0;i<min(n,m);i++){
		ans[i]+=(ll)(a[i].x+0.1)*f;
	}
}
void work(int x){
	int i,y;
	vis[x]=1;
	m=0;
	T++;
	dfs(x,0,0);
	cal(1);
	for(i=tai[x];i;i=mp[i].fro){
		y=mp[i].to;
		if(!vis[y]){
			m=0;
			T++;
			dfs(y,0,1);
			cal(-1);
			sum=siz[y];
			rt=0;
			getrt(y,0);
			siz[rtf]=sum-siz[rt];
			work(rt);
		}
	}
}
int main(){
    freopen("bzoj3451.in","r",stdin);
	int i,x,y;
	bal[0]=INF;
	scanf("%d",&n);
	for(i=1;i<n;i++){
		scanf("%d%d",&x,&y);
		x++;
		y++;
		bde(x,y);
	}
	sum=n;
	getrt(1,0);
	siz[rtf]=sum-siz[rt];
	work(rt);
	for(i=0;i<=n-1;i++){
		ANS+=1.0*ans[i]/(i+1);
	}
	printf("%.4lf\n",ANS);
	return 0;
}

/*
5
0 1
1 2
1 3
0 4

3
0 1
1 2

*/

