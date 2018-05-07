#include <cstdlib>
#include <cstdio>
#include <cstring>
#include <iostream>
#include <algorithm>
#include <queue>
using namespace std;

#define eps 1e-9
#define ii pair<int,int>
#define INF 0x3f3f3f3f
typedef long long ll;

int T,n,m,go[4][2]={{0,1},{0,-1},{1,0},{-1,0}};
double res,len,dis[110][110];
bool instack[110][110];
char a[110][110];
ii s,t;

double spfa(double mid){
    queue<ii>Q;Q.push(s);
    memset(instack,0,sizeof(instack));
    instack[s.first][s.second]=true;
    for(int i=0;i<n;i++)for(int j=0;j<m;j++)dis[i][j]=INF;
    dis[s.first][s.second]=0;
    while(!Q.empty()){
        ii tp=Q.front();Q.pop();instack[tp.first][tp.second]=false;
        for(int i=0;i<4;i++){
            int tx=tp.first+go[i][0];
            int ty=tp.second+go[i][1];
            if(tx<0 || tx>=n || ty<0 || ty>=m || a[tx][ty]=='#') continue;
            double val=i>1?mid:1.0;
            if(dis[tp.first][tp.second]+val<dis[tx][ty]){
                dis[tx][ty]=dis[tp.first][tp.second]+val;
                if(!instack[tx][ty])instack[tx][ty]=true,Q.push(ii(tx,ty));
            }
        }
    }
    return dis[t.first][t.second];
}

int main(){
    freopen("bzoj2709.in","r",stdin);
    scanf("%d",&T);
    while(T--){
        scanf("%lf%d%d\n",&len,&n,&m);
        for(int i=0;i<n;i++){
            gets(a[i]);
            for(int j=0;j<m;j++){
                if(a[i][j]=='S')s=ii(i,j);
                if(a[i][j]=='E')t=ii(i,j);
            }
        }
        double l=0,r=10;
        while(r-l>eps){
            double mid=(l+r)/2.0;
            if(spfa(mid)<=len) res=mid,l=mid;
            else res=mid,r=mid;
        }
        printf("%.5lf\n",res);
    }
    return 0;
}
