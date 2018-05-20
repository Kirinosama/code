#include <cstdio>
#include <algorithm>

typedef long long int64;

struct IO_Tp
{
	bool is_digit(const char ch) const
	{
		return '0' <= ch && ch <= '9';
	}
	
	IO_Tp& operator>>(int& res)
	{
		res = 0;
		static char ch;
		while (ch = getchar(), !is_digit(ch))
			;
		do
			(res *= 10) += ch & 15;
		while (ch = getchar(), is_digit(ch));
		return *this;
	}
} IO;

int N, D, A, B;
int x[155], p[25], Ans(1 << 30);
bool vis[155], visp[155];

int dfs(const int i)
{
	int res(1);
	vis[i] = true, visp[x[i]] = true; 
	for (int j(0); j != N; ++j)
		if (!vis[j] && !visp[x[j]] && (x[i] - x[j] == D * 2 || x[j] - x[i] == D * 2))
			res += dfs(j);
	return res;
} 

int main(int argc, char** argv)
{
	freopen("point.in", "r", stdin);
	freopen("point.out", "w", stdout);
	
	IO >> N >> D >> A >> B;
	for (int i(0); i != N; ++i)
		IO >> x[i];
	if (N <= 20)
	{
		for (int s(0); s != (1 << N); ++s)
		{
			for (int i(0); i != N; ++i)
				p[i] = s >> i & 1 ? x[i] - D : x[i] + D;
			std::sort(p, p + N);
			int res(A);
			for (int i(1); i != N; ++i)
				res += std::min(A, B * (p[i] - p[i - 1]));
			Ans = std::min(Ans, res);
		}
	}
	else
		for (int i(0); i != N; ++i)
			if (!vis[i] && !visp[x[i]])
				Ans += std::max(1, dfs(i) - 1) * A;
	printf("%d", Ans);
	
	return 0;
}
