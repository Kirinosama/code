#include <cstdlib>
#include <cstdio>
#include <cstring>
#include <iostream>
#include <algorithm>
#include <cmath>
using namespace std;

//高斯消元模版

#define MAXN 30
const double eps=1e-8;	
// #85a7a5
int n;
double a[MAXN][MAXN],s[MAXN][MAXN],ans[MAXN];

void swap_line(int p,int q){
	for(int i=1;i<=n+1;i++)
		swap(s[p][i],s[q][i]);
}

void Gaosi(){
	for(int i=1;i<=n;i++){
		for(int j=i;j<=n;j++)
			if(fabs(s[j][i])>eps){
				swap_line(i,j);
				break;
			}
		for(int j=i+1;j<=n;j++){
			double mul=s[j][i]/s[i][i];
			for(int k=i;k<=n+1;k++)
				s[j][k]-=mul*s[i][k];
		}
	}
	for(int i=n;i>=1;i--){
		ans[i]=s[i][n+1]/s[i][i];
		for(int j=n-1;j>=1;j--)
			s[j][n+1]-=s[j][i]*ans[i];
	}
}

void print(){
	// for(int i=1;i<=n;i++){
	// 	for(int j=1;j<=n+1;j++)
	// 		printf("%lf ",s[i][j]);
	// 	cout<<endl;
	// }
	for(int i=1;i<=n;i++){
		printf("%.3f",ans[i]);
		if(i!=n) cout<<' ';
	}
}

int main()
{
    freopen("bzoj1013.in","r",stdin);
    cin>>n;
    for(int i=1;i<=n+1;i++){
    	for(int j=1;j<=n;j++)
    		scanf("%lf",&a[i][j]);
    	for(int j=1;j<=n;j++){
    		s[i-1][j]=2.0*(a[i][j]-a[i-1][j]);
    		s[i-1][n+1]+=a[i][j]*a[i][j]-a[i-1][j]*a[i-1][j];
    	}
    }
    Gaosi();
    print();
    return 0;
}
