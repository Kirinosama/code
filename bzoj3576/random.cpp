#include <iostream>
#include <ctime>
using namespace std;

int main(){
	freopen("bzoj3576.in","w",stdout);
	srand(time(0));
	int T=rand()%99+1;int F=rand()%10+1;
	cout<<T<<' '<<F<<endl;
	while(T--){
		int n=rand()%10+1; printf("%d ",n);
		for(int i=1;i<=n;i++) printf("%d ",rand()%99+1);
		cout<<endl;
	} 
	return 0;
}