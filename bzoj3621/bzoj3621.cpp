#include <cstdlib>
#include <cstdio>
#include <cstring>
#include <iostream>
#include <algorithm>
#include <cmath>
using namespace std;

#define eps 1e-4
#define ii pair<int,int>
#define INF 0x3f3f3f3f
typedef long long ll;

struct complex{
	double real,imag;
	complex(){real=imag=0.0;}
	complex(double x,double y){real=x,imag=y;}
	void in(){scanf("%lf%lf",&real,&imag);}
	double len(){return real*real+imag*imag;}
	complex operator + (const complex &a)const{
		return complex(real+a.real,imag+a.imag);
	}
	complex operator - (const complex &a)const{
		return complex(real-a.real,imag-a.imag);
	}
	complex operator * (const complex &a)const{
		return complex(real*a.real-imag*a.imag,real*a.imag+imag*a.real);
	}
	complex operator / (const complex &a)const{
		double div=a.real*a.real+a.imag*a.imag;
		return complex((real*a.real+imag*a.imag)/div,(imag*a.real-real*a.imag)/div);
	}
}a[3],b[3],c[3];

void solve(){
	for(int i=0;i<3;i++) a[i].in();
	for(int i=0;i<3;i++) b[i].in();
	for(int i=0;i<3;i++)
		for(int j=0;j<3;j++)
			for(int k=0;k<3;k++)if(i!=j && i!=k && j!=k){
				c[0]=b[i],c[1]=b[j],c[2]=b[k];
				complex K=(c[0]-c[1])/(a[0]-a[1]);
				complex p=(a[0]*K-c[0])/(K-complex(1,0));
				complex a1=(a[2]-p)*K,a2=c[2]-p;
				if(fabs(a1.real-a2.real)<eps && fabs(a1.imag-a2.imag)<eps){
					printf("%.6lf %.6lf\n",p.real,p.imag);
					return ;
				}
			}	
}

int main(){
    freopen("bzoj3621.in","r",stdin);
    int T;scanf("%d",&T);
    while(T--)solve();
    return 0;
}