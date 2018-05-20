#include<bits/stdc++.h>
using namespace std;

typedef long long LL;

int N,M,D,A,B;
int X[155],X2[155];
LL Ans=1ll<<60,F[155];

namespace Sub1{
	bool Tag[25];

	LL Calc(){
		int i,j;
		for(i=1;i<=N;i++)
			if(Tag[i])
				X2[i]=X[i]+D;
			else X2[i]=X[i]-D;
		sort(X2+1,X2+N+1);
		M=unique(X2+1,X2+N+1)-X2-1;
		for(i=1;i<=M;i++){
			F[i]=1ll<<60;
			for(j=1;j<=i;j++)
				F[i]=min(F[i],F[j-1]+A+1ll*B*(X2[i]-X2[j]));
		}
		return F[M];
	}
	
	void DFS(int t){
		if(t>N){
			Ans=min(Ans,Calc());
			return;
		}
		Tag[t]=true,DFS(t+1);
		Tag[t]=false,DFS(t+1);
	}
	
	void Work1(){
		DFS(1);
		printf("%lld\n",Ans);
	}
}
using Sub1::Work1;

namespace Sub2{
	bool Vis[155],Tag[155],Tag2[155];
	
	LL Calc(){
		int i,j;
		sort(X2+1,X2+N+1);
		M=unique(X2+1,X2+N+1)-X2-1;
		for(i=1;i<=M;i++){
			F[i]=1ll<<60;
			for(j=1;j<=i;j++)
				F[i]=min(F[i],F[j-1]+A+1ll*B*(X2[i]-X2[j]));
		}
		return F[M];
	}
	
	LL Calc2(){
		int i,j;
		for(i=1;i<=N;i++)
			if(Tag[i])
				X2[i]=X[i]+D;
			else X2[i]=X[i]-D;
		sort(X2+1,X2+N+1);
		M=unique(X2+1,X2+N+1)-X2-1;
		for(i=1;i<=M;i++){
			F[i]=1ll<<60;
			for(j=1;j<=i;j++)
				F[i]=min(F[i],F[j-1]+A+1ll*B*(X2[i]-X2[j]));
		}
		return F[M];
	}
	
	LL SA(){
		int i,k;
		LL ans=1ll<<60;
		double t=30000;
		for(i=1;i<=N;i++)
			Tag[i]=rand()%2;
		ans=Calc2();
		for(;t>1e-3;t*=0.97){
			memset(Vis,false,sizeof(Vis));
			for(i=1;i<=N;i++)
				Tag2[i]=Tag[i];
			for(k=1;k<=5;k++){
				int x=rand()%N+1;
				while(Vis[x])
					x=rand()%N+1;
				Tag[x]^=1;
				Vis[x]=true;
			}
			LL x=Calc2();
			if(x<=ans)
				ans=x;
			else for(i=1;i<=N;i++)
				Tag[i]=Tag2[i];
		}
		return ans;
	}
	
	void Work2(){
		int i,j,k,t;
		srand(time(0));
		for(i=1;i<N;i++){
			for(j=1;j<=i;j++)
				X2[i]=X[i]+D;
			for(j=i+1;j<=N;j++)
				X2[i]=X[i]-D;
			Ans=min(Ans,Calc());
			for(j=1;j<=8;j++){
				memset(Vis,false,sizeof(Vis));
				t=rand()%10+5;
				for(k=1;k<=t;k++){
					int x=rand()%N+1;
					while(Vis[x])
						x=rand()%N+1;
					if(x<=i)
						X2[x]=X[x]-D;
					else X2[x]=X[x]+D;
					Vis[x]=true;
				}
				Ans=min(Ans,Calc());
			}
		}
		printf("%lld\n",min(Ans,SA()));
	}
}
using Sub2::Work2;

int main(){
	freopen("point.in","r",stdin);
	freopen("point.out","w",stdout);
	int i;
	scanf("%d%d%d%d",&N,&D,&A,&B);
	for(i=1;i<=N;i++)
		scanf("%d",&X[i]);
	sort(X+1,X+N+1);
	if(N<=20)
		Work1();
	else Work2();
	return 0;
}
