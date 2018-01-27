#include <iostream>
#include <ctime>
using namespace std;

int main(){
	freopen("bzoj2875.in","w",stdout);
	srand(time(0));
	int n=rand()+1;
	int m=rand()+1;
	int a=rand(),c=rand(),x0=rand();
	int g=rand()%100000000+1;
	printf("%d %d %d %d %d %d",m,a,c,x0,n,g);
	return 0;
}