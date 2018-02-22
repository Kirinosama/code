#include <cstdlib>
#include <cstdio>
#include <cstring>
#include <iostream>
#include <algorithm>
#include <cmath>
using namespace std;

#define ii pair<int,int>
#define INF 0x3f3f3f3f
typedef long long ll;

int T,w[20];

int cal(int *a){
	int tot=0;
	int cnt[14]={0};
	int cnt1[11]={0};
	bool flag1=true,flag2=true,flag3=false,flag4=false;
	for(int i=0;i<5;i++){
		tot+=w[a[i]];cnt[a[i]]++;cnt1[w[a[i]]]++;
		if(a[i]>=5) flag1=false;
		if(a[i]<=10) flag2=false;
	}
	for(int i=1;i<=13;i++) if(cnt[i]>=4) flag3=true;
	if(tot<=10 && flag1) return 60;
	if(flag2) return 50;
	if(flag3) return 40;
	for(int i=0;i<5;i++){
		if(flag4)break;
		for(int j=i+1;j<5;j++){
			int k=((w[a[i]]+w[a[j]])/10+1)*10-w[a[i]]-w[a[j]];
			int sum=(w[a[i]]==k)+(w[a[j]]==k);
			if(cnt1[k]-sum){
				flag4=true;break;
			}
		}
	}
	if(flag4){
		if(tot%10==0) return 30;
		if(tot%10<7) return tot%10;
		else return (tot%10)*2;
	}else return 0;
}

void solve(){
	int a[5],sum=0;
	scanf("%d %d %d %d",&a[0],&a[1],&a[2],&a[3]);
	for(int i=1;i<=13;i++){	
		a[4]=i;
		//printf("%d : %d\n",i,cal(a));
		sum+=cal(a);
	}
	printf("%d\n",(int)floor((double)sum/13.0+0.5001));
}

int main(){
    freopen("niuniu.in","r",stdin);
    freopen("niuniu.out","w",stdout);
    cin>>T;
    for(int i=1;i<=13;i++) w[i]=i<=10?i:10;
    while(T--)solve();
    return 0;
}