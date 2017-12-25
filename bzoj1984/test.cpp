#include <cstdlib>
#include <cstdio>
#include <cstring>
#include <iostream>
#include <ctime>
using namespace std;

#define MAXN 10
#define MAXM 30

int book[100010],cnt;

int main(){
	freopen("bzoj1984.in","w",stdout);
	srand(time(0));
	int n=rand()%MAXN+2;
	cout<<n<<endl;
	book[++cnt]=1;
	for(int i=1;i<n;i++){
		int u=book[rand()%cnt+1];
		int v=i+1;
		book[++cnt]=v;
		printf("%d %d %d\n",u,v,rand()%100);
	}
	int m=rand()%MAXM+1;
	for(int i=1;i<=m;i++){
		int c=rand()%4;
		if(c==0)
			printf("Change %d %d\n",rand()%(n-1)+1,rand()%100);
		if(c==1)
			printf("Cover %d %d %d\n",rand()%n+1,rand()%n+1,rand()%100);
		if(c==2)
			printf("Add %d %d %d\n",rand()%n+1,rand()%n+1,rand()%100);
		if(c==3){
			int x=rand()%n+1,y=rand()%n+1;
			while(x==y) y=rand()%n+1;
			printf("Max %d %d\n",x,y);
		}
	}
	printf("Stop");
	return 0;
}
