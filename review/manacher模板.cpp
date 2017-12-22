#include <cstdlib>
#include <cstdio>
#include <cstring>
#include <iostream>
#include <algorithm>
using namespace std;

#define MAXN 22000010

string s1,s;
int l[MAXN];

inline void manacher(){
	int ans=-1;
	int maxright=-1,pos=-1;
	for(register int i=0;i<s.length();i++){
		if(i<=maxright) l[i]=min(l[2*pos-i],maxright-i+1);
		else l[i]=1;
		for(int &j=l[i];i-j>=0 && i+j<s.length() && s[i-j]==s[i+j];j++)
		if(i+l[i]-1>maxright)
			maxright=i+l[i]-1,pos=i;
		if(i%2) ans=max(ans,(l[i]-1)/2*2+1);
		else ans=max(ans,l[i]/2*2);
	}
	cout<<ans;
}

int main(){
	freopen("input","r",stdin);
	cin>>s1;
	s+='#';
	for(register int i=0;i<s1.length();i++)
		s+=s1[i],s+='#';
	manacher();
	return 0;
}