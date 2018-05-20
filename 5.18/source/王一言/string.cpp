#include<bits/stdc++.h>
using namespace std;

int cal(int n)
{
	int x=(sqrt(8ll*n+1)-1)/2;
	if(1ll*x*(x+1)/2<n) x++;
	x++;
	return x;
}

int main()
{
	freopen("string.in","r",stdin);
	freopen("string.out","w",stdout);
	int m,t,n,x,y,tot,a,p;
	cin>>t;
	while(t--)
	{
		scanf("%d",&n);
		a='1';
		m=cal(n);
	//	cout<<"M "<<m<<endl;
		x=1ll*(m-1)*m/2-n;
	//	cout<<"X "<<x<<endl;
		tot=0;
	//	printf("%d",a);
	/*	tot=1;
		if(x!=0) 
		{
			x--;
			tot++;
			printf("%d",a);
		}*/
		while(x)
		{
			a=!a;
		//	if(a=='0') a='1';
		//	else a='0';
			//a=='0'?a='0':a='1';
			y=cal(x);
			while(1ll*y*(y-1)/2>x) y--;
		//	cout<<"P "<<y<<" "<<x<<endl;
			for(int i=1;i<=y;i++) putchar(a+'0');//printf("%d",a);
			x-=1ll*y*(y-1)/2;
			tot+=y;
		}
		//cout<<"A "<<tot<<" "<<m<<endl;
		for(int i=tot+1;i<=m;i++) 
		{
			a=!a;
			//if(a=='0') a='1';
			//else a='0';
			//a=(a=='0'?'0':'1');
		//	a=='0'?a='0':a='1';
		//	printf("%d",a);
			putchar(a+'0');
		}
	//	printf(" %d",n);
	//	printf("\n");
		putchar('\n');
	}
	return 0;
}

