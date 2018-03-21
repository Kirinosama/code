#include <iostream>
#include <ctime>
using namespace std;

int main(){
	freopen("bzoj2962.in","w",stdout);
	srand(time(0));
	int n=rand()%100+1,m=rand()%100+1;
	cout<<n<<' '<<m<<endl;
	for(int i=1;i<=n;i++) printf("%d ",rand()%2000000001-1000000000);
	for(int i=1;i<=m;i++){
		int c=rand()%3;
		int x=rand()%n+1,y=rand()%n+1;
		if(x>y) swap(x,y);
		if(!c){
			printf("I %d %d %d\n",x,y,rand()%2000000001-1000000000);
		}else if(c==1){
			printf("R %d %d\n",x,y);
		}else{
			printf("Q %d %d %d\n",x,y,rand()%(min(20,y-x+1))+1);
		}
	}
	return 0;
}