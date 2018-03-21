#include <cstdio>
#include <cstring>
#define f(x, y, z) for(int x = (y); x <= (z); ++x)

int n, m, v[100086], dp[100086];

int main(){
	freopen("mining.in","r",stdin);
	//freopen("mining7.out","w",stdout);
	scanf("%d%d", &n, &m);
	memset(v, 0, sizeof(v));
	while(n--){
		int a, b; scanf("%d%d", &a, &b);
		v[b] += a;
	}
	dp[0] = 0; int ans = 0;
	f(i, 1, m){
		dp[i] = -200000000;
		if(i >= 4){
			int c = dp[i - 4] + v[i];
			if(c > dp[i]) dp[i] = c;
		}
		if(i >= 7){
			int c = dp[i - 7] + v[i];
			if(c > dp[i]) dp[i] = c;
		}
		if(dp[i] > ans) ans = dp[i];
	}
	printf("%d\n", ans);
	return 0;
}
