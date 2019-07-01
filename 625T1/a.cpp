#include <cctype>
#include <cmath>
#include <cstdio>
#include <algorithm>
#include <cstring>
#include <stack>
#define INF 0x3f3f3f3f
#define run(a,b,c) for(a=b;a<=c;a++)
using namespace std;
namespace fast
{
	inline int read()
	{
		int num = 0, w = 1; char c = 0;
		while (c != '-' && !isdigit(c)) c = getchar();
		if (c == '-') w = -1, c = getchar();
		while (isdigit(c)) num = num * 10 + c - '0', c = getchar();
		return num * w;
	}

	inline void write(int x)
	{
		if (x < 0) putchar('-'), x = -x;
		if (x / 10) write(x / 10);
		putchar(x % 10 + '0');
	}
}
using namespace fast;

const int MAXN = 1005;

long long h[MAXN][MAXN];

long long ans;

int main()
{
	freopen("input","r",stdin);
	int N;
	N = read();
	for (int j = N - 1; j >= 0; j--)
	{
		for (int i = 0; i <= N - 1; i++)
		{
			scanf("%lld", &h[i][j]);
		}
	}
	for (int i = 1; i <= N - 1; i++)
	{
		for (int j = 1; j <= N - 1; j++)
		{
			int a = i, b = j;
			while (1)
			{
				if (a < b)
				{
					swap(a, b);
				}
				if (a%b == 0)
				{
					break;
				}
				a = a % b;
			}
			if (b == 1)
			{
				//				printf("\n%d %d\n",i,j);
				ans++;
			}
			a = i, b = j;
			long long now = h[i][j];
			while (a <= N - 1 && b <= N - 1)
			{
				a += i, b += j;
				if (h[a][b] > now)
				{
					ans++;
				}
				now = max(now, h[a][b]);
			}
		}
	}
	long long now = h[0][0];
	for (int i = 1; i <= N - 1; i++)
	{
		if (h[0][i] > now)
		{
			ans++;
		}
		now = max(now, h[0][i]);
	}
	now = h[0][0];
	for (int i = 1; i <= N - 1; i++)
	{
		if (h[i][0] > now)
		{
			ans++;
		}
		now = max(now, h[i][0]);
	}
	printf("%lld", ans);
	getchar();
	getchar();
	return 0;
}
