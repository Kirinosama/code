#include <cstdlib>
#include <cstdio>
#include <cstring>
#include <iostream>
#include <algorithm>
#include <ctime>
using namespace std;

#define MAXN 50010

int n,st,x,val,ne,res,ne_res;
int s[MAXN];
int v[MAXN],nex[MAXN];

int main()
{
	//freopen("input","r",stdin);
	srand(time(0)+519);
	scanf("%d %d %d",&n,&st,&x);

//	for(int i=1;i<=n;i++)
//		scanf("%d %d",&v[i],&nex[i]);

	printf("? %d\n",st);fflush(stdout);
	scanf("%d %d",&val,&ne);
	//val=v[st]; ne=nex[st]; 
	
	if(x<=val)
	{
		printf("! %d",val);
		fflush(stdout);
		return 0;
	}
	for(int i=1;i<=n;i++) s[i]=i;
		random_shuffle(s+1,s+1+n);
	for(int i=1;i<=min(n,1000);i++)
	{
		int ask=s[i];
		printf("? %d\n",ask);fflush(stdout);
		scanf("%d %d",&val,&ne);
	//	val=v[ask]; ne=nex[ask];

		if(val<=x)
		{
			if(val>res)
			{
				res=max(res,val);
				ne_res=ne;
			}
		}
	}
	if(!res)
	{
		printf("? %d\n",st);
		fflush(stdout);
		scanf("%d %d",&res,&ne_res);
	}
	if(res==x)
	{
		printf("! %d",res);
		fflush(stdout);
		return 0;
	}
	while(ne_res!=-1 && res<x)
	{
		printf("? %d\n",ne_res);fflush(stdout);
		scanf("%d %d",&val,&ne);
		//val=v[ne_res]; ne=nex[ne_res];
		res=val;ne_res=ne;
	}
	if(res>=x)
	{
		printf("! %d",res);
		fflush(stdout);
		return 0;
	}
	else printf("! -1");
	fflush(stdout);
	return 0;
}