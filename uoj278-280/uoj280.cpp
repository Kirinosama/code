#include <bits/stdc++.h>
using namespace std;

#define MAXN 100010

int Max,n,a[MAXN],b[MAXN];
set <int> s;

void premake(){
	for(int i=1;i<=n;i++)b[i]=a[i];
	sort(b+1,b+n+1);
	Max=unique(b+1,b+n+1)-b-1;
}

bool judge(int mid){
	for():
}

int main(){
	freopen("input","r",stdin);
	cin>>n;
	for(int i=1;i<=n;i++)
		scanf("%d",&a[i]),s.insert(a[i]);
	premake();
	int l=1,r=Max,res;
	while(l<=r){
		int mid=(l+r)>>1;
		if(judge(b[mid])) res=b[mid],l=mid+1;
		else r=mid-1;
	}
	cout<<res;
	return 0;
}
