#include <stdio.h>
#include <iostream>
#include <string.h>
#include <stdlib.h>
#include <algorithm>
using namespace std;
int O,N,A[11];
int main(){
	freopen("string.in","r",stdin);
	freopen("string.out","w",stdout);
	scanf("%d",&O);
	for (int o=1;o<=O;o++){
		scanf("%d",&N);
		if (N==1){
	   	   printf("01\n");continue;
		}
		if (N==2){
	   	   printf("011\n");continue;
		}
		if (N==3){
	   	   printf("010\n");continue;
		}
		if (N==4){
	   	   printf("0011\n");continue;
		}
		if (N==5){
	   	   printf("0100\n");continue;
		}
		if (N==6){
	   	   printf("1010\n");continue;
		}
		if (N==7){
		   printf("00010\n");continue;
		}
		if (N==8){
		   printf("00110\n");continue;
		}
		if (N==9){
		   printf("01011\n");continue;
		}
		if (N==10){
		   printf("01010\n");continue;
		}
		if (N==11){
		   printf("000110\n");continue;
		}
		if (N<=15){
		while (1){
			  for (int i=1;i<=6;i++)A[i]=rand()&1;

			  int s=0;
			  for (int i=1;i<=6;i++){
				  for (int j=i+1;j<=6;j++){
					  bool o[2];
					  o[0]=false;
					  o[1]=false;
					  for (int k=i;k<=j;k++){
						  o[A[k]]=true;
					  }
					  if (o[0]&&o[1]){
						 s++;
					  }
				  }
			  }
			  if (s==N){
				 for (int i=1;i<=6;i++){
					 printf("%d",A[i]);
				 }
				 printf("\n");break;
			  }
		}
		}
		else{
		while (1){
			  for (int i=1;i<=7;i++)A[i]=rand()&1;
			  
			  int s=0;
			  for (int i=1;i<=7;i++){
				  for (int j=i+1;j<=7;j++){
					  bool o[2];
					  o[0]=false;
					  o[1]=false;
					  for (int k=i;k<=j;k++){
						  o[A[k]]=true;
					  }
					  if (o[0]&&o[1]){
						 s++;
					  }
				  }
			  }
			  if (s==N){
				 for (int i=1;i<=7;i++){
					 printf("%d",A[i]);
				 }
				 printf("\n");break;
			  }
		}
		}
	}
	return 0;
}
