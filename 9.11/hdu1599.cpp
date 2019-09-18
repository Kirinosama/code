#include <cstdlib>
#include <cstring>
#include <cstdio>
#include <algorithm>
#include <iostream>
using namespace std;

const int INF=0x3f3f3f3f;
int n,m,dis[110][110];

int main(){
	freopen("input","r",stdin);
	freopen("output","w",stdout);
	while(scanf("%d%d",&n,&m)!=EOF){
		memset(dis,0x3f,sizeof(dis));
		for(int i=1;i<=m;i++){
			static int x,y,z;
			scanf("%d%d%d",&x,&y,&z);
			dis[x][y]=dis[y][x]=min(dis[x][y],z);
		}	
		for(int i=1;i<=n;i++)dis[i][i]=0;
		int ans=0x7fffffff;
		for(int k=1;k<=n;k++){
			for(int i=1;i<k;i++)
				for(int j=1;j<k;j++){
					if(i==j || dis[i][j]==INF || dis[j][k]==INF || dis[k][i]==INF)
						continue;
					ans=min(ans,dis[i][j]+dis[j][k]+dis[k][i]);
					dis[i][j]=min(dis[i][k]+dis[k][j],dis[i][j]);
				}
		}
		if(ans==0x7fffffff) cout<<"It's impossible."<<endl;
		else cout<<ans<<endl;
	}
	return 0;
}

