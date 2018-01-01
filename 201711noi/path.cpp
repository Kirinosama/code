#include <cstdlib>
#include <cstdio>
#include <cstring>
#include <iostream>
#include <algorithm>
using namespace std;

#define MAXN 2010
#define ii pair<int,int>
#define INF 0x3f3f3f3f
typedef long long ll;

int n,m;
ll MOD;
ll ans[9][9]={
{0,0,0,0,0,0,0,0,0},
{0,1,0,0,0,0,0,0,0},
{0,1,1,0,0,0,0,0,0},
{0,2,2,4,0,0,0,0,0},
{0,8,6,12,38,0,0,0,0},
{0,64,32,48,152,728,0,0,0},
{0,1024,320,320,760,3640,26704,0,0},
{0,32768,6144,3840,6080,21840,160224,1866256,0},
{0,0,0,0,0,0,0,0,0}
};

void solve(){
	for(int i=1;i<=n;i++)
		printf("%lld\n",ans[n][i]%MOD);
}

int main(){
    freopen("path.in","r",stdin);
    freopen("path.out","w",stdout);
    scanf("%d %lld",&n,&MOD);
    if(n<=8) solve();
    return 0;
}