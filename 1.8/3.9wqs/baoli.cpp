#include <cstdlib>
#include <cstdio>
#include <cstring>
#include <iostream>
#include <algorithm>
using namespace std;

#define MOD 10000007
#define ii pair<int,int>
#define INF 0x3f3f3f3f
typedef long long ll;

int a[10010],b[10010],sum1,sum2;

int main(){
    freopen("3.9wqs.in","r",stdin);
    a[1]=1;b[2]=1;
    for(int i=3;i<=10002;i++){
    	a[i]=(a[i-1]+a[i-2])%MOD;
    	b[i]=(b[i-1]+b[i-2])%MOD;
    	sum1=(sum1+a[i])%MOD;sum2=(sum2+b[i])%MOD;
    }
    printf("%d %d\n%d %d\n%d %d",a[10001],b[10001],a[10002],b[10002],sum1,sum2);
    return 0;
}