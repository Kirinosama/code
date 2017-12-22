#include <cstdlib>
#include <cstdio>
#include <cstring>
#include <iostream>
#include <cmath>
#include <algorithm>
using namespace std;

char s[6010],len;

int yuan(char c)
{
	if(c=='a' || c=='e' || c=='i' || c=='o' || c=='u') return 1;
	return 0;
}

void print(int pos)
{
	if(pos>=len) return;
	if(pos>=len-2)
	{
		for(int i=pos;i<len;i++)
			printf("%c",s[i]);
		return;
	}
	if(yuan(s[pos]))
	{
		printf("%c",s[pos]);
		print(pos+1);
		return;
	}
	if(yuan(s[pos+1]))
	{
		printf("%c%c",s[pos],s[pos+1]);
		print(pos+2);
		return;
	}
	printf("%c%c",s[pos],s[pos+1]);
	if(pos+2==len) return;
	if(yuan(s[pos+2]))
	{
		print(pos+2);
		return;
	}
	if(s[pos]==s[pos+1])
	{
		char c=s[pos];
		pos=pos+2;
		while(s[pos]==c && pos<len)
		{
			printf("%c",s[pos]);
				pos++;
		}
		if(pos<len)
		{
			if(!yuan(s[pos])) 
				printf(" ");
			print(pos);
		}
		return;
	}
	else 
	{
		printf(" ");
		print(pos+2);
		return;
	}
}

int main()
{
	freopen("input","r",stdin);
	scanf("%s",s);
	len=strlen(s);
	print(0);
	return 0;
}
