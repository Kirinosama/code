#include <bits/stdc++.h>
using namespace std;

int cnt,n,m,k,x;
char a[510],go[510][28],res[510];

int main(){
	freopen("input","r",stdin);
	scanf("%d %d %d %d\n",&n,&m,&k,&x);x--;
	for(int i=1;i<=n;i++)scanf("%c",&a[i]);
	for(int i=1;i<=m;i++){
		scanf("\n");
		for(int j=0;j<k;j++)scanf("%c",&go[i][j]);
		sort(go[i],go[i]+k);
	}
	for(int i=m;i>=1;i--){
		int ch=x%k;
		res[i]=go[i][ch];
		x/=k;
	}
	for(int i=1;i<=n;i++){
		if(a[i]!='#') cout<<a[i];
		else cout<<res[++cnt];
	}
	return 0;
}
