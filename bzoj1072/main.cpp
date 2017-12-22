#include<iostream>  
#include<cstdio>  
#include<cstring>  
using namespace std;  
int K,n,limit[16];  
double f[101][1<<16],p[16];  
int main()  
{  
    int x;  
    scanf("%d%d",&K,&n);  
    for(int i=1;i<=n;++i){  
        scanf("%lf",&p[i]);  
        while(scanf("%d",&x)){  
            if(!x) break;  
            limit[i]|=1<<(x-1);  
        }  
    }  
    for(int i=K;i>=1;--i)  
      for(int j=0;j<=(1<<(n+1))-1;++j)  
      {  
        for(int k=1;k<=n;++k)  
        {  
            if((limit[k]&j)==limit[k]) f[i][j]+=max(f[i+1][j],f[i+1][j|(1<<(k-1))]+p[k]);  
            else f[i][j]+=f[i+1][j];      
        }  
        f[i][j]/=n;  
      }  
    printf("%.6f\n",f[1][0]);  
}  
