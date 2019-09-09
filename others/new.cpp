#include <cstdlib>
#include <cstring>
#include <cstdio>
#include <iostream>
using namespace std;

int f[2][1024][1024];
int n,m,ans,M[110];
char a[110][20];


bool check(int l,int mask){
	if(l<1) return true;
	if((mask&(mask<<1))!=0) return false;
	if((mask&(mask<<2))!=0) return false;
/*	for(int i=m;i>=1;i--){
		int x=mask&1;
		if(x==1 && a[l][i]=='H') return false;
		mask>>=1;
	}*/
	if(mask&M[l]) return false;
	return true;
}

bool ok(int mask1,int mask2){
	if(mask1&mask2) return false;
	else return true; 
}

int lowbit(int x){return x&-x;}

int cal1(int mask){
	int cnt=0;
	for(int i=mask;i;i-=lowbit(i))
		cnt++;
	return cnt;
}

int main(){
//	freopen("input.in","r",stdin);
	scanf("%d %d\n",&n,&m);
	for(int i=1;i<=n;i++){
		for(int j=1;j<=m;j++)
			scanf("%c",&a[i][j]);
		scanf("\n");
		for(int j=m;j>=1;j--)
			M[i]=(M[i]<<1)+(a[i][j]=='H');
	}
	int Maxmask=1<<m;
	for(int i=0;i<Maxmask;i++)
		for(int j=0;j<Maxmask;j++)
			f[0][i][j]=0xc0c0c0c0;
	f[0][0][0]=0;
	for(int i=1;i<=n;i++){
		for(int j=0;j<Maxmask;j++)if(check(i,j)){ //j本行的选法 
			for(int k=0;k<Maxmask;k++)if(ok(j,k) && check(i-1,k)){ //k是上一行的选法 
				f[i&1][j][k]=0xc0c0c0c0;
				for(int p=0;p<Maxmask;p++)if(ok(j,p)){//p是上上的选法 
					f[i&1][j][k]=max(f[i&1][j][k],f[(i-1)&1][k][p]);
				}
				f[i&1][j][k]+=+cal1(j);
				if(i==n) ans=max(ans,f[i&1][j][k]);
			}
		}
	}
	cout<<ans;
	return 0;
}
