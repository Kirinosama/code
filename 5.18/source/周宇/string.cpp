
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <iostream>
#include <algorithm>
using namespace std;

typedef long long LL;

const int Maxn = 5E4 + 5;

int N, n;
int num[Maxn];

void Prepare () {
	int N = 5E4;
	for (int i = 1; i <= N; ++i)
		num[i] = (i - 1ll) * i / 2;
}

void Print (int n, int X, int t, int f) {
	while (n) {
		while (num[t] > X) --t;
		for (int i = 1; i <= t; ++i)
			putchar ('0' + f);
		X -= num[t], f = !f, n -= t;
	}
	puts ("");
}

void Work () {
	scanf ("%d", &N), n = 1;
	while (num[n] < N) ++n;
	Print (n, num[n] - N, n, 0);
}

int main () {
	freopen ("string.in", "r", stdin),
	freopen ("string.out", "w", stdout);
	Prepare ();
	int test;
	scanf ("%d", &test);
	while (test--) Work ();
	return 0;
}

