#include <cstdlib>
#include <cstdio>
#include <cstring>
#include <iostream>
#include <ctime>
using namespace std;

int a[10010],cnt,zhi[10010];
int book[10010];

int main(){
	freopen("bzoj3994.in","w",stdout);
	srand(time(0));
	int n=1e9;
	for(int i=2;i<=8000;i++){
		if(!book[i]){
			zhi[++cnt]=i;
			for(int j=i*2;j<=8000;j+=i) book[j]=1;
		}
	}
	int m=zhi[cnt];
	int x=rand()%(m-1)+1;
	int s=m;
	for(int i=0;i<m;i++) a[i]=i;
	random_shuffle(a,a+m);
	printf("%d %d %d %d\n",n,m,x,s);
	for(int i=0;i<s;i++) printf("%d ",a[i]);
	return 0;
}