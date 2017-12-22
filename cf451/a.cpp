#include <cstdlib>
#include <cstdio>
#include <cstring>
#include <iostream>
#include <algorithm>
using namespace std;

#define ii pair<int,int>
#define INF 0x3f3f3f3f
typedef long long ll;

int n;

int main(){
    freopen("cf451.in","r",stdin);
    scanf("%d",&n);
    int k=n%10;
    if(k<=5) printf("%d",n-k);
    else printf("%d",n+10-k);
    return 0;
}