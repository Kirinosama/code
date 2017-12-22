#include <cstdlib>
#include <cstdio>
#include <cstring>
#include <iostream>
#include <algorithm>
#include <map>
using namespace std;

#define MAXN 50100
int a[MAXN],n,ans;

void merge_sort(int l,int r){
	if(l==r) return;
	int mid=(l+r)>>1;
	int s[MAXN],cnt=-1;
	merge_sort(l,mid);
	merge_sort(mid+1,r);
	int pos1=l,pos2=mid+1;
	while(pos1<=mid && pos2<=r){
		if(a[pos1]<=a[pos2])
			s[++cnt]=a[pos1++];
		else{
			ans+=mid+1-pos1;
			s[++cnt]=a[pos2++];
		}
	}
	while(pos1<=mid) s[++cnt]=a[pos1++];
	while(pos2<=r) s[++cnt]=a[pos2++];
	for(int i=l;i<=r;i++) a[i]=s[i-l];
}

int main(){
	freopen("input","r",stdin);
	cin>>n;
	for(int i=1;i<=n;i++) scanf("%d",&a[i]);
	merge_sort(1,n);
	cout<<ans;
	return 0;
}