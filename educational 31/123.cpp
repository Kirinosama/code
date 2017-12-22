#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

const int N = 100005;

int a[N], s[N], f[N], n, k, m, top;
ll ans;

int main()
{
	cin >> n >> k >> m;
	for (int i = 1; i <= n; i++)
		scanf("%d", a + i);
	if (k >= n)
	{
		bool flag = 1;
		for (int i = 2; i <= n; i++)
			 if (a[i] != a[i - 1]) flag = 0;
		if (flag) cout << (ll)n * m % k;
			 else cout << (ll)n * m << endl;
		return 0;
	}
	for (int i = 1; i <= n; i++)
	{
		s[++top] = a[i];
		if(top > 1&&s[top] == s[top - 1])
			f[top] = f[top - 1] + 1;
		else
			f[top] = 1;
		if (f[top] == k) top -= k;
	}
	int L = 1, R = top;
	while (s[L] == s[R]&&L != R)
	{
		int l = L, r = R, cnt = 0;
		while(s[L]==s[l]&&l < r&&cnt < k) ++l, ++cnt;
		while(s[R]==s[r]&&l < r&&cnt < k) --r, ++cnt;
		if (cnt == k) L = l, R = r, ans += k;
				 else break;
	}
	bool flag = 1;
	for (int i = L + 1; i <= R; i++)
		if(s[i]!=s[i-1]) flag = 0;
	if(flag) cout << ((ll)(R-L+1) * m % k ? (ll)(R - L + 1) * m % k + ans : 0);
		else cout << ans+(ll)(R-L+1)*m;
	return 0;
}