#include <cstdlib>
#include <cstdio>
#include <cstring>
#include <iostream>
#include <algorithm>
using namespace std;

#define ii pair<int,int>
#define INF 0x3f3f3f3f
typedef long long ll;

int n,a,b;

int main(){
    freopen("cf451.in","r",stdin);
    scanf("%d %d %d",&n,&a,&b);
    for(int i=0;i*a<=n;i++)
    	if(!((n-i*a)%b)){
    		printf("YES\n%d %d",i,(n-i*a)/b);
    		return 0;
    	}
    printf("NO");
    return 0;
}