#include <cstdlib>
#include <cstdio>
#include <cstring>
#include <iostream>
#include <algorithm>
#include <ctime>
using namespace std;

#define MOD 51061
#define ls son[x][0]
#define rs son[x][1]
#define MAXN 100010
#define ii pair<int,int>
#define INF 0x3f3f3f3f
typedef long long ll;

ii E[MAXN];

int main(){
	freopen("bzoj2631.in","w",stdout);
	srand(time(0));
	int n=rand()%100000+1,q=rand()%100000+1;
	printf("%d %d\n",n,q);
	for(int i=2;i<=n;i++){
		int x=rand()%(i-1)+1,y=i;
		E[i]=ii(x,y);
		printf("%d %d\n",x,y);
	}
	for(int i=1;i<=q;i++){
		int t=rand()%4;
		if(t==0)
			printf("+ %d %d %d\n",rand()%n+1,rand()%n+1,rand()%10001);
		if(t==1)
			printf("* %d %d %d\n",rand()%n+1,rand()%n+1,rand()%10001);
		if(t==2)
			printf("/ %d %d\n",rand()%n+1,rand()%n+1);
		if(t==3){
			int u1=E[n].first,v1=E[n].second;
			printf("- %d %d %d %d\n",u1,v1,u1,v1);
		}
	}
	return 0;
}