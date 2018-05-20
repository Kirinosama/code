#include <cstdio>

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

int T, N;

int main(int argc, char** argv)
{
	freopen("string.in", "r", stdin);
	freopen("string.out", "w", stdout);
	
	IO >> T;
	while (T--)
	{
		IO >> N;
		int r, cnt(0);
		static int res[2005];
		for (r = 1; r * (r - 1) / 2 < N; ++r)
			;
		N = r * (r - 1) / 2 - N;
		for (int i(r - 1); i > 1; --i)
			while (N >= i * (i - 1) / 2)
				N -= i * (i - 1) / 2, r -= res[cnt++] = i;
		for (int i(0); i != cnt; ++i)
			for (int c(res[i]); c; --c)
				putchar('0' + (i & 1));
		for (int c(0); c != r; ++c)
			putchar('0' + ((cnt + c) & 1));
		putchar('\n');
	}
	
	return 0;
}
