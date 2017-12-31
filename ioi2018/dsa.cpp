#include <cstdlib>
#include <cstdio>
#include <cstring>
#include <iostream>
#include <algorithm>
#include <cmath>
using namespace std;

#define MAXN 200010
#define MAXM 2000010
#define ii pair<int,int>
#define INF 0x3f3f3f3f
typedef long long ll;

//f[k][d]表示从k开始长度为d的最早结束位置
//popback时反向更新（可在结尾用set存）

int n,m,q,a[MAXN],maxlen,cnt;
int f[MAXN][30],pos[MAXM];

void addl(int x){
	n++;
	for(int i=n;i>=2;i--){
		a[i]=a[i-1];
		pos[a[i]]=i;
		for(int j=0;j<30;j++)
			f[i][j]=f[i-1][j]==INF?INF:f[i-1][j]+1;
	}
	memset(f[1],0x3f,sizeof(f[1]));
	a[1]=x,pos[x]=1,f[1][1]=1;
	for(int i=2;i<=n;i++)
		if(!(a[i]%x))
			for(int j=25;j>=2;j--){
				f[1][j]=min(f[1][j],f[i][j-1]);
			}
	for(int i=25;i>=maxlen;i--){
		if(f[1][i]!=INF){
			if(i==maxlen) cnt++;
			else maxlen=i,cnt=1;
		}
	}
	cout<<maxlen<<' '<<cnt<<endl;
}

void addr(int x){
	n++;
	memset(f[n],0x3f,sizeof(f[n]));
	a[n]=x,pos[x]=n,f[n][1]=n;
	for(int i=1;i<n;i++)
		for(int j=25;j>=1;j--){
			if(f[i][j]!=INF && !(x%a[f[i][j]])){
				f[i][j+1]=min(f[i][j+1],n);
				if(f[i][j+1]!=INF && j+1>=maxlen){
					if(j+1>maxlen) maxlen=j+1,cnt=1;
					else cnt++;
				}
			}
		}
	cout<<maxlen<<' '<<cnt<<endl;
}

void dell(){
	n--;pos[a[1]]=0;
	if(f[1][maxlen]!=INF){
		cnt--;
		if(!cnt){
			maxlen--;
			for(int i=2;i<=n+1;i++)
				if(f[i][maxlen]!=INF)cnt++;
		}
	}
	cout<<maxlen<<' '<<cnt<<endl;
	for(int i=1;i<=n;i++){
		a[i]=a[i+1];
		pos[a[i]]=i;
		for(int j=0;j<30;j++){
			if(f[i+1][j]==INF)
				f[i][j]=INF;
			else f[i][j]=f[i+1][j]-1;
		}
	}
}

void delr(){
	pos[a[n]]=0,n--;
	if(maxlen==1) cnt--;
	for(int i=1;i<=sqrt(a[n+1]);i++){
		if(!(a[n+1]%i)){
			if(pos[i] && pos[i]<n+1)
				for(int j=25;j>=1;j--)
					if(f[pos[i]][j]==n+1){
						f[pos[i]][j]=INF;
						if(j==maxlen) cnt--;
					}
			if(pos[a[n+1]/i] && pos[a[n+1]/i]<n+1)
				for(int j=25;j>=1;j--)
					if(f[pos[a[n+1]/i]][j]==n+1){
						f[pos[a[n+1]/i]][j]=INF;
						if(j==maxlen) cnt--;
					}
		}
	}
	if(!cnt){
		maxlen--;
		for(int i=1;i<=n;i++)
			if(f[i][maxlen]!=INF) cnt++;
	}
	cout<<maxlen<<' '<<cnt<<endl;
}

void solve(){
	int type,x;
	scanf("%d",&type);
	switch (type){
		case 0:
			scanf("%d",&x);
			addl(x);
			break;
		case 1:
			scanf("%d",&x);
			addr(x);
			break;
		case 2:
			dell();
			break;
		case 3:;
			delr();
	}
}

void premake(){
	memset(f,0x3f,sizeof(f));
	for(int i=n;i>=1;i--)
		f[i][1]=pos[a[i]]=i;
	for(int i=n;i>=1;i--){
		for(int j=1;j<=sqrt(a[i]);j++)
			if(!(a[i]%j)){
				if(pos[j] && pos[j]<i)
					for(int k=25;k>=2;k--)
						f[pos[j]][k]=min(f[pos[j]][k],f[i][k-1]);
				if(pos[a[i]/j] && pos[a[i]/j]<i)
					for(int k=25;k>=2;k--)
						f[pos[a[i]/j]][k]=min(f[pos[a[i]/j]][k],f[i][k-1]);
			}
	}
	for(int i=1;i<=n;i++)
		for(int j=25;j>=maxlen;j--)
			if(f[i][j]!=INF){
				if(j>maxlen) maxlen=j,cnt=1;
				else cnt++;
			}
	cout<<maxlen<<' '<<cnt<<endl;
}

int main(){
    freopen("dsa.in","r",stdin);
    freopen("dsa.out","w",stdout);
    cin>>n>>m>>q;
    for(int i=1;i<=n;i++)
    	scanf("%d",&a[i]);
    premake();
    while(q--)
    	solve();
    return 0;
}