#include <iostream>  
#include <cstring>  
#include <cstdio>  
#include<algorithm>  
using namespace std;  
int main()  `
{  
    int n,k,b,c,d,t1;  
    int a[4005],ans[4005];  
    while(scanf("%d%d",&n,&k)!=EOF)  
    {  
        memset(a,0,sizeof(a));  
        for(int i=0;i<k;i++)  
        {  
            cin>>b;  
            if(b==2)  
            {  
                cin>>t1;  
                a[t1]=1;  
            }  
            else  
            {  
                cin>>c>>d;  
                a[c]=1;  
                a[d]=1;  
            }  
        }  
        int sum=0;  
        int t=0;  
        for(int i=1;i<n;i++)  
        {  
            if(!a[i])  
            {  
                ans[t++]=i; 
            }  
        }  
        for(int i=0;i<t;i++)  
        {  
            int flag=ans[i+1]-ans[i];  
            if(flag==1)  
            i++;  
            sum++;  
        }  
        cout<<sum<<" "<<t<<endl;  
    }  
    return 0;  
}  