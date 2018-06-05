#include <bits/stdc++.h>
using namespace std;

int height[1010],sa[1010],sa2[1010],rk[1010],cnt[1010];
string str;
int n;

bool same(int *s,int x,int y,int z){
	return s[x]==s[y] && s[x+z]==s[y+z];
}

void getsa(int m){
	for(int i=0;i<m;i++)cnt[i]=0;
	for(int i=0;i<n;i++)cnt[rk[i]=str[i]]++;
	for(int i=1;i<m;i++)cnt[i]+=cnt[i-1];
	for(int i=n-1;i>=0;i--)sa[--cnt[rk[i]]]=i;
	for(int gap=1;gap<n;gap<<=1){
		int p=0;
		for(int i=n-gap;i<n;i++)
			sa2[p++]=i;
		for(int i=0;i<n;i++)if(sa[i]>=gap)
			sa2[p++]=sa[i]-gap;
		for(int i=0;i<m;i++)cnt[i]=0;
		for(int i=0;i<n;i++)cnt[rk[i]]++;
		for(int i=1;i<m;i++)cnt[i]+=cnt[i-1];
		for(int i=n-1;i>=0;i--)sa[--cnt[rk[sa2[i]]]]=sa2[i];
		swap(rk,sa2);rk[sa[0]]=0;
		for(int i=1;i<n;i++)rk[sa[i]]=rk[sa[i-1]]+!same(sa2,sa[i],sa[i-1],gap);
		m=rk[sa[n-1]]+1;if(n==m)break;
	}
}

void getheight(){
	for(int i=0;i<n;i++)rk[sa[i]]=i;
	int k=0;
	for(int i=0;i<n-1;i++){
		int j=sa[rk[i]-1];	
		if(k) k--;
		while(str[i+k]==str[j+k]) k++;
		height[rk[i]]=k;
	}
}

int main(){
	freopen("input","r",stdin);
	cin>>str;
	str=str+'\n';n=str.length();
	getsa('z'+1);
	getheight();
	for(int i=0;i<n;i++){
		int pos=sa[i];printf("%d",height[i]);
		for(int j=pos;j<n;j++)printf("%c",str[j]);
	}
	return 0;
}
