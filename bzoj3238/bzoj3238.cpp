#include <cstdlib>
#include <cstdio>
#include <cstring>
#include <iostream>
#include <algorithm>
using namespace std;

#define MAXN 500010
typedef long long ll;

string str;
int sa[MAXN],sa2[MAXN],rk[MAXN],cnt[MAXN],height[MAXN];
int top,sta[MAXN];
ll rp[MAXN],lp[MAXN],n;

bool same(int *a,int x,int y,int z){
	return a[x]==a[y] && a[x+z]==a[y+z];
}

void make_sa(string s,int m){
	for(int i=0;i<m;i++)cnt[i]=0;
	for(int i=0;i<n;i++)cnt[rk[i]=s[i]]++;
	for(int i=1;i<m;i++)cnt[i]+=cnt[i-1];
	for(int i=n-1;i>=0;i--)sa[--cnt[rk[i]]]=i;
	for(int gap=1;gap<n;gap<<=1){
		int p=0;
		for(int i=n-gap;i<n;i++)sa2[p++]=i;
		for(int i=0;i<n;i++)if(sa[i]>=gap)
			sa2[p++]=sa[i]-gap;
		for(int i=0;i<m;i++)cnt[i]=0;
		for(int i=0;i<n;i++)cnt[rk[i]]++;
		for(int i=1;i<m;i++)cnt[i]+=cnt[i-1];
		for(int i=n-1;i>=0;i--)sa[--cnt[rk[sa2[i]]]]=sa2[i];
		swap(rk,sa2);rk[sa[0]]=0;
		for(int i=1;i<n;i++)rk[sa[i]]=rk[sa[i-1]]+!same(sa2,sa[i-1],sa[i],gap);
		m=rk[sa[n-1]]+1;
		if(n==m) return;
	}
}

void make_height(){
	int k=0;
	for(int i=0;i<n;i++)rk[sa[i]]=i;
	for(int i=0;i<n-1;i++){
		if(k) k--;
		int j=sa[rk[i]-1];
		while(str[i+k]==str[j+k]) k++;
		height[rk[i]]=k;
	}
}

int main(){
	freopen("bzoj3238.in","r",stdin);
	cin>>str;str+='\n';n=str.length();
	make_sa(str,'z'+1);
	make_height();
	n--;
	sta[0] = 1;
    for(int i = 2 ; i <= n ; i ++ )
    {
        while(top && height[sta[top]] >= height[i]) top -- ;
        lp[i] = i - sta[top] , sta[++top] = i;
    }
    top = 0 , sta[0] = n + 1;
    for(int i = n ; i >= 2 ; i -- )
    {
        while(top && height[sta[top]] > height[i]) top -- ;
        rp[i] = sta[top] - i , sta[++top] = i;
    }
	ll ans=(n-1)*n*(n+1)/2;
	for(int i=1;i<=n;i++)ans-=2*height[i]*rp[i]*lp[i];
	cout<<ans;
	return 0;
}
