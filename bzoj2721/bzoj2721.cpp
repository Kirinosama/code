#include <cstdlib>
#include <cstdio>
#include <cstring>
#include <iostream>
#include <algorithm>
#include <cmath>
using namespace std;

#define MOD 1000000007
#define ii pair<int,int>
#define INF 0x3f3f3f3f
typedef long long ll;

int n,cnt[1000010];
int zhi[1000010],zhi_cnt,book[1000010];

void solve(int x){
	for(int i=1;i<=zhi_cnt && zhi[i]<=sqrt(x);i++){
		if(!book[x]) break;
		while(!(x%zhi[i]))
			cnt[zhi[i]]++,x/=zhi[i];
	}
	if(x!=1) cnt[x]++;
}

void premake(){
	for(int i=2;i<=n;i++)
		if(!book[i]){
			zhi[++zhi_cnt]=i;
			for(int j=i*2;j<=n;j+=i)
				book[j]=1;
		}
}

int main(){
    freopen("bzoj2721.in","r",stdin);
    scanf("%d",&n);
    premake();
    for(int i=1;i<=n;i++)
    	solve(i);
    ll ans=1;
    for(int i=2;i<=n;i++)
    	ans=ans*(cnt[i]*2+1)%MOD;
    printf("%lld",ans);
    return 0;
}