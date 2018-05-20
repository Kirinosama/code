#include <bits/stdc++.h>
using namespace std;
char s[105], st[105];
int main() {
	freopen("number.in", "r", stdin);
	freopen("number.out", "w", stdout);
	int T; scanf("%d", &T);
	while(T--) {
		scanf("%s", s + 1);
		int n = strlen(s + 1);
		long long ans = 0;
		for(int i = 1; i <= n; ++i) ans = ans * 10 + s[i] - '0';
		for(int i = 2; i <= n; ++i) {
			for(int len = n - i + 1; len < n; ++len) {
				if(i - len > 0) {
					long long t = 0;
					for(int j = i - len; j < i; ++j) t = t * 10 + s[j] - '0';
					long long tmp = t + 1;
					int tot = 0;
					while(tmp) {
						st[++tot] = (char)(tmp % 10 + '0');
						tmp /= 10;
					}
					reverse(st + 1, st + tot + 1);
					bool f = 1;
					for(int j = 1; j <= tot && i + j - 1 <= n; ++j) if(st[j] != s[i + j - 1]) {
						f = 0; break;
					}
					for(int k = 1, p = i - 2 * len; p > 0; p -= len, ++k) {
						long long tt = t - k, as = 0;
						if(tt <= 0) {
							f = 0;
							break;
						}
						if(p - len <= 0) {
							int tot = 0;
							while(tt) {
								st[++tot] = tt % 10;
								tt /= 10;
							}
							for(int j = p; j; --j) {
								if(s[j] != st[j + tot - p]) {
									f = 0;
									break;
								}
							}
							break;
						}
						for(int j = p; j < p + len; ++j) as = as * 10 + s[j] - '0';
						if(as != tt) {
							f = 0;
							break;
						}						
					}
					if(f && t > 0) {
						ans = min(ans, t + 1);
					}
				} else if(len * 2 >= n) {
					long long t = 0;
					for(int j = n - i + 1; j <= n; ++j) t = t * 10 + s[j] - '0';
					for(int j = 1; j <= n - i; ++j) t = t * 10 + s[j] - '0';
					long long tmp = t + 1;
					int tot = 0;
					while(tmp) {
						st[++tot] = (char)(tmp % 10 + '0');
						tmp /= 10;
					}
					reverse(st + 1, st + tot + 1);
					bool f = 1;
					for(int j = 1; j <= tot && i + j - 1 <= n; ++j) {
						if(st[j] != s[i + j - 1]) {
							f = 0;
							break;
						}
					}
					if(f && t > 0) {
						ans = min(ans, t + 1);
					}
				}
			}
		}
		printf("%lld\n", ans);
	}
	fclose(stdin);
	fclose(stdout);
	return 0;
}
