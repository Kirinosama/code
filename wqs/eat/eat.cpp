#include <cstdlib>
#include <cstdio>
#include <cstring>
#include <iostream>
#include <algorithm>
using namespace std;

#define MAXN 5010
#define ii pair<int,int>
#define INF 0x3f3f3f3f
typedef long long ll;

int n,A,B,C,D,a[MAXN],b[MAXN],c[MAXN],d[MAXN];
int s1[MAXN*MAXN],s2[MAXN*MAXN];

int main(){
    freopen("eat.in","r",stdin);
    freopen("eat.out","w",stdout);
    cin>>n>>A>>B>>C>>D;int cnt1=0,cnt2=0;
    for(int i=1;i<=A;i++)scanf("%d",&a[i]);
    for(int i=1;i<=B;i++)scanf("%d",&b[i]);
    for(int i=1;i<=C;i++)scanf("%d",&c[i]);
    for(int i=1;i<=D;i++)scanf("%d",&d[i]);	
    for(int i=1;i<=A;i++)
    	for(int j=1;j<=B;j++)
    		s1[++cnt1]=a[i]+b[j];
    for(int i=1;i<=C;i++)
    	for(int j=1;j<=D;j++)
    		s2[++cnt2]=c[i]+d[j];
    sort(s1+1,s1+cnt1+1);sort(s2+1,s2+cnt2+1);int pos=0;ll ans=0;
    while(pos<cnt2 && s1[1]+s2[pos+1]<=n) pos++;
   	ans+=pos;
   	for(int i=2;i<=cnt1;i++){
   		while(pos && s1[i]+s2[pos]>n) pos--;
   		ans+=pos;
   	}
   	cout<<ans;
    return 0;
}