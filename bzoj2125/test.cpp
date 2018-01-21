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
	freopen("bzoj2125.in","w",stdout);
	srand(time(0));
	int n=rand()%10000+1;
	int m=n+rand()%30+1;
	int q=rand()%10000+1;
	cout<<n<<' '<<m<<' '<<q<<endl;
	int l=2,r=n;
	for(int i=1;i<=m-n+1;i++){
		int rt=rand()%(l-1)+1;
		int R=i==m-n+1?r:Rand(l,2*n-1-m+i);
		printf("%d %d %d\n",rt,l,rand()%300+1);
		for(int i=l;i<R;i++) printf("%d %d %d\n",i,i+1,rand()%300+1);
		printf("%d %d %d\n",R,rt,rand()%300+1);
		l=R+1;
	}
	for(int i=1;i<=q;i++){
		int x=rand()%n+1;
		int y=rand()%n+1;
		while(x==y) y=rand()%n+1;
		printf("%d %d\n",x,y);
	}
	return 0;
}