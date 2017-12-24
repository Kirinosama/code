#include <cstdlib>
#include <cstdio>
#include <cstring>
#include <iostream>
#include <algorithm>
using namespace std;

char a[20][20];
int x,y;

void full(int x,int y){
	bool flag=false;
	for(int i=(x-1)*3+1;i<=x*3;i++)
		for(int j=(y-1)*3+1;j<=y*3;j++)
			if(a[i][j]=='.'){
				a[i][j]='!';
				flag=true;
			}
	if(!flag)
		for(int i=1;i<=9;i++)
			for(int j=1;j<=9;j++)
				if(a[i][j]=='.')
					a[i][j]='!';
	for(int i=1;i<=9;i++){
		for(int j=1;j<=9;j++){
			printf("%c",a[i][j]);
			if(j==3 || j==6) printf(" ");
		}
		cout<<endl;
		if(i==3 || i==6) cout<<endl;
	}			
}

int main(){
	freopen("input","r",stdin);
	for(int i=1;i<=9;i++){
		for(int j=1;j<=9;j++){
			scanf("%c",&a[i][j]);
			if(j%3==0) getchar();
		}
		if(i==3 || i==6) getchar();
	}
	scanf("%d %d",&x,&y);
	x=x%3,y=y%3;
	if(!x) x=3;
	if(!y) y=3;
	full(x,y);
	return 0;
}
