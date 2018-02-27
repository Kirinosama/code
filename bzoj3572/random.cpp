#include <iostream>
#include <algorithm>
#include <ctime>
using namespace std;

int a[300010];

int main(){
	freopen("bzoj3572.in","w",stdout);
	srand(time(0));
	int n=rand()%3000+1;cout<<n<<endl;
	for(int i=1;i<n;i++)printf("%d %d\n",rand()%i+1,i+1);
	for(int i=1;i<=n;i++)a[i]=i;
	int q=rand()%1000+1;cout<<q<<endl;
	while(q--){
		int len=rand()%n+1;cout<<len<<endl;
		random_shuffle(a+1,a+1+len);
		for(int i=1;i<=len;i++) printf("%d ",a[i]);
		cout<<endl;
	}
	return 0;
}