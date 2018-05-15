#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<algorithm>
#include<cstring>
#include<cmath>
#include<ctime>
#define inf 0x7fffffff
#define ll long long
using namespace std;
int main()
{
	freopen("harem4.in","w",stdout);
    srand(time(0));
    int n=10000,m=10000,c=1000;
    cout<<n<<' '<<c<<' '<<m<<endl;
    for(int i=1;i<=n;i++)
        cout<<rand()%c+1<<' ';
    cout<<endl;
    for(int i=1;i<=m;i++)
    {
    	int x=rand()%n+1,y=rand()%n+1;
    	if(x>y)swap(x,y);
    	cout<<x<<' '<<y<<endl;
    }
	return 0;
}

