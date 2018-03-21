#include <cstdlib>
#include <cstdio>
#include <cstring>
#include <iostream>
#include <algorithm>
#include <ctime>
using namespace std;

#define MAXN 200010
#define MAXM 1000010
#define ii pair<int,int>
#define INF 0x3f3f3f3f
typedef long long ll;

int a[MAXN];

int Rand(int l,int r){
	int add=rand()%(r-l+1);
	return l+add;
}

int main(){
	freopen("bzoj4316.in","w",stdout);
	srand(time(0));
	int n=rand()%50000+1;
	int m=n+rand()%50+1;
	cout<<n<<' '<<m<<endl;
	int l=2,r=n;
	for(int i=1;i<=m-n+1;i++){
		int rt=rand()%(l-1)+1;
		int R=i==m-n+1?r:Rand(l,2*n-1-m+i);
		printf("%d %d\n",rt,l);
		for(int i=l;i<R;i++) printf("%d %d\n",i,i+1);
		printf("%d %d\n",R,rt);
		l=R+1;
	}
	return 0;
}