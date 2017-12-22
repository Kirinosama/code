#include <cstdlib>
#include <cstdio>
#include <cstring>
#include <iostream>
#include <algorithm>
#include <vector>
using namespace std;

#define cost(x,y) (larger[x-1][y+1]+small[x+1][y-1])
#define pos(x) v[i-1]
#define MAXN 10010
#define MAXK 110
#define ii pair<int,int>
#define INF 0x3f3f3f3f
typedef long long ll;

vector <int> v;
int a[MAXN],n,k,small[MAXN][MAXK],larger[MAXN][MAXK],f[MAXN][MAXK];

void premake(){
	for(int i=1;i<=n;i++)
    	for(int j=1;j<=k;j++)
    		larger[i][j]=larger[i-1][j]+(a[i]==j);
    for(int i=1;i<=n;i++)
    	for(int j=k;j>=1;j--)
    		larger[i][j-1]+=larger[i][j];
    for(int i=n;i>=1;i--)
    	for(int j=1;j<=k;j++)
    		small[i][j]=small[i+1][j]+(a[i]==j);
    for(int i=n;i>=1;i--)
    	for(int j=1;j<=k;j++)
    		small[i][j+1]+=small[i][j];

}

void dp(){
	int ans=INF;
	memset(f,0x3f,sizeof(f));
	f[0][1]=0;
	for(int i=1;i<=v.size();i++){
		for(int j=1;j<=k;j++)
			for(int z=1;z<=j;z++)
				f[i][j]=min(f[i][j],f[i-1][z]+cost(pos(i),j));
	}
	for(int i=1;i<=k;i++) ans=min(ans,f[v.size()][i]);
	for(int i=1;i<=n;i++)
		if(a[i]!=-1) ans+=small[i+1][a[i]-1];
	printf("%d",ans);
}

int main(){
    freopen("bzoj1786.in","r",stdin);
    scanf("%d %d",&n,&k);
    for(int i=1;i<=n;i++){
    	scanf("%d",&a[i]);
    	if(a[i]==-1) v.push_back(i);    	
    }
    premake();
    dp();
    return 0;
}