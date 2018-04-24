#include <cstdlib>
#include <cstdio>
#include <cstring>
#include <iostream>
#include <algorithm>
#include <map>
#include <cmath>
using namespace std;

#define ii pair<int,int>
#define INF 0x3f3f3f3f
typedef long long ll;

int n,k;
map <int,int> book;

ll pow(ll x,ll y,ll z){
    ll res=1;
    while(y){
        if(y&1)res=(res*x)%z;
        x=(x*x)%z,y>>=1;
    }
    return res;
}

void solve1(){
    ll x,y,z;
    scanf("%lld%lld%lld",&x,&y,&z);
    printf("%lld\n",pow(x,y,z));
}

ll gcd(ll x,ll y){
    if(!x) return y;
    if(!y) return x;
    return gcd(y,x%y);
}

void solve2(){
    ll x,y,z;
    scanf("%lld%lld%lld",&x,&y,&z);
    ll t=gcd(x,z);
    if(y%t){
        printf("Orz, I cannot find x!\n");
        return;
    }
    ll inv=pow(x,z-2,z);
    printf("%lld\n",(inv*y)%z);
}

void solve3(){
    ll a,b,p;
    scanf("%lld%lld%lld",&a,&b,&p);
    ll sqr=ceil(sqrt(p));ll now=b;
    book.clear();
    for(int i=0;i<=sqr;i++){
        book[now]=i;
        now=(now*a)%p;
    }
    a=pow(a,sqr,p);now=a;
    for(int i=1;i<=sqr;i++){
        if(book.find(now)!=book.end()){
            printf("%lld\n",i*sqr-book[now]);
            return;
        }
        now=(now*a)%p;
    }
    printf("Orz, I cannot find x!\n");
}

int main(){
    freopen("bzoj2242.in","r",stdin);
    cin>>n>>k;
    for(int i=1;i<=n;i++){
        if(k==1)solve1();
        else if(k==2) solve2();
        else solve3();
    }
    return 0;
}
