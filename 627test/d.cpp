#include <iostream>
#include <cstdio>
#include <cmath>
#include <cstring>
#include <cstdlib>
#include <algorithm>
#include <string>
#include <queue>
#include <map>
#define INF 0x3f3f3f3f
#define NO 100005
#define MO 100005
typedef long long ll;
typedef double db;
using namespace std;
inline ll read()
{
	char ch = ' ', last;
	ll ans = 0;
	while (ch < '0' || ch > '9')
		last = ch, ch = getchar();
	while (ch >= '0' && ch <= '9')
		ans = ans * 10 + int(ch - '0'), ch = getchar();
	if (last == '-')
		return -ans;
	return ans;
}
void write(ll x)
{
	if (x >= 10)
		write(x / 10);
	putchar(x % 10 + '0');
}
//head

ll n, c, cnt, fib[NO], a[NO], cnt2;
//variable

void init()
{
	cin>>n;
	fib[1]=fib[2]=1;cnt=2;
	while (fib[cnt] + fib[cnt - 1] <= 1e9)
		fib[cnt+1] = fib[cnt] + fib[cnt-1],cnt++;
	for (int i = 2; i <= cnt; i++)
		for (int j = 2; j <= i; j++)
			for (int k = 2; k <= j; k++)
				a[++cnt2] = fib[i] + fib[j] + fib[k];
	sort(a + 1, a + cnt2 + 1);
}
//functions

int main()
{
	//freopen("a.txt", "w", stdout);
	init();
	while (n--)
	{
		//ll c = read();
		ll c;
		scanf("%lld",&c);	
		int l = lower_bound(a + 1, a + cnt2 + 1, c) - a;
		if (a[l] == c)
			puts("MINAMI");
		else
			puts("KOTORI");
	}
	return 0;
}
//main

