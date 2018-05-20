#include<bits/stdc++.h>
using namespace std;

const int N=455;

int n,d,a,b,x[N],y[N],ans=0x7f7f7f7f;
bool had[N],vis[N];

void DFS(int i)
{
	if(i==n+1)
	{
		for(int i=1;i<=n;i++) y[i]=x[i];
		sort(y+1,y+n+1);
		//for(int i=1;i<=n;i++) cout<<y[i]<<" ";
		//cout<<endl;
		int res=a;
		for(int i=2;i<=n;i++) res=res+min(a,b*(y[i]-y[i-1]));
		ans=min(res,ans);
		return ;
	}
	DFS(i+1);
	x[i]+=2*d;
	DFS(i+1);
	x[i]-=2*d;
	return ;
}

int main()
{
	freopen("point.in","r",stdin);
	freopen("point.out","w",stdout);
	int m=0;
	cin>>n>>d>>a>>b;
	for(int i=1;i<=n;i++) cin>>x[i];
	if(n<=20)
	{
		DFS(1);
		cout<<ans;
		return 0;
	}
	//cout<<"YES"<<endl;
		ans=0;
		sort(x+1,x+n+1);
		for(int i=1;i<=n;i++)
		{
			if(x[i]!=x[i-1]) 
			{
				x[++m]=x[i];
				had[x[m]]=true;
			}
		}
		for(int i=1;i<=m;i++)
		{
			if(!vis[x[i]]&&had[x[i]+2*d]) vis[x[i]+2*d]=true;
			else ans+=a;
		}
		cout<<ans;
	return 0;
}

