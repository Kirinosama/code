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

int n;

struct complex{
    double real,imag;
    complex(){real=imag=0.0;}
    complex(double x,double y){real=x,imag=y;}
    complex operator + (const complex &a)const{
        return complex(real+a.real,imag+a.imag);
    }
    complex operator - (const complex &a)const{
        return complex(real-a.real,imag-a.imag);
    }
    complex operator * (const complex &a)const{
        return complex(real*a.real-imag*a.imag,imag*a.real+real*a.imag);
    }
    void operator /= (const double x){
        real/=x,imag/=x;
    }
}A[MAXN],B[MAXN],C[MAXN],u[MAXN];

int lowbit(int x){
    return x&-x;
}

int bit_reverse(int x,int size){
    int res=0;
    for(int i=x;i;i-=lowbit(i)){
        res+=size/2/lowbit(i);
    }
    return res;
}

void fft(complex *A,int size,bool opt){
    for(int i=0;i<size;i++){
        int j=bit_reverse(i,size);
        if(i>j)swap(A[i],A[j]);
    }
    for(int i=0;i<size;i++){
        double ang=(opt?2.0:-2.0)*M_PI*(double)i/(double)size;
        u[i]=complex(cos(ang),sin(ang));
    }
    for(int step=2;step<=size;step<<=1){
        int gap=step>>1,add_gap=size/step;
        for(int i=0;i<size;i+=step){
            for(int j=i;j<i+gap;j++){
                int k1=(j-i)*add_gap;
                int k2=k1+gap*add_gap;
                complex new1=A[j]+A[j+gap]*u[k1];
                complex new2=A[j]+A[j+gap]*u[k2];
                A[j]=new1,A[j+gap]=new2;
            }
        }
    }
    if(!opt){
        for(int i=0;i<size;i++)A[i]/=(double)size;
    }
}

int main(){
    freopen("bzoj2194.in","r",stdin);
    cin>>n;
    for(int i=0;i<n;i++){
        scanf("%lf%lf",&A[i].real,&B[n-1-i].real);
    }
    int size=1;while(size<2*n) size<<=1;
    fft(A,size,true);fft(B,size,true);
    for(int i=0;i<size;i++)C[i]=A[i]*B[i];
    fft(C,size,false);
    for(int i=n-1;i<=2*n-2;i++)printf("%lld\n",llround(C[i].real));
    return 0;
}
