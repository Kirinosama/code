#include <iostream>
using namespace std;

int main(){
	freopen("bzoj3626.in","r",stdin);
	double min=9999999;int pos=0;
	for(int i=1;i<=10000;i++){
		double res=(double)(i*i+8)/(double)(i+1);
		if(res<min){
			min=res,pos=i;
		}
	}
	printf("%d %lf",pos,min);
	return 0;
}