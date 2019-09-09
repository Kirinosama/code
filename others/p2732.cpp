#include <iostream>
#include <cstdio>
#include <cstring>
using namespace std;

int f[6][6][6][6][6];
int a[1000];
int d[6];
int len=0;

int num[6];
int qian[6];

int main()
{
//	freopen("input","r",stdin);
	memset(f,0x3f,sizeof(f));
	int s,n,k,p,b,c;
	cin>>s;
	for(int i=1;i<=s;i++)
	{
		memset(d,0,sizeof(d));
		cin>>n;
		int num;
		for(int j=1;j<=n;j++)
		{
			cin>>b;
			if(a[b]==0)
			{
				len++;
				a[b]=len;
			}
			cin>>d[a[b]];
		}
		cin>>num;
		f[d[1]][d[2]][d[3]][d[4]][d[5]]=num;
	}
	cin>>b;
	for(int i=1;i<=b;i++)
	{
		cin>>c>>k>>p;
		if(a[c]==0)
		{
			len++;
			a[c]=len;
		}
		int x=a[c];
		num[x]=k;
		qian[x]=p;
	}
	f[0][0][0][0][0]=0;
	f[1][0][0][0][0]=min(f[1][0][0][0][0],qian[1]);
	f[0][1][0][0][0]=min(f[0][1][0][0][0],qian[2]);
	f[0][0][1][0][0]=min(f[0][0][1][0][0],qian[3]);
	f[0][0][0][1][0]=min(f[0][0][0][1][0],qian[4]);
	f[0][0][0][0][1]=min(f[0][0][0][0][1],qian[5]);
	for(int A=0;A<=num[1];A++)
		for(int B=0;B<=num[2];B++)
			for(int C=0;C<=num[3];C++)
				for(int D=0;D<=num[4];D++)
					for(int E=0;E<=num[5];E++)		
						for(int a=0;a<=A;a++)
							for(int b=0;b<=B;b++)
								for(int c=0;c<=C;c++)
									for(int d=0;d<=D;d++)
										for(int e=0;e<=E;e++)
											f[A][B][C][D][E]=min(f[A][B][C][D][E],f[A-a][B-b][C-c][D-d][E-e]+f[a][b][c][d][e]);
	cout<<f[num[1]][num[2]][num[3]][num[4]][num[5]];
	return 0;
}
