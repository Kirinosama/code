#include <cstdlib>
#include <cstdio>
#include <cstring>
#include <iostream>
#include <algorithm>
using namespace std;

#define MAXN 1010

typedef long long ll;

struct data{
    int l,r;
}p[MAXN];

ll a0,b0;
int n,num[10000020],len,cnt,a[10000020];

bool cmp (const data &a,const data &b){
    return a.l*a.r<b.l*b.r;
}

void mul(int x){
    for(int i=0;i<len;i++)
        num[i]*=x;
    for(int i=0;i<len+15;i++)
        if(num[i]>=10)
            num[i+1]+=num[i]/10,num[i]%=10;
    for(int i=len+15;i>=0;i--){
        if(num[i]){
            len=i+1;break;
        }
    }
}

void Devide(int x){
    int i,sum=0;cnt=0;
    memset(a,0,sizeof(a));
    for(i=len-1;i>=0;i--){
        sum=sum*10+num[i];
        if(sum>=x){
            break;
        }
    }
    if(sum<x){
        a[++cnt]=0;
        printf("1");
        return;
    }
    a[++cnt]=sum/x;sum%=x;
    for(i=i-1;i>=0;i--){
        sum=sum*10+num[i];
        a[++cnt]=sum/x;
        sum%=x;
    }
    for(int i=1;i<=cnt;i++) printf("%d",a[i]);
}

int main(){
//	freopen("input","r",stdin);
    cin>>n>>a0>>b0;
    p[0].l=a0,p[0].r=b0;
    for(int i=1;i<=n;i++) scanf("%d %d",&p[i].l,&p[i].r);
    sort(p+1,p+1+n,cmp);len=1;num[0]=1;
    for(int i=1;i<=n;i++)
        mul(p[i-1].l);
    Devide(p[n].r);
    return 0;
}