#include <cstdlib>
#include <cstring>
#include <cstdio>
#include <ctime>
#include <iostream>
using namespace std;

#define N 10000

char a[100010];

int main(){
	srand(time(0));
	freopen("bzoj3230.in","w",stdout);
	int n=rand()%N+1;int m=rand()%N+1;
	cout<<n<<' '<<m<<endl;
	for(int i=1;i<=n;i++){
		a[i]=rand()%26+'a';
		cout<<a[i];
	}
	cout<<endl;
	for(int i=1;i<=m;i++){
		int x=rand()%N+1,y=rand()%N+1;
		if(x>y) swap(x,y);
		printf("%d %d\n",x,y);
	}
	return 0;
}