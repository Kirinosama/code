#include <bits/stdc++.h>
using namespace std;

#define MAXN 1000010

set<int>s;
int n,a[MAXN],cnt,T;

void premake(){
	a[++cnt]=1;a[++cnt]=1;
	while(a[cnt]+a[cnt-1]<=1e9){
		a[cnt+1]=a[cnt]+a[cnt-1];
		cnt++;
	}
	for(int i=1;i<=cnt;i++)
		for(int j=i;j<=cnt;j++)
			for(int k=j;k<=cnt;k++)
				s.insert(a[i]+a[j]+a[k]);
}

int main(){
	//freopen("a.in","r",stdin);
	cin>>T;premake();
	while(T--){
		int x;scanf("%d",&x);
		printf("%s\n",s.find(x)==s.end()?"KOTORI":"MINAMI");
	}
	return 0;
}
