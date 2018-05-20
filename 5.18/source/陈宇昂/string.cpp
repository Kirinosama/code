#include<bits/stdc++.h>
using namespace std;

int T;
int L[505];

namespace Sub1{
	int N;
	int Ans[505],B[505][25];
	bool A[25],Vis[505];
	
	int Calc(){
		int i=1,j,sum=0;
		for(;i<=N;i=j){
			for(j=i;j<=N&&A[j]==A[i];j++);
			sum+=(j-i)*(j-i+1)/2;
		}
		sum=N*(N+1)/2-sum;
		if(!Ans[sum]){
			Ans[sum]=N;
			for(i=1;i<=N;i++)
				B[sum][i]=A[i];
		}
		//if(N==20)
		//	printf("%d ",sum);
	}
	
	void DFS(int t){
		if(t>N){
			Calc();
			return;
		}
		A[t]=true,DFS(t+1);
		A[t]=false,DFS(t+1);
	}
	
	void Work1(){
		int i,j;
		for(N=1;N<=21;N++)
			DFS(1);
		//puts("");
		for(i=1;i<=T;i++){
			for(j=1;j<=Ans[L[i]];j++)
				printf("%d",B[L[i]][j]);
			puts("");
		}
	}
}
using Sub1::Work1;

int main(){
	freopen("string.in","r",stdin);
	freopen("string.out","w",stdout);
	int i;
	scanf("%d",&T);
	for(i=1;i<=T;i++)
		scanf("%d",&L[i]);
	Work1();
	return 0;
}
