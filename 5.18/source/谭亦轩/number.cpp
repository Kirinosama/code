#include <iostream>
#include <cstdio>
#include <cstring>

using namespace std;

typedef unsigned long long	ll;
const size_t			MaxL = 21;

int	T, N;
char	S[MaxL], tmp1[MaxL], tmp2[MaxL];
ll	Number[MaxL];
ll	Ans;

inline bool issuffix(ll x, ll y)
{
	ll	t = x, res = 1;
	while(t)
		t /= 10, res *= 10;
	return y % res == x;
}

inline bool isprefix(ll x, ll y)
{
	if(!x)
		return false;
	while(y > x)
		y /= 10;
	return x == y;
}

inline ll calc(ll x, ll y)
{
	//cerr << x << ' ' << y << endl;
	static int	tmp[MaxL];
	int		qr = 0;
	ll	tmpx = x;
	do
		tmp[++qr] = tmpx % 10;
	while(tmpx /= 10);
	bool	all0 = true;
	for(int i = 1; i < qr; ++i)
		if(tmp[i] != 0)
			all0 = false;
	if(tmp[qr] != 1 || qr == 1)
		all0 = false;
	if(all0)
		--qr;
	ll	s;
	if(all0) {
		ll	t = y;
		while(qr && t % 10 == 0)
			--qr, t /= 10;
		s = 1;
	} else {
		for(s = 1; y / s; s *= 10);
		for(; s != 1; s /= 10)
			if(y / (s / 10) % 10 && isprefix(y % s, x))
				break;
	}
	//cerr << s << endl;
	ll	t = y / s;
	//cerr << t << endl;
	while(qr && t < Ans)
		t = t * 10 + tmp[qr--];
	//cerr << t << endl;
	return t;
}

void DFS(int i, int cnt)
{
	//printf("%d %d\n", i, cnt);
	if(i > N) {
		//for(int j = 1; j <= cnt; ++j)
		//	printf("%llu%c", Number[j], " \n"[j == cnt]);
		if(cnt > 2) {
			ll	t = Number[cnt - 1] + 1;
			if(isprefix(Number[cnt], t))
				Ans = min(Ans, t);
		} else if(cnt == 2) {
			ll	t = Number[1] + 1;
			//cout << t << ' ' << Number[2] << ' ' << calc(t, Number[2]) << endl;
			//printf("%llu %llu %llu\n", t, Number[2], calc(t, Number[2]));
			Ans = min(Ans, calc(t, Number[2]));
		}
		return;
	}
	Number[cnt] = Number[cnt] * 10 + (S[i] ^ '0');
	if(cnt <= 2 || (cnt > 2 && Number[cnt] <= Number[cnt - 1] + 1))
		DFS(i + 1, cnt);
	Number[cnt + 1] = 0;
	if(i != N && S[i + 1] != '0' && ((cnt > 2 && Number[cnt] == Number[cnt - 1] + 1) || (cnt == 2 && issuffix(Number[1], Number[2] - 1)) || cnt == 1))
		DFS(i + 1, cnt + 1);
	Number[cnt] /= 10;
}

int main()
{
	freopen("number.in", "r", stdin);
	freopen("number.out", "w", stdout);

	cin >> T;
	while(T--) {
		scanf("%s", S + 1);
		N = strlen(S + 1);
		Ans = 0;
		for(char *s = S + 1; *s; ++s)
			Ans = Ans * 10 + (*s ^ '0');
		Number[1] = 0;
		DFS(1, 1);
		printf("%llu\n", Ans);
	}

	return 0;
}
