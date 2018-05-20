#include<bits/stdc++.h>
using namespace std;

const int N=1200005;

int tot,ans[N],num[N],sum[N];

struct node
{
	int c[12],next;
}tree[N];

vector<int> V[N];

void insert(int id,string s,int len)
{
	int u=0;
	//for(int i=0;i<len;i++) cout<<s[i];
//	cout<<endl;
	for(int i=0;i<len;i++)
	{
		if(!tree[u].c[s[i]-'0']) tree[u].c[s[i]-'0']=++tot;
		u=tree[u].c[s[i]-'0'];
	}
	V[u].push_back(id);
	return ;
}

void build()
{
	queue<int> Q;
	for(int i=0;i<10;i++)
	{
		int v=tree[0].c[i];
		if(v) 
		{
			tree[v].next=0;
			Q.push(v);
		}
	}
	while(!Q.empty())
	{
		int u=Q.front();
		Q.pop();
		for(int i=0;i<10;i++)
		{
			int v=tree[u].c[i];
			if(v)
			{
				Q.push(v);
				tree[v].next=tree[tree[u].next].c[i];
			}
			else tree[u].c[i]=tree[tree[u].next].c[i];
		}
	}
	return ;
}

int query(string s)
{
	int len=s.length(),u=0,v,res=0;
//	for(int i=0;i<len;i++) cout<<s[i];
//	cout<<endl;
	for(int i=0;i<len;i++)
	{
		if(u&&!tree[u].c[s[i]-'0']) u=tree[u].next;
		u=tree[u].c[s[i]-'0'];
		v=u;
		while(v&&V[v].size())
		{
		//	cout<<"YES "<<v<<" "<<s[i]<<" "<<V[v].size()<<" "<<num[i]<<endl;
		//	for(int )
		//	ans[tree[v].i]=num[i];
		//	tree[v].i=-1;
			for(int j=0;j<V[v].size();j++) ans[V[v][j]]=num[i];
			V[v].clear();
			v=tree[v].next;
		}
	}
	return res;
}

char s[N],c[N];

int main()
{
	freopen("number.in","r",stdin);
	freopen("number.out","w",stdout);
	int t,n,len;
	cin>>t;
	for(int i=1;i<=t;i++)
	{
		scanf("%d",&sum[i]);
		n=sum[i];
		len=0;
		while(n)
		{
			s[len++]=n%10+'0';
		//	cout<<n%10<<" "<<s[len]<<endl;
			n/=10;
		}
		for(int j=0;len-j-1>j;j++) swap(s[j],s[len-j-1]);
		//for(int j=0;j<len;j++) cout<<s[j];
	//	cout<<endl;
		insert(i,s,len);
	}
//	int u=0;
//	int v=tree[u].c[2];
//	cout<<V[v].size()<<endl;
	build();
//	cout<<"YES"<<endl;
	len=0;
	for(int i=1;i<=200000;i++)
	{
		int n=i,l=len;
		while(n)
		{
			c[len++]=n%10+'0';
			n/=10;
		}
	//	cout<<"P "<<l<<" "<<len<<endl;
		for(int j=l;len-j+l-1>j;j++) swap(c[j],c[len-j+l-1]);
		for(int j=l;j<len;j++) num[j]=i;
	}
//	for(int i=0;i<len;i++) cout<<num[i]<<" ";
//	cout<<endl;
//	for(int i=1;i<=tot;i++) cout<<V[i].size()<<" ";
//	cout<<endl;
	query(c); 
	for(int i=1;i<=t;i++) 
	{
		if(sum[i]!=0&&sum[i]<ans[i]) printf("%d\n",sum[i]);
		else printf("%d\n",ans[i]);
	}
	return 0;
}

