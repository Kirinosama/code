#include <cstdlib>
#include <cstdio>
#include <cstring>
#include <iostream>
#include <algorithm>
using namespace std;

int v1,v2,v3,v4;

bool judge(int x,int y,int z){
	if(x>y && y>z){
		if(v4<=z && 2*v4>=z && 2*v4<x && 2*v4<y)
			return true;
	}
	return false;
}

int main(){
	freopen("input","r",stdin);
	scanf("%d %d %d %d",&v1,&v2,&v3,&v4);
	for(int i=v1;i<=2*v1;i++)
		for(int j=v2;j<=2*v2;j++)
			for(int k=v3;k<=2*v3;k++)
				if(judge(i,j,k)){
					printf("%d %d %d",i,j,k);
					return 0;
				}
	printf("-1");
	return 0;
}