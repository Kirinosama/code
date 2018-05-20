
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <iostream>
#include <algorithm>
using namespace std;

typedef long long LL;

const LL INF = (LL)1E18;

LL N;
LL pw[20];
int a[20], n;
LL Ans;

int Calc (LL X) {
	int i = 0;
	while (pw[i] <= X) ++i;
	return i;
}

bool Judge (int L, int R, LL X) {
	if (a[L] == 0) return false;
	if (X <= 0) return false;
	LL tmp = 0;
	for (int i = L; i <= R; ++i)
		tmp = tmp * 10 + a[i];
	return (tmp == X);
}

bool Judge1 (int R, LL X) {
	if (R == 0) return true;
	if (X <= 0) return false;
	LL tmp = 0;
	for (int i = 1; i <= R; ++i)
		tmp = tmp * 10 + a[i];
	return (tmp == X % pw[R]);
}

bool Judge2 (int L, LL X, int len) {
	if (L == n + 1) return true;
	if (X <= 0) return false;
	LL tmp = 0;
	for (int i = L; i <= n; ++i)
		tmp = tmp * 10 + a[i];
	return (tmp == X / pw[len - (n - L + 1)]);
}

void Work () {
	scanf ("%lld", &N), n = 0, Ans = INF;
	LL tmp = N; while (tmp) a[++n] = tmp % 10, tmp /= 10;
	reverse (a + 1, a + n + 1);
	for (int i = 1, j; i <= n; ++i) {
		for (j = 1; j <= i && j + i - 1 <= n; ++j) {
			tmp = 0; bool flag = false;
			if (a[j] == 0) continue ;
			for (int k = j; k <= j + i - 1; ++k)
				tmp = tmp * 10 + a[k];
			if (!Judge1 (j - 1, tmp - 1)) continue ;
			for (int k = j + i, len = i; k <= n; k += len) {
				len = Calc (++tmp);
				if (k + len - 1 <= n)
				{
					if (!Judge (k, k + len - 1, tmp)) {
						flag = true; break ;
					}
				}
				else
				{
					if (!Judge2 (k, tmp, len)) {
						flag = true; break ;
					}
				}
			}
			if (flag) continue ;
			Ans = min (Ans, tmp);
		}
		for (; j <= i; ++j) {
			int x = j - 1, y = n - x;
			if (a[x + 1] == 0) continue ;
			tmp = 0; LL val = 0;
			for (int k = 1; k <= x; ++k)
				tmp = tmp * 10 + a[k];
			++tmp; bool flag = false;
			for (int k = i + 1; k <= n; ++k)
				if (a[k] != (tmp / pw[x - (k - i)]) % 10) {
					flag = true; break ;
				}
			if (flag) continue ;
			for (int k = x + 1; k <= n; ++k)
				val = val * 10 + a[k];
			val = val * pw[x - (n - i)] + tmp % pw[x - (n - i)];
			Ans = min (Ans, val);
		}
		if (Ans != INF) {printf ("%lld\n", Ans); return ;}
	}
}

int main () {
	freopen ("number.in", "r", stdin),
	freopen ("number.out", "w", stdout);
	pw[0] = 1;
	for (int i = 1; i <= 18; ++i)
		pw[i] = pw[i - 1] * 10ll;
	int test;
	scanf ("%d", &test);
	while (test--) Work ();
	return 0;
}

