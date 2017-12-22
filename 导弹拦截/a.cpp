#include<iostream>
#include <cstdlib>
#include <cstdio>
#include<vector>
#include <algorithm>
using namespace std;
vector<int> b,c;
int a[100010],f1[100010],f2[100010],bb[100010],cc[100010];
int i=1,n=0,t;
int main()
{
	freopen("input","r",stdin);
    while(cin>>a[++n])
	b.push_back(a[n]); 
	for(i=n-1;i>=1;i--)						//倒着找
	{
		t=upper_bound(b.begin(),b.end(),a[i])-b.begin();		//它在比它大的前面 
		f1[i]=bb[b[t-1]]+1;							//这个也要算入 
		bb[a[i]]=f1[i];
		b.insert(b.begin()+t-1,a[i]);		//插它前面 
	}
	cout<<f1[1]<<endl;
	c.push_back(a[1]);
	for(i=1;i<=n;i++) 
	{
		t=upper_bound(c.begin(),c.end(),a[i])-c.begin();		//它在比它大的前面 
		f2[i]=cc[c[t-1]]+1;							//这个也要算入 
		cc[a[i]]=f2[i];
		c.insert(c.begin()+t-1,a[i]);		//插它前面 
	}
	cout<<f2[n];
	return 0;
}