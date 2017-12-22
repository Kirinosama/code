#include<cmath>  
#include<cstdio>  
#include<cstring>  
#include<iostream>  
#include<algorithm>  
using namespace std;  

typedef long long ll;  
ll r,ans;  
ll factors[100100];  
int tot;

void Get_Factors(ll x)  
{  
    ll i;  
    for(i=1;i*i<x;i++)  
        if(x%i==0)  
            factors[++tot]=i,factors[++tot]=x/i;  
    if(i*i==x)  
        factors[++tot]=i;  
}  

ll GCD(ll x,ll y)  
{  
    return y?GCD(y,x%y):x;  
}

bool Is_Square(ll x)  
{  
    double temp=sqrt( (double)x );  
    if(fabs(floor(temp+1e-7)-temp)<1e-7)  
        return true;  
    return false;  
}
  
int main()  
{  
    cin>>r;  
    int i;  
    ll u;  
    Get_Factors(r<<1);  
    for(i=1;i<=tot;i++)  
    {  
        ll d=factors[i];  
        for(u=1;u*u<(r+1)/d;u++)  
        {  
            ll v_2=r*2/factors[i]-u*u;  
            if( Is_Square(v_2) )  
                if(GCD(v_2,u*u)==1)  
                    ++ans;  
        }  
    }  
    cout<<(ans+1<<2)<<endl;  
}  