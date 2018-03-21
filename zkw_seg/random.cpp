#include <iostream>
#include <ctime>
using namespace std;

int main(){
	freopen("zkw_seg.in","w",stdout);
	srand(time(0));
	int n=rand()%1000000+1;
	int m=rand()%2000000+1;
	cout<<n<<' '<<m<<endl;
	for(int i=1;i<=m;i++){
		int opt=rand()%7;
		if(opt!=2 && opt!=3) printf("%d %d\n",opt+1,rand()%n);
		else printf("%d\n",opt+1);
	}
	return 0;
}