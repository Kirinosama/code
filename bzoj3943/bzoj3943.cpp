#include <cstdio>  
#include <cstring>  
#include <iostream>  
#include <algorithm>  
#define M 2020  
using namespace std;  
int n,a[M];  
long long ans;  
void Prim()  
{  
    static int f[M];  
    static bool v[M];  
    int i,j,k;  
    for(i=1;i<=n;i++)  
    {  
        k=0;  
        for(j=1;j<=n;j++)  
            if(!v[j]&&f[j]>=f[k])  
                k=j;  
        v[k]=true;ans+=f[k];  
        for(j=1;j<=n;j++)  
            f[j]=max(f[j],a[k]^a[j]);  
    }  
}  

int main()  
{  
	freopen("bzoj3943.in","r",stdin);
    int i;  
    cin>>n;  
    for(i=1;i<=n;i++)  
        scanf("%d",&a[i]);  
    Prim();  
    cout<<ans<<endl;  
    return 0;  
}  
