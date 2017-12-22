#include <cstdlib>
#include <cstdio>
#include <cstring>
#include <iostream>
using namespace std;

#define MAXN 200
int num[300],ll,flag;

char s[MAXN];


void dfs(int x)
{
	int cant[5];
	cant[1]=cant[2]=cant[3]=cant[4]=0;
	if(x==ll+1)
	{
		printf("%d %d %d %d",num['R'],num['B'],num['Y'],num['G']);
		flag=1;
		return;
	}
	if(x==0)
	{
		num['R']=num['B']=num['Y']=num['G']=0;
	}
	if(s[x]!='!')
	{
		dfs(x+1);
		return;
	}
	for(int i=1;i<=3;i++)
	{
		if(x+i<=ll && s[x+i]!='!')
		{
			if(s[x+i]=='R')
				cant[1]=1;
			if(s[x+i]=='B')
				cant[2]=1;
			if(s[x+i]=='Y')
				cant[3]=1;
			if(s[x+i]=='G')
				cant[4]=1;
		}
		if(x-i>=0 && s[x-i]!='!')
		{
			if(s[x-i]=='R')
				cant[1]=1;
			if(s[x-i]=='B')
				cant[2]=1;
			if(s[x-i]=='Y')
				cant[3]=1;
			if(s[x-i]=='G')
				cant[4]=1;
		}	
	}
	if(!cant[1])
	{
		s[x]='R';
		num['R']++;
		dfs(x+1);
		if(flag)
			return;
		num['R']--;
		s[x]='!';
	}
	if(!cant[2])
	{
		s[x]='B';
		num['B']++;
		dfs(x+1);
		if(flag)
			return;
		num['B']--;
		s[x]='!';
	}
	if(!cant[3])
	{
		s[x]='Y';
		num['Y']++;
		dfs(x+1);
		if(flag)
			return;
		num['Y']--;
		s[x]='!';
	}
	if(!cant[4])
	{
		s[x]='G';
		num['G']++;
		dfs(x+1);
		if(flag)
			return;
		num['G']--;
		s[x]='!';
	}
}

int main()
{
	freopen("input","r",stdin);
	cin>>s;
	ll=strlen(s)-1;
	dfs(0);
	return 0;
}