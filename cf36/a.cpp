#include <cstdlib>
#include <cstdio>
#include <cstring>
#include <iostream>
#include <algorithm>
using namespace std;

#define ii pair<int,int>
#define INF 0x3f3f3f3f
typedef long long ll;

int n,k,a[210];

int main(){
    freopen("cf36.in","r",stdin);
    cin>>n>>k;
    for(int i=1;i<=n;i++)
    	scanf("%d",&a[i]),a[i]=-a[i];
    sort(a+1,a+1+n);
    for(int i=1;i<=n;i++)
    	if(!(k%(-a[i]))){
    		printf("%d",k/(-a[i]));
    		return 0;
    	}
    return 0;
}