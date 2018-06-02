#include <bits/stdc++.h>
using namespace std;

int cnt[1010],rk[1010],sa[1010],sa2[1010],height[1010];
string s;
int n;

bool same(int *a,int x,int y,int z){
	return a[x]==a[y] && a[x+z]==a[y+z];
}

void getsa(int m){
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
		for(int i=1;i<n;i++)rk[sa[i]]=rk[sa[i-1]]+!same(sa2,sa[i],sa[i-1],gap);
		m=rk[sa[n-1]]+1;if(n==m) break;
	}
}

void getheight(){
	for(int i=0;i<n;i++)rk[sa[i]]=i;
	int k=0;
	for(int i=0;i<n-1;i++){
		int j=sa[rk[i]-1];
		if(k) k--;
		while(s[i+k]==s[j+k]) k++;
		height[rk[i]]=k;
	}
}

int main(){
	freopen("input","r",stdin);
	cin>>s;s=s+'\n';n=s.length();
	getsa('z'+1);
	getheight();
	for(int i=0;i<n;i++){
		for(int j=sa[i];j<n;j++)printf("%c",s[j]);
		cout<<endl;
	}
	for(int i=1;i<n;i++)printf("%d ",height[i]);
	return 0;
}
