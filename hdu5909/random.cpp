#include <bits/stdc++.h>
using namespace std;

int main(){
	freopen("input","w",stdout);
	srand(time(0));
	int T=10;
	cout<<T<<endl;
	for(int i=1;i<=T;i++){
		int n=1000,m=1024;
		cout<<n<<' '<<m<<endl;
		for(int j=1;j<=n;j++)printf("%d ",rand()%m);
		cout<<endl;
		for(int j=1;j<n;j++)printf("%d %d\n",j+1,rand()%j+1);
	}
	return 0;
}
