#include <iostream>
#include <cstdlib>
#include <cstring>
#include <cstdio>
#include <cmath>
#include <algorithm>
#include <ctime>
#include <vector>
#include <queue>
#include <map>
#include <set>
#ifdef WIN32   
#define OT "%I64d"
#else
#define OT "%lld"
#endif
using namespace std;
typedef long long LL;
const int MAXN = 150;
int n,m;
int w[MAXN][MAXN];
double num[MAXN][MAXN];
double ans[MAXN];

inline int getint()
{
	   int w=0,q=0;
	   char c=getchar();
	   while((c<'0' || c>'9') && c!='-') c=getchar();
	   if (c=='-')  q=1, c=getchar();
	   while (c>='0' && c<='9') w=w*10+c-'0', c=getchar();
	   return q ? -w : w;
}

inline void work(){
	n=getint(); m=getint(); int x,y,z;
	memset(w,127/3,sizeof(w));
	for(int i=1;i<=m;i++) {
	x=getint(); y=getint(); z=getint();
	w[x][y]=w[y][x]=z; num[x][y]=num[y][x]=1;
	}
	for(int k=1;k<=n;k++)
	for(int i=1;i<=n;i++) 
		if(i!=k)
		for(int j=1;j<=n;j++)
			if(j!=k && j!=i) {
			if(w[i][j]>w[i][k]+w[k][j]) {
				w[i][j]=w[i][k]+w[k][j];
				num[i][j]=num[i][k]*num[k][j];
			}
			else if(w[i][j]==w[i][k]+w[k][j]) num[i][j]+=num[i][k]*num[k][j];
			}

	for(int k=1;k<=n;k++) 
	for(int i=1;i<=n;i++) if(i!=k)
		for(int j=1;j<=n;j++)
		if(j!=k && j!=i) {
			if(w[i][j]==w[i][k]+w[k][j]) ans[k]+=((num[i][k]*num[k][j])/num[i][j]);
		}
	for(int i=1;i<=n;i++) printf("%.3lf\n",ans[i]);
}

int main()
{
 	work();
 	return 0;
}