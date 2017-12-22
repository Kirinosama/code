#include <ctime>
#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <iostream>
using namespace std;

#define MAXN 200
#define MAXM 10000
int a[200010],b[200010],tot;

int main(){
	freopen("bzoj1095.in","w",stdout);
	srand(time(0));
	int n=rand()%MAXN+1;cout<<n<<endl;
	for(int i=1;i<=n;i++)
		a[i]=i;
	for(int i=1;i<=n;i++){
		random_shuffle(b+1,b+1+tot);
		random_shuffle(a+1+tot,a+1+n);
		if(i==1) b[++tot]=a[1];
		else{
			cout<<a[tot+1]<<' '<<b[1]<<endl;
			b[tot+1]=a[tot+1];tot++;
		}
	}
	int m=rand()%MAXM+1;cout<<m<<endl;
	for(int i=1;i<=m;i++){
		if(rand()%10<=2)
			printf("G\n");
		else
			printf("C %d\n",rand()%n+1);
	}
	printf("1\nG");
}