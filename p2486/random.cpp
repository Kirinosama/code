#include <iostream>
#include <ctime>
using namespace std;

int main(){
	freopen("p2486.in","w",stdout);
	srand(time(0));
	int n=rand()%100000+1;
	int m=rand()%100000+1;
	cout<<n<<' '<<m<<endl;
	for(int i=1;i<=n;i++) printf("%d ",rand()%3+1);
		cout<<endl;
	for(int i=1;i<n;i++)
		printf("%d %d\n",rand()%i+1,i+1);
	for(int i=1;i<=m;i++){
		int k=rand()%2;
		if(!k) printf("Q %d %d\n",rand()%n+1,rand()%n+1);
		else printf("C %d %d %d\n",rand()%n+1,rand()%n+1,rand()%10+1);
	}
	return 0;
}