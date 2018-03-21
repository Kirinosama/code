#include <iostream>
using namespace std;

int book[200000000];

int main(){
	freopen("out3","w",stdout);
	for(int i=2;i<=1e8;i++)if(!book[i]){
		cout<<i<<endl;
		for(long long j=(long long)i*2;j<=2e8;j+=i)
			book[j]=1;
	}
	for(int i=2e8;i>=1e8;i--)if(!book[i]){
		printf("%d",i);return 0;
	}
}