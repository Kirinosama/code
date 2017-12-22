#include <cstdlib>
#include <cstdio>
#include <cstring>
#include <iostream>
#include <algorithm>
using namespace std;

#define MAXN 110

int n;
double a[MAXN][MAXN],ans[MAXN];

void swap_line(int x,int y){
	for(int i=1;i<=n+1;i++)
		swap(a[x][i],a[y][i]);
}

void gauss(){
	for(int i=1;i<=n;i++){
		for(int j=i;j<=n;j++)
			if(a[j][i]!=0){
				swap_line(i,j);
				break;
			}
		if(a[i][i]==0) return;
		double mul=1.0/a[i][i];
		for(int j=1;j<=n+1;j++)
			a[i][j]*=mul;
		for(int j=i+1;j<=n;j++){
			double mul=-a[j][i];
			for(int k=1;k<=n+1;k++)
				a[j][k]+=a[i][k]*mul;
		}
	}
}

bool judge(){
	for(int i=1;i<=n;i++)
		for(int j=i;j<=n;j++)
			if(a[i][j]==0) return false;
	return true;
}

void get_ans(){
	for(int i=n;i>=1;i--){
		ans[i]=a[i][n+1];
		for(int j=i-1;j>=1;j--)
			a[j][n+1]-=ans[i]*a[j][i];
	}
	for(int i=1;i<=n;i++) printf("%.2f\n",ans[i]);
}

int main(){
	freopen("input","r",stdin);
	cin>>n;
	for(int i=1;i<=n;i++)
		for(int j=1;j<=n+1;j++)
			scanf("%lf",&a[i][j]);
	gauss();
	if(!judge()) cout<<"No Solution";
	else get_ans();
	return 0;
}