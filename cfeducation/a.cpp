#include <cstdlib>
#include <cstdio>
#include <cstring>
#include <iostream>
#include <algorithm>
using namespace std;

int len,cnt;
char s[20],a[20];

bool check(char *a)
{
	for(int i=1;i<=len;i++)
		if(a[i]!=a[len-i+1])
			return false;
	return true;
}

int main()
{
	freopen("input","r",stdin);
	scanf("%s",s);
	len=strlen(s);
	for(int i=len-1;i>=0 && s[i]=='0';i--)
		cnt++;
	for(int i=0;i<len && s[i]=='0';i++)
		cnt--;
	for(int i=1;i<=cnt;i++) a[i]='0';
	for(int i=0;i<len;i++) a[cnt+i+1]=s[i];
	len=cnt+len;
	if(check(a)) printf("YES");
	else printf("NO");
	return 0;
}