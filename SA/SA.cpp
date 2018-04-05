#include <cstdlib>
#include <cstdio>
#include <cstring>
#include <iostream>
#include <algorithm>
using namespace std;

/*
末尾补'\n'防越界 
*/

#define MAXN 100010
#define ii pair<int,int>
#define INF 0x3f3f3f3f
typedef long long ll;

string s;
int n,rk[MAXN],sa[MAXN],sa2[MAXN],cnt[MAXN],height[MAXN];

bool same(int *t,int x,int y,int len){
	return t[x]==t[y] && t[x+len]==t[y+len];
}

void build_sa(int m){
	for(int i=0;i<m;i++) cnt[i]=0;
	for(int i=0;i<n;i++) cnt[rk[i]=s[i]]++;
	for(int i=1;i<m;i++) cnt[i]+=cnt[i-1];
	for(int i=n-1;i>=0;i--) sa[--cnt[rk[i]]]=i;
	for(int gap=1;gap<n;gap<<=1){
		int p=0;
		for(int i=n-gap;i<n;i++) sa2[p++]=i;
		for(int i=0;i<n;i++)if(sa[i]>=gap)
			sa2[p++]=sa[i]-gap;
		for(int i=0;i<m;i++) cnt[i]=0;
		for(int i=0;i<n;i++) cnt[rk[i]]++;
		for(int i=1;i<m;i++) cnt[i]+=cnt[i-1];
		for(int i=n-1;i>=0;i--) sa[--cnt[rk[sa2[i]]]]=sa2[i];
		swap(sa2,rk);
		rk[sa[0]]=0;
		for(int i=1;i<n;i++)
			rk[sa[i]]=rk[sa[i-1]]+!same(sa2,sa[i],sa[i-1],gap);
		m=rk[sa[n-1]]+1;
		if(n==m) break;
	}
}

void build_height(){
	int k=0;
	for(int i=0;i<n;i++) rk[sa[i]]=i;
	for(int i=0;i<n;i++){
		if(k) k--;
		int j=sa[rk[i]-1];
		while(s[i+k]==s[j+k]) k++;
		height[rk[i]]=k;
	}
}

int main(){
    freopen("SA.in","r",stdin);
    cin>>s;s=s+'\n';n=s.length();
    build_sa('z'+1);
    build_height();
    for(int i=0;i<n;i++) printf("%d ",sa[i]);
    	cout<<endl;
    for(int i=0;i<n;i++) printf("%d ",height[i]);
    return 0;
}
