#include <bits/stdc++.h>
using namespace std;

#define MAXN 10010
#define INF 0x3f3f3f3f

string s;
int n,x;
int f[50][10010];

int getnum(int l,int r){
	int res=0;
	for(int i=l;i<=r;i++){
		res=res*10+s[i]-'0';
		if(res>x) return INF;
	}
	return res;
}

int main(){
	cin>>s>>x;
	n=s.length();s=' '+s;
	memset(f,0x3f,sizeof(f));
	f[0][0]=-1;
	for(int i=1;i<=n;i++){
		for(int j=0;j<i;j++){
			int cur=getnum(j+1,i);
			if(cur>x) continue;
			for(int k=cur;k<=x;k++)if(f[j][k-cur]!=INF)
				f[i][k]=min(f[i][k],f[j][k-cur]+1);
		}
	}
	cout<<(f[n][x]==INF?-1:f[n][x]);
	return 0;
}
