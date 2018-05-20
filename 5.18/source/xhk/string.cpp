#include <bits/stdc++.h>
using namespace std;
int tot;
int ans[30];
bool dfs(int l, int s) {
	if(l == 0) {
		if(s == 0) {
			return 1;
		} else {
			return 0;
		}
	}
	for(int i = 1; i <= l; ++i) {
		if(s >= i * i) {
			ans[++tot] = i;
			if(dfs(l - i, s - i * i)) return 1;
			--tot;
		}
	}
	return 0;
}
int main() {
	freopen("string.in", "r", stdin);
	freopen("string.out", "w", stdout);
	int T; scanf("%d", &T);
	while(T--) {
		int t; scanf("%d", &t);
		int l = 0, r = t, n = 0, sum = 0;
		tot = 0;
		while(r - l > 1) {
			int mid = (l + r) >> 1;
			if(mid * (mid - 1) / 2 > t) r = mid;
			else l = n = mid;
		}
		while(n * (n - 1) / 2 < t) ++n;
		dfs(n, n * n - 2 * t);	
		for(int i = 1, p = 0; i <= tot; ++i, p ^= 1) {
			while(ans[i]--) printf("%c", (char)(p + '0'));
		}
		puts("");
	}
	fclose(stdin);
	fclose(stdout);
	return 0;
}
