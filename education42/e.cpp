#include <cstdlib>
#include <cstdio>
#include <iostream>
using namespace std;
const int N = 1e6 + 200;
string s, t[200];
struct SuffixArray
{
	int n, sa[N], buf[2][N], * rk, * x;
	SuffixArray(): rk(buf[0]), x(buf[1]) {}
	void build(int _n)
	{
		static int c[N];
		n = _n;
		rep (i, 0, n) ++c[int(s[i])];
		rep (i, 1, 1<<(8*sizeof(char))) c[i] += c[i-1];
		per (i, n-1, 0) sa[--c[int(s[i])]] = i;
		int m = rk[sa[0]] = 0;
		rep (i, 1, n) rk[sa[i]] = m += s[sa[i-1]] != s[sa[i]];
		for (int k = 1; ++m < n; swap(x, rk), k <<= 1)
		{
			int* p = x;
			rep (i, n-k, n) *p++ = i;
			rep (i, 0, n) if (sa[i] >= k) *p++ = sa[i]-k;
			fill_n(c, m, 0);
			rep (i, 0, n) ++c[rk[i]];
			rep (i, 1, m) c[i] += c[i-1];
			per (i, n-1, 0) sa[--c[rk[x[i]]]] = x[i];
			m = x[sa[0]] = 0;
			rep (i, 1, n) x[sa[i]] = m += rk[sa[i]] != rk[sa[i-1]] || rk[sa[i]+k] != rk[sa[i-1]+k];
		}
	}
	int query(const string& t)
	{
		int l = -1, r = n, len = t.size();
		while (r-l > 1)
		{
			int m = (l+r)/2;
			if (s.substr(sa[m], len) < t) l = m;
			else r = m;
		}
		int p = r;
		l = p-1, r = n;
		while (r-l > 1)
		{
			int m = (l+r)/2;
			if (s.substr(sa[m], len) <= t) l = m;
			else r = m;
		}
		return r - p;
	}
} sa;
int main()
{
	ios::sync_with_stdio(false);
	int n;
	cin >> n;
	rep (i, 0, n)
	{
		cin >> t[i];
		s += t[i] + ' ';
	}
	s[s.size()-1] = '\0';
	sa.build(s.size());
	rep (i, 0, n)
		cout << sa.query(t[i]) << endl;
	return 0;
}
