#include <stdio.h>
#include <iostream>
#include <string.h>
#include <stdlib.h>
#include <algorithm>
using namespace std;
int O,N,M,ANS[233333],S[1111111],P[1111111],T[23];
void _1(int x){
	 int s=0,x_=x;
	 if (x!=0){
	 	while (x){
			  T[++s]=x%10;
			  x/=10;
		}
	 }
	 else{
		  T[++s]=0;
	 }
	 for (int i=0;i!=s;i++){
	 	 M++;
		 S[M]=T[s-i];
		 P[M]=x_;
	 }
}
int _2(int x,int y){
	int res=0;
	for (int i=0;i!=y;i++){
		res=res*10+S[x+i];
	}
	return res;
}
void prep(){
	for (int i=1;i<=200000;i++){
		_1(i);
		ANS[i]=i;
	}
	for (int i=1;i<=M;i++){
		for (int j=2;j<=6&&i+j<=M;j++){
			int p=_2(i,j);
			ANS[p]=min(ANS[p],P[i+j-1]);
		}
	}
}
int main(){
	freopen("number.in","r",stdin);
	freopen("number.out","w",stdout);
	prep();
	scanf("%d",&O);
	for (int o=1;o<=O;o++){
		scanf("%d",&N);
		printf("%d\n",ANS[N]);
	}
	return 0;
}
