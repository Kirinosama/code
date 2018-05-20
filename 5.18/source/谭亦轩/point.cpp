#include <iostream>
#include <cstdio>
#include <algorithm>

using namespace std;

const size_t	MaxN = 155;

int	N, D, A, B, X[MaxN];
int	Tmp[MaxN], Ans = 0x7F7F7F7F;

void DFS(int i)
{
	if(i > N) {
		static int	tmp[MaxN];
		for(int i = 1; i <= N; ++i)
			tmp[i] = Tmp[i];
		sort(tmp + 1, tmp + 1 + N);
		int	ans = 0, mn = 0x7F7F7F7F;
		for(int i = 1; i <= N; ++i) {
			if(i > 1 && tmp[i] == tmp[i - 1])
				continue;
			mn = min(mn, ans - B * tmp[i]);
			ans = mn + A + B * tmp[i];
		}
		Ans = min(Ans, ans);
		return;
	}
	Tmp[i] = X[i] - D;
	DFS(i + 1);
	Tmp[i] = X[i] + D;
	DFS(i + 1);
}

int main()
{
	freopen("point.in", "r", stdin);
	freopen("point.out", "w", stdout);

	cin >> N >> D >> A >> B;
	for(int i = 1; i <= N; ++i)
		scanf("%d", X + i);

	DFS(1);

	cout << Ans << endl;

	return 0;
}
