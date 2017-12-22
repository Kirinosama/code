#include <cstdlib>
#include <cstdio>
#include <cstring>
#include <vector>
#include <iostream>
using namespace std;

#define MAXN 20
#define MAXM 1000010

char s[MAXN];
int n,m,dp[MAXM];
vector <char> v;

struct node
{
	int cnt;
	node* to[30];
	void clr(){
		cnt=0;
		for(int i=0;i<30;i++) to[i]=NULL;
	}
}*root;

void newnode(node*&p)
{
	p=new node;
	p->clr();
}

void add(node*p,char *s)
{
	int l=strlen(s);
	for(int i=0;i<l;i++)
	{
		if(!p->to[s[i]-'a'+1])
			newnode(p->to[s[i]-'a'+1]);
		p=p->to[s[i]-'a'+1];
	}
	p->cnt++;
}

void solve()
{
	string s1;
	cin>>s1;
	memset(dp,0,sizeof(dp));dp[0]=1;
	for(int i=0;i<s1.length();i++)
	{
		if(!dp[i]) continue;
		node* p=root;
		for(int j=i;j<s1.length();j++)
		{
			int k=s1[j]-'a'+1;
			if(p->to[k])
			{
				p=p->to[k];
				if(p->cnt)	dp[j+1]=1;
			}
			else break;
		}
	}
	for(int i=s1.length();i>=0;i--)
		if(dp[i])
		{
			printf("%d\n",i);
			return;
		}
}

void print(node* p)
{
	if(p->cnt)
	{
		for(int i=0;i<v.size();i++)
			printf("%c",v[i]);
		cout<<endl;
	}
	for(int i=1;i<=26;i++)
	{
		if(p->to[i])
		{
			v.push_back(i+'a'-1);
			print(p->to[i]);
			v.pop_back();
		}
	}
}

int main()
{
	freopen("input","r",stdin);
	scanf("%d %d\n",&n,&m);
	newnode(root);
	for(int i=1;i<=n;i++)
	{
		scanf("%s\n",s);
		add(root,s);
	}
	for(int i=1;i<=m;i++)
		solve();
	return 0;
}