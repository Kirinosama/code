#include <iostream>
#include <ctime>
using namespace std;

int main(){
	freopen("bzoj3083.in","w",stdout);
	srand(time(0));
	int n=rand()%100000+1,m=rand()%100000+1;cout<<n<<' '<<m<<endl;
	for(int i=1;i<n;i++) printf("%d %d\n",i+1,rand()%i+1);
	for(int i=1;i<=n;i++) printf("%d ",rand()%2147483647+1);cout<<endl;
	int rt=rand()%n+1;cout<<rt<<endl;
	for(int i=1;i<=m;i++){
		int c=rand()%3;
		if(!c){
			printf("1 %d\n",rand()%n+1);
		}else if(c==1){
			printf("2 %d %d %d\n",rand()%n+1,rand()%n+1,rand()%2147483647+1);
		}else{
			printf("3 %d\n",rand()%n+1);
		}
	}
}