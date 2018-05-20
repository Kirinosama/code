
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <iostream>
#include <algorithm>
using namespace std;

typedef long long LL;

namespace INPUT {
	const int L = 1 << 15;
	char _buf[L], *S, *T, c;
	char _gc () {
		if (S == T) {
			T = (S = _buf) + fread (_buf, 1, L, stdin);
			if (S == T) return EOF;
		}
		return *S++;
	}
	void readi (int &X) {
		for (c = _gc (); c < '0' || c > '9'; c = _gc ()); X = c & 15;
		for (c = _gc (); c >= '0' && c <= '9'; X = X * 10 + (c & 15), c = _gc ());
	}
}
using INPUT :: readi;

const int Maxn = 155;
const int INF = 0x3f3f3f3f;

int N, D, A, B;
int a[Maxn], b[Maxn];
int cur[Maxn];
int Ans = INF;

void Check () {
	int Val = A;
	memcpy (cur, b, sizeof (int) * (N + 1));
	sort (cur + 1, cur + N + 1);
	for (int i = 2; i <= N; ++i)
		Val = Val + min (B * (cur[i] - cur[i - 1]), A);
	Ans = min (Ans, Val);
}

void Dfs (int i) {
	if (i > N) {
		Check ();
		return ;
	}
	b[i] = a[i], Dfs (i + 1);
	b[i] = a[i] + D, Dfs (i + 1);
}

namespace _1 {
	void main () {
		Dfs (1);
		printf ("%d", Ans);
		exit (0);
	}
}

namespace _2 {
	bool b[Maxn];
	
	void main () {
		int Ans = 0;
		memset (b, false, sizeof (b));
		for (int i = 1; i <= N; ++i) b[a[i]] = true;
		for (int i = 1; i <= 150 - D; ++i)
			if (b[i] && b[i + D]) Ans += A, b[i] = b[i + D] = false;
		for (int i = 1; i <= 150; ++i)
			Ans += b[i] * A;
		printf ("%d", Ans);
		exit (0);
	}
}

int main () {
	freopen ("point.in", "r", stdin),
	freopen ("point.out", "w", stdout);
	readi (N), readi (D), readi (A), readi (B), D *= 2;
	if (N == 0) {puts ("0"); return 0;}
	for (int i = 1; i <= N; ++i) readi (a[i]);
	if (N <= 20) _1 :: main ();
	_2 :: main ();
	return 0;
}

