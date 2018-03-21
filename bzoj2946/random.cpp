#include <iostream>
#include <ctime>

using namespace std;

int Rand(int l,int r){
	int add=rand()%(r-l+1);
	return l+add;
}

int main(){
	freopen("bzoj2946.in","w",stdout);
	srand(time(0));
	int n=rand()%5+1;cout<<n<<endl;
	for(int i=1;i<=n;i++){
		int len=rand()%2000+1;
		for(int j=1;j<=len;j++) printf("%c",Rand('a','z'));
		cout<<endl;
	}
	return 0;
}