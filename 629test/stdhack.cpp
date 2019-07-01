#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <cmath>
#include <algorithm>

using namespace std;

const int MAXN=210000;
const int Shift=100001;
const int INF=10000001;

int n;
int C[510];

int f[2][MAXN];

int main()
{
	//freopen("hack.in","r",stdin);
	//freopen("hack.out","w",stdout);

	scanf("%d",&n);
	for (int i=1;i<=n;++i)
		 scanf("%d",&C[i]);

	int Cur=0,Sum=0;
	f[Cur][0]=0;
	for (int i=1;i<=n;++i)
	{
		for (int j=-Sum-C[i];j<=Sum+C[i];++j) f[Cur^1][j+Shift]=-INF;
		for (int j=-Sum;j<=Sum;++j)
		{
			f[Cur^1][j+Shift+C[i]]=max(f[Cur^1][j+Shift+C[i]],f[Cur][j+Shift]+C[i]);
			f[Cur^1][j+Shift-C[i]]=max(f[Cur^1][j+Shift-C[i]],f[Cur][j+Shift]+C[i]);
			f[Cur^1][j+Shift]=max(f[Cur^1][j+Shift],f[Cur][j+Shift]);
		}
		Cur^=1;
		Sum+=C[i];
	}
	printf("%d\n",(Sum-f[Cur][Shift])+f[Cur][Shift]/2);	

	return 0;
}

