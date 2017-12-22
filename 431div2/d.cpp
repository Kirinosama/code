#include <cstdlib>
#include <cstdio>
#include <cstring>
#include <iostream>
#include <algorithm>
#include <map>
#include <set>
#include <queue>
#include <vector>
#include <cmath>
using namespace std;

const double eps=1e-8;
const int INF=0x3f3f3f3f;
#define MAXN 100010

int father[MAXN],f[MAXN],a[MAXN],n;

int solve(int x)
{
	if(x==1) return 0;
	if(f[x]) return f[x];
	int res=INF;
	for(int i=1;i<x;i++)
		res=min(res,i*(x-i)+solve(i)+solve(x-i));
	return f[x]=res;
}

int main()
{
	for(int i=1;i<=50;i++)
		printf("%d\n",solve(i));
	return 0;
}
