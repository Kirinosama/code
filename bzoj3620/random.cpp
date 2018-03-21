#include <iostream>
#include <ctime>
using namespace std;

int main(){
	freopen("bzoj3620.in","w",stdout);
	srand(time(0));
	int n=rand()%1500+1;
	for(int i=1;i<=n;i++){
		printf("%c",rand()%('z'-'a'+1)+'a');
	}
	printf("\n%d",rand()%100+1);
	return 0;
}