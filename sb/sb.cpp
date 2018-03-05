#include <cstdlib>
#include <cstdio>
#include <cstring>
#include <iostream>
#include <algorithm>
#include <cmath>
using namespace std;

#define kind(x) ((x-1)/4)
#define ii pair<int,int>
#define INF 0x3f3f3f3f
typedef long long ll;

double Maxp,Minp;

int main(){
    freopen("sb.in","r",stdin);
    double Min=INF,Max=-INF;
   	for(double x=M_PI/6.0+0.01;x<=M_PI/2.0;x+=0.001){
   		if(3.0/cos(x)>10) continue;
   		if(3.0/cos(0.666667*M_PI-x)>6) continue;
   		double res=tan(x)+tan(0.6666667*M_PI-x);
   		if(res>Max){
   			Max=res;Maxp=x;
   		}
   		if(res<Min){
   			Min=res;Minp=x;
   		}
   	}
   	printf("%lf:%lf\n",Minp/M_PI*180.0,Min);
   	printf("%lf:%lf\n",Maxp/M_PI*180.0,Max);	
    return 0;
}