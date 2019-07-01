#include <cstdlib>
#include <cstdio>
#include <iostream>
#include <cmath>
using namespace std;

#define INF 0x3f3f3f3f
#define ii pair<int,int>
typedef long long ll;

double a,b;
double c;

int main(){
	freopen("123.in","r",stdin);
	for(double i=0.00001;i<=0.20000;i+=(double)0.00001){
		b=(double)sqrt(0.04-i*i);
		double ans=0.6*i-0.16+0.8*b;
		if(fabs(ans-0)<0.00001) cout<<0.7*i<<endl;
	}
	return 0;
}
