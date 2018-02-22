#include <cstdlib>
#include <cstdio>
#include <cstring>
#include <iostream>
#include <algorithm>
using namespace std;

#define ii pair<int,int>
#define INF 0x3f3f3f3f
typedef long long ll;

int n,l,r;

int main(){
    freopen("cycle.in","r",stdin);
    freopen("cycle.out","w",stdout);
    cin>>n;l=INF,r=INF;
    for(int i=1;i<=n;i++){
    	int x;
    	scanf("%d",&x);
    	if(!x){
    		l=min(l,i-1);
    		r=min(r,n-i);
    	}
    }
    if((l&1) || (r&1)) cout<<"YES";
    else cout<<"NO";
    return 0;
}