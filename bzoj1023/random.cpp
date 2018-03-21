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
	freopen("bzoj1023.in","w",stdout);
	srand(time(0));
	for(int i=1;i<=rand()%10+1;i++){
		int n=Rand(20,1000);
		int m=Rand(n+10,min(n+30,2*n-9));
		cout<<n<<' '<<m-n+1<<endl;
		int l=2,r=n;
		for(int i=1;i<=m-n+1;i++){
			int rt=rand()%(l-1)+1;
			int R=i==m-n+1?r:Rand(l,2*n-1-m+i);
			printf("%d %d ",R-l+3,rt);
			for(int i=l;i<=R;i++) printf("%d ",i);
			printf("%d\n",rt);
			l=R+1;
		}
	}
	return 0;
}