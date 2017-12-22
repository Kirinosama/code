#include <cstdlib>
#include <cstdio>
#include <cstring>
#include <iostream>
#include <algorithm>
#include <ctime>
using namespace std;

int main(){
	freopen("bzoj1789.in","w",stdout);
	srand(time(0));
	for(int i=1;i<=3;i++){
		int n=rand()%50;printf("%d ",n);
		for(int i=1;i<=n;i++)
			printf("%c",'A'+rand()%26);
		printf("\n");
	}
	return 0;
}