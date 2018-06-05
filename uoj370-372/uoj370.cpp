#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
ll ans,f[300010];
int n,a[100010],book[300010];

void make(int x){
	int Xor=((1<<18)-1)^x;
	if(book[Xor])return;
	for(int i=Xor;i;i=(i-1)&Xor)
		book[i]=1;
}

void premake(){
	int all=(1<<21)-1;
	for(int i=1;i<=n;i++)all&=a[i];
	ans+=(ll)all*(ll)n;
	for(int i=1;i<=n;i++)a[i]^=all;
	for(int i=1;i<=n;i++)make(a[i]);
}

int main(){
	freopen("input","r",stdin);
	freopen("output","w",stdout);
	cin>>n;
	for(int i=1;i<=n;i++)scanf("%d",&a[i]);
	premake();
	memset(f,0x3f,sizeof(f));f[0]=0;
	for(int i=1;i<1<<18;i++){
		for(int j=i;j;j=(j-1)&i){
			if((i^j)>=f[i])break;
			if(book[j])f[i]=min(f[i],f[i^j]+(i^j));
		}
	}
	cout<<f[(1<<18)-1]+ans;
	return 0;
}
