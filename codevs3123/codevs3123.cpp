#include <cstdlib>
#include <cstdio>
#include <cstring>
#include <iostream>
#include <algorithm>
#include <cmath>
using namespace std;

#define MAXN 400010
#define ii pair<int,int>
#define INF 0x3f3f3f3f
typedef long long ll;

string s1,s2;
int ans[MAXN];
int rightmost;

struct complex{
	double real,imag;
	complex(){real=imag=0;}
	complex(double x){real=x,imag=0;}
	complex(double x,double y){real=x,imag=y;}
	complex operator +(const complex &a)const{
		return complex(real+a.real,imag+a.imag);
	}
	complex operator *(const complex &a)const{
		return complex(real*a.real-imag*a.imag,imag*a.real+real*a.imag);
	}
	complex operator -(const complex &a)const{
		return complex(real-a.real,imag-a.imag);
	}
}u[MAXN],can1[MAXN],can2[MAXN],can3[MAXN];

int lowbit(int x){
	return x&-x;
}

int reverse(int x,int size){
	int ans=0;
	for(int i=x;i;i-=lowbit(i))
		ans|=size/2/lowbit(i);
	return ans;
}

void fft(complex *A,int size,bool type){
	for(int i=0;i<size;i++){
		int a=reverse(i,size);
		if(i<a) swap(A[i],A[a]);
	}
	for(int i=0;i<size;i++)
		u[i]=complex(cos((type ? 2.0 : -2.0)*M_PI*(double)i/(double)size),sin((type ? 2.0 : -2.0)*M_PI*(double)i/(double)size));
	for(int step=2;step<=size;step<<=1){
		int gap=step>>1;
		int add_gap=size/step;
		for(int i=0;i<size;i+=step){
			for(int j=i;j<i+gap;j++){
				int k1=(j-i)*add_gap;
				int k2=k1+gap*add_gap;
				complex res1=A[j]+A[j+gap]*u[k1];
				complex res2=A[j]+A[j+gap]*u[k2];
				A[j]=res1,A[j+gap]=res2;
			}
		}
	}
	if(!type)
		for(int i=0;i<size;i++) 
			A[i].real/=(double)size,A[i].imag/=(double)size;
}

int main(){
    freopen("codevs3123.in","r",stdin);
 	cin>>s1>>s1>>s2;
 	int size=1;
 	while(size<max(s1.length(),s2.length())*2)
 		size<<=1;
    for(int i=0;i<s1.length();i++) can1[i]=complex(s1[s1.length()-1-i]-'0');
    for(int i=0;i<s2.length();i++) can2[i]=complex(s2[s2.length()-1-i]-'0'); 	
    fft(can1,size,true);
    fft(can2,size,true);
    for(int i=0;i<size;i++)
    	can3[i]=can1[i]*can2[i];
	fft(can3,size,false);
	for(int i=0;i<size;i++)
		ans[i]=llround(can3[i].real);
	for(int i=0;i<=size;i++){
		ans[i+1]+=ans[i]/10;
		ans[i]%=10;
		if(ans[i]) rightmost=i;
		if(ans[i+1]) rightmost=i+1;
	}
	for(int i=rightmost;i>=0;i--)
		printf("%d",ans[i]);
    return 0;
}