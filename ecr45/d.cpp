#include <bits/stdc++.h>
using namespace std;

int n,a,b,f[1010][1010];

int main(){
	freopen("input","r",stdin);
	cin>>n>>a>>b;
	if(a!=1 && b!=1){
		cout<<"NO";
		return 0;
	}
	if((n==2) || (n==3)){
		if((max(a,b)!=2) || (min(a,b)!=1)){
			cout<<"NO";return 0;
		}
	}
	int c=a+b-1;
	for(int i=c;i<n;i++)
		f[i][i+1]=f[i+1][i]=1;
	if(a==1){
		for(int i=1;i<=n;i++)
			for(int j=1;j<=n;j++)if(i!=j)
				f[i][j]^=1;
	}
	printf("YES");
	for(int i=1;i<=n;i++){
		printf("\n");
		for(int j=1;j<=n;j++)printf("%d",f[i][j]);
	}
	return 0;
}
