#include<bits/stdc++.h>
using namespace std;

const int maxsiz=305;

int n,d,a,b;
bool exist0[maxsiz],exist1[maxsiz];
int p[maxsiz];

int main(){
	scanf("%d%d%d%d",&n,&d,&a,&b);
	
	for(int w,i=1;i<=n;i++){
		scanf("%d",&p[i]);
		exist0[p[i]]=true;
	}
		
	for(int i=1;i<=maxsiz/2;i++)
		if(exist0[i]){
			if(i-d>=0&&exist1[i-d])
				continue;
			else exist1[i+d]=true;
		}
	long long ans=0;
	for(int i=1;i<maxsiz;i++)
		if(exist1[i])
			ans+=a;
	printf("%lld\n",ans);
	
	return 0;
}
