#include <math.h>
#include <time.h>
#include <stdio.h>
#include <iostream>
#include <string.h>
#include <stdlib.h>
#include <algorithm>
using namespace std;
const long long inf=0x3f3f3f3f3f3f3f3fll;
int N,D,A,B,O[222],P[222];
bool G[222],G_[222];
long long F[222];
long long calc(){
	 sort(P+1,P+N+1);
	 memset(F,0x3f,sizeof(F));
	 F[1]=0;
	 for (int i=1;i<=N;i++){
	 	 register long long tmp=inf;
		 for (int j=1;j<=i;j++){
			 tmp=min(tmp,F[j]-(long long)B*P[j]);
		 }
		 F[i+1]=tmp+(long long)B*P[i]+A;
	 }
	 return F[N+1];
}
long long work(){
	 int cnt=2333333/N;
	 for (int i=1;i<=N;i++){
	 	 P[i]=O[i]+(G[i]?D:0);
	 }
	 long long res=calc(),lim=(long long)D*B;
	 long double bas=powl((long double)1.0/lim,(long double)1.0/(cnt));
	 while (cnt--){
	 	   for (int i=1;i<=N;i++){
		   	   G[i]=G_[i];
  		   }
		   int s=rand()%5+1;
		   while (s--){
				 G[rand()%N+1]^=1;
		   }
		   for (int i=1;i<=N;i++){
			   P[i]=O[i]+(G[i]?D:0);
		   }
		   int tmp=calc();
		   if (tmp-res<lim){
			  res=tmp;
		   }
		   else{
				for (int i=1;i<=N;i++){
					G[i]=G_[i];
				}
		   }
		   lim*=bas;
	 }
	 return res;
}
int main(){
	long long ANS=0x3f3f3f3f3f3f3f3fll;
	freopen("point.in","r",stdin);
	freopen("point.out","w",stdout);
	scanf("%d%d%d%d",&N,&D,&A,&B);
	D<<=1;
	for (int i=1;i<=N;i++){
		scanf("%d",&O[i]);
	}
	sort(O+1,O+N+1);
	N=unique(O+1,O+N+1)-O-1;
	for (int i=1;i<=N;i++){
		P[i]=O[i];
	}
	srand((unsigned long long)(new(char)));
	work();
	while (clock()<777){
		  for (int i=1;i<=N;i++){
			  G[i]=rand()&1;
		  }
		  ANS=min(ANS,work());
	}
	printf("%lld",ANS);
	return 0;
}
