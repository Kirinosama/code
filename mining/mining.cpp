#include <cstdlib>
#include <cstdio>
#include <cstring>
#include <iostream>
#include <algorithm>
using namespace std;

#define MAXN 100010
#define ii pair<int,int>
#define INF 0x3f3f3f3f
typedef long long ll;

struct mine{
	int x,y;
	bool operator < (const mine &a)const{
		return x<a.x;
	}
}E[MAXN];

int n,m,cnt,ans,book[20];
int a[MAXN],b[MAXN],f[MAXN];

int main(){
    freopen("mining10.in","r",stdin);
    freopen("mining10.out","w",stdout);
    cin>>n>>m;
    for(int i=1;i<=n;i++)scanf("%d%d",&E[i].y,&E[i].x);
    sort(E+1,E+n+1);
	for(int i=1;i<=n;i++)if(E[i].x!=E[i-1].x){
		a[++cnt]=E[i].x,b[cnt]=E[i].y;
	}else{
		b[cnt]+=E[i].y;
	}
	book[4]=book[7]=book[8]=book[11]=book[12]=book[14]=book[15]=book[16]=1;
	int st=0,Max=0;
	for(int i=1;i<=cnt;i++){
		f[i]=-INF;
		while(a[i]-a[st+1]>=18){
			st++;Max=max(f[st],Max);
		}
		if(a[i]-a[st]>=18) f[i]=max(f[i],b[i]+Max);
		for(int j=i-1;j>=0 && a[i]-a[j]<18;j--)if(book[a[i]-a[j]]){
			f[i]=max(f[i],b[i]+f[j]);
		}
		ans=max(ans,f[i]);
	}
	cout<<ans<<endl;
	//for(int i=1;i<=cnt;i++)printf("%d %d\n",a[i],f[i]);
    return 0;
}