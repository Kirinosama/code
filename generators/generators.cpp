#include <bits/stdc++.h>
using namespace std;

#define MAXN 10010

int n,k,ch,pos,Maxpos[MAXN];
int x[MAXN],a[MAXN],b[MAXN],c[MAXN],Max[MAXN];

int main(){
	freopen("input","r",stdin);
	cin>>n>>k;
	int ans=0,ans1=-1;
	for(int i=1;i<=n;i++)
		scanf("%d%d%d%d",&x[i],&a[i],&b[i],&c[i]);
	for(int i=1;i<=n;i++){
		int cur=x[i],tot=0;Max[i]=-1;
		while(1){
			if(cur>Max[i])Max[i]=cur,Maxpos[i]=t;
			cur=(cur*a[i]+b[i])%c[i];
			if(cur==x[i]) break;
			tot++;
		}
		ans+=Max[i];
	}
	if(ans%k){
		cout<<ans<<endl;
		for(int i=1;i<=n;i++)printf("%d ",Maxpos[i]);
		return 0;
	}
	for(int i=1;i<=n;i++){
		int cur=x[i],tot=0;
		while(1){
			if((ans-Max[i]+cur)%k)
				if(ans-Max[i]+cur>ans1){
					ans1=ans-Max[i]+cur;
					ch=i;pos=tot;
				}
			cur=(cur*a[i]+b[i])%c[i];
			if(cur==x[i]) break;
			tot++;
		}
	}
	if(ans1==-1) cout<<-1;
	else{
		cout<<ans1<<endl;
		for(int i=1;i<=n;i++){
			if(ch==i) printf("%d ",pos);
			else printf("%d ",Maxpos[i]);
		}
	}
	return 0;
}
