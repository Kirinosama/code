#include <bits/stdc++.h>
using namespace std;

int n,m,a[100010],b[100010],c[100010];

void fwt(int *A,int size,bool flag){
	for(int step=2;step<=size;step<<=1){
		int gap=step>>1;
		for(int i=0;i<size;i+=step){
			for(int j=i;j<i+gap;j++){
				int t0=A[j],t1=A[j+gap];
				if(flag) A[j+gap]=t0+t1;
				else A[j+gap]=t1-t0;
			}
		}
	}
}

int main(){
	freopen("input","r",stdin);
	cin>>n>>m;
	for(int i=0;i<n;i++)scanf("%d",&a[i]);
	for(int j=0;j<m;j++)scanf("%d",&b[j]);
	for(int i=0;i<n;i++)
		for(int j=0;j<m;j++)
			c[i|j]+=a[i]*b[j];
	for(int i=0;i<max(n,m);i++)printf("%d ",c[i]);
	cout<<endl;
	int size=1;
	while(size<max(n,m)) size<<=1;
	fwt(a,size,true);fwt(b,size,true);
	for(int i=0;i<size;i++)a[i]*=b[i];
	fwt(a,size,false);
	for(int i=0;i<max(n,m);i++)printf("%d ",a[i]);
	return 0;
}
