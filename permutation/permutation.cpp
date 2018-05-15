#include <cstdlib>
#include <cstdio>
#include <cstring>
#include <iostream>
#include <algorithm>
using namespace std;

#define ii pair<int,int>
#define INF 0x3f3f3f3f
typedef long long ll;

struct bignum{
    int num[510];
    int len;
    bignum(){len=1;memset(num,0,sizeof(num));}
    bignum(int x){
        if(!x) return;
        len=0;
        while(x){
            num[len]=x%10;
            x/=10,len++;
        }
    }
    bignum operator + (const bignum &a)const{
        bignum c;
        for(int i=0;i<=max(a.len,len);i++){
            c.num[i]+=num[i]+a.num[i];
            if(c.num[i]>=10)c.num[i+1]+=c.num[i]/10,c.num[i]%=10;
        }
        c.len=1;
        for(int i=1;i<=max(a.len,len);i++)if(c.num[i])
            c.len=i+1;
        return c;
    }
    bignum operator * (const bignum &a)const{
        bignum c;
        for(int i=0;i<len;i++)
            for(int j=0;j<a.len;j++)
                c.num[i+j]+=num[i]*a.num[j];
        for(int i=0;i<len+a.len;i++){
            if(c.num[i]>=10)c.num[i+1]+=c.num[i]/10,c.num[i]%=10;
        }
        c.len=1;
        for(int i=1;i<=len+a.len;i++)if(c.num[i])
            c.len=i+1;
        return c;
    }
    void print(){
        for(int i=len-1;i>=0;i--)printf("%d",num[i]);
    }
}f[110][110];

int n,m;

int main(){
    freopen("permutation.in","r",stdin);
    freopen("permutation.out","w",stdout);
    cin>>n>>m;f[1][0]=bignum(1);
    for(int i=2;i<=n;i++){
        for(int j=0;j<=m;j++){
            f[i][j]=f[i][j]+f[i-1][j]*bignum(j+1);
            if(j>0)f[i][j]=f[i][j]+f[i-1][j-1]*bignum(i-j);
        }
    }
    f[n][m].print();
    return 0;
}
