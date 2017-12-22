#include <cstdlib>
#include <cstdio>
#include <cstring>
#include <iostream>
#include <algorithm>
#include <vector>
using namespace std;

#define MAXN 1010
#define ii pair<int,int>
#define INF 0x3f3f3f3f
typedef long long ll;

struct point{
	int x,y;
}s[MAXN],t[MAXN];

vector <ii> v;
int go[70][70],f[70][70][40],n,m,k,ans,cnt;
char pre[70][70][40];
string anss[5010];

//swne

void make(int x,int y){
	cnt++;
	for(int i=k;i>=1;i--){
		anss[cnt]=pre[x][y][i]+anss[cnt];
		switch (pre[x][y][i]){
			case 'S':y++;break;
			case 'W':x++;break;
			case 'N':y--;break;
			case 'E':x--;
		}
	}
}

void solve(){
	f[30][30][0]=0;
	ans=-1;
	for(int p=1;p<=k;p++){
		for(int i=-p;i<=p;i++)
			for(int j=-p;j<=p;j++){
				if(f[i+30][j+31][p-1]+go[i+30][j+30]>=f[i+30][j+30][p])
					f[i+30][j+30][p]=f[i+30][j+31][p-1]+go[i+30][j+30],pre[i+30][j+30][p]='S';
				if(f[i+31][j+30][p-1]+go[i+30][j+30]>=f[i+30][j+30][p])
					f[i+30][j+30][p]=f[i+31][j+30][p-1]+go[i+30][j+30],pre[i+30][j+30][p]='W';
				if(f[i+30][j+29][p-1]+go[i+30][j+30]>=f[i+30][j+30][p])
					f[i+30][j+30][p]=f[i+30][j+29][p-1]+go[i+30][j+30],pre[i+30][j+30][p]='N';
				if(f[i+29][j+30][p-1]+go[i+30][j+30]>=f[i+30][j+30][p])
					f[i+30][j+30][p]=f[i+29][j+30][p-1]+go[i+30][j+30],pre[i+30][j+30][p]='E';
				if(p==k && f[i+30][j+30][p]>=ans){
					if(f[i+30][j+30][p]==ans) v.push_back(ii(i,j));
					else ans=f[i+30][j+30][p],v.clear(),v.push_back(ii(i,j));
				}
			}
	}
	printf("%d\n",ans);
	for(int i=0;i<v.size();i++) make(v[i].first+30,v[i].second+30);
	sort(anss+1,anss+cnt+1);
	cout<<anss[1];
}

int main(){
    freopen("bzoj1605.in","r",stdin);
    scanf("%d %d %d",&n,&m,&k);
    for(int i=1;i<=n;i++) scanf("%d %d",&s[i].x,&s[i].y);
    for(int i=1;i<=m;i++) scanf("%d %d",&t[i].x,&t[i].y);
    for(int i=1;i<=n;i++)
    	for(int j=1;j<=m;j++)
    		if(abs(s[i].x-t[j].x)+abs(s[i].y-t[j].y)<=k)
    			go[t[j].x-s[i].x+30][t[j].y-s[i].y+30]++;
    memset(f,0xef,sizeof(f));
    solve();
    return 0;
}