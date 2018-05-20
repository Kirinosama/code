#include <iostream>
#include <cstdio>

using namespace std;

const size_t	MaxL = 51, MaxN = 1001;

int	F[MaxL][MaxL][MaxN], Pre[MaxL][MaxL][MaxN];
int	Ans[MaxN];

void DFS(int i, int j, int k)
{
	if(i == 0)
		return;
	DFS(i - 1, Pre[i][j][k], k - j);
	putchar((F[i][j][k] >> 1 & 1) ^ '0');
}

int main()
{
	freopen("string.in", "r", stdin);
	freopen("string.out", "w", stdout);

	F[1][0][0] = 1;
	for(int i = 1; i != 46; ++i)
		for(int j = 0; j <= i; ++j)
			for(int k = 0; k <= min(i * (i - 1) / 2, 1000); ++k)
				if(F[i][j][k]) {
					int	t = k + i;
					F[i + 1][i][t] = F[i][j][k] ^ 2;
					Pre[i + 1][i][t] = j;
					if(!Ans[t])
						Ans[t] = (i + 1) << 10 | i;
					t = k + j;
					F[i + 1][j][t] = F[i][j][k];
					Pre[i + 1][j][t] = j;
					if(!Ans[t])
						Ans[t] = (i + 1) << 10 | j;
				}

	int	T, N;
	cin >> T;
	while(T--) {
		scanf("%d", &N);
		DFS(Ans[N] >> 10, Ans[N] & 0x3FF, N);
		putchar('\n');
	}

	return 0;
}
