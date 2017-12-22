#include <cstdlib>
#include <cstring>
#include <cstdio>
#include <ctime>
#include <iostream>
using namespace std;

#define N 500000

int main(){
	srand(time(0));
	freopen("bzoj1941.in","w",stdout);
	int n=rand()%N+1;printf("%d\n",n);
	for(int i=1;i<=n;i++){
		int x=rand()%100000001;
		int y=rand()%100000001;
		printf("%d %d\n",x,y);
	}
	return 0;
}