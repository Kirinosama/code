#include <cstdlib>
#include <cstdio>
#include <iostream>
#include <ctime>
using namespace std;

const int INF=1e8;

int x,y,z; 
float a,b,c;

int main()
{
	cin>>x;
	int flag=0;
	for(int i=2;i<x;i++)
	{
		if(x%i==0)
		{
			cout<<i<<endl;
			z=z+1;
			flag=1;
		}
	}

	if(flag==0) cout<<"Yes";
	if(flag==1){ cout<<"No";
cout<<z;}
	return 0;
}
