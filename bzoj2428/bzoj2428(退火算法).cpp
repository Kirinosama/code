#include <cstdlib>
#include <cstdio>
#include <cstring>
#include <cmath>
#include <iostream>
#include <algorithm>
using namespace std;

#define ii pair<int,int>
#define INF 0x3f3f3f3f
typedef long long ll;

double minans,ave,sum[30];
int n,m,a[30],belong[30];

void init(){
	for(int i=1;i<=m;i++)
		sum[i]=0.0;
	for(int i=1;i<=n;i++){
		int x=rand()%m+1;
		belong[i]=x;
		sum[x]+=a[i];
	}
}

void sa(){
	double t=10000;
	double ans=0.0,tmp;
	init();
	for(int i=1;i<=m;i++)
		ans+=(sum[i]-ave)*(sum[i]-ave);
	while(t>0.1){
		t*=0.9;
		int p=rand()%n+1,x=belong[p],y;
		if(t>500)
			y=min_element(sum+1,sum+m+1)-sum;
		else y=rand()%m+1;
		if(x==y) continue;
		tmp=ans;
		tmp-=(sum[x]-ave)*(sum[x]-ave);
		tmp-=(sum[y]-ave)*(sum[y]-ave);
		sum[x]-=a[p],sum[y]+=a[p];
		tmp+=(sum[x]-ave)*(sum[x]-ave);
		tmp+=(sum[y]-ave)*(sum[y]-ave);
		if(tmp<=ans){
			belong[p]=y;ans=tmp;
		}
		else if(rand()%10000>t){
			sum[x]+=a[p],sum[y]-=a[p];
		}
		else{
			belong[p]=y;ans=tmp;
		}
		minans=min(minans,ans);
	}
}

int main(){
    freopen("bzoj2428.in","r",stdin);
    srand(19990720);
    scanf("%d %d",&n,&m);
    for(int i=1;i<=n;i++){
    	scanf("%d",&a[i]);
    	ave+=a[i];
    }
    ave/=(double)m;minans=1e30;
    for(int i=1;i<=10000;i++)
    	sa();
    printf("%.2lf",sqrt(minans/m));
    return 0;
}