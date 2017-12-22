#include <cstdlib>
#include <cstdio>
#include <cstring>
#include <iostream>
#include <algorithm>
using namespace std;

int len,n,book[50],cnt;
char s[2000];

int main()
{
	freopen("input","r",stdin);
	scanf("%s",s);
	len=strlen(s);
	for(int i=0;i<len;i++)
	{
		book[s[i]-'a'+1]++;
		if(book[s[i]-'a'+1]==1) cnt++;
	}
	scanf("%d",&n);
	if(len<n) printf("impossible");
	else if(cnt<=n) printf("%d",n-cnt);
	else cout<<0;
	return 0;
}