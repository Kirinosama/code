#include <cstdlib>
#include <cstdio>
#include <cstring>
#include <iostream>
#include <ctime>
using namespace std;

int a[310],cnt,zhi[300];
int book[310];

int main(){
	freopen("bzoj3994.in","w",stdout);
	srand(time(0));
	int n=rand()%20+1;
	for(int i=2;i<=100;i++){
		if(!book[i]){
			zhi[++cnt]=i;
			for(int j=i*2;j<=100;j+=i) book[j]=1;
		}
	}
	int m=zhi[rand()%cnt+1];
	int x=rand()%(m-1)+1;
	int s=rand()%m+1;
	for(int i=0;i<m;i++) a[i]=i;
	random_shuffle(a,a+m);
	printf("%d %d %d %d\n",n,m,x,s);
	for(int i=0;i<s;i++) printf("%d ",a[i]);
	return 0;
}