#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <algorithm>

typedef long long int64;

int T, l;
int64 Ans;
char s[25];

int main(int argc, char** argv)
{
	freopen("number.in", "r", stdin);
	freopen("number.out", "w", stdout);
	
	scanf("%d", &T);
	while (T--)
	{
		scanf("%s", s + 1);
		l = strlen(s + 1);
		Ans = atoll(s + 1);
		static char tmp[45];
		for (int i(2); s[i]; ++i)
			if (s[i] != '0')
			{
				for (int j(1); s[j]; ++j)
					tmp[j] = s[j];
				bool c(true);
				for (int j(i - 1); c && j; --j)
					(c = tmp[j] == '9') ? tmp[j] = '0' : ++tmp[j];
				for (int j(l); j >= i; --j)
					tmp[j + 1] = tmp[j];
				tmp[i] = '$';
				static int b[25];
				b[0] = b[1] = 0;
				for (int j(2); j <= l + 1; b[j] += tmp[j] == tmp[b[j] + 1], ++j)
					for (b[j] = b[j - 1]; b[j] && tmp[j] != tmp[b[j] + 1]; b[j] = b[b[j]])
						;
				for (int j(b[l + 1] + 1); j != i; ++j)
					tmp[l + 1 - b[l + 1] + j] = tmp[j];
				tmp[l + 1 - b[l + 1] + i] = '\0';
				Ans = std::min(Ans, atoll(tmp + i + 1));
			}
		for (int w(1), ff(false); !ff && w <= l - 2; ++w)
			for (int i(2); i <= 1 + w && i + w <= l; ++i)
				if (s[i] != '0')
				{
					for (int j(i); j != i + w; ++j)
						tmp[j] = s[j];
					tmp[i + w] = '\0';
					int64 x(atoll(tmp + i));
					for (int j(i - 1), r(x - 1); j; r /= 10, --j)
						tmp[j] = '0' + r % 10;
					int cur(1);
					bool f(true);
					for (; f && tmp[cur]; ++cur)
						f &= tmp[cur] == s[cur];
					for (; f && s[cur]; )
						for (sprintf(tmp + cur, "%lld", ++x); f && tmp[cur] && s[cur]; ++cur)
							f &= tmp[cur] == s[cur];
					if (f)
						Ans = std::min(Ans, x), ff = true;
				}
		printf("%lld\n", Ans);
	}
	
	return 0;
}
