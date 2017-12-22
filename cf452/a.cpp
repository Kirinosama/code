#include <cstdlib>
#include <cstdio>
#include <cstring>
#include <iostream>
#include <algorithm>
using namespace std;

#define MAXN 200010
#define ii pair<int,int>
#define INF 0x3f3f3f3f
typedef long long ll;

int a[MAXN],n,cnt1,cnt2;

int main(){
    freopen("cf452.in","r",stdin);
    scanf("%d",&n);
    for(int i=1;i<=n;i++){
    	scanf("%d",&a[i]);
    	if(a[i]==1) cnt1++;
    	if(a[i]==2) cnt2++;
    }
    int k=min(cnt1,cnt2);
    printf("%d",k+(cnt1-k)/3);
    return 0;
}