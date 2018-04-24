#include <cstdlib>
#include <cstdio>
#include <cstring>
#include <iostream>
#include <algorithm>
using namespace std;

#define ii pair<int,int>
#define INF 0x3f3f3f3f
typedef long long ll;

int main(){
    freopen("bzoj4552.in","r",stdin);
    cin>>n>>m;
    for(int i=1;i<=n;i++)scanf("%d",&a[i]);
    while(m--)solve();
    return 0;
}
