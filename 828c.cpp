#include <cstdlib>
#include <cstring>
#include <iostream>
#include <vector>
#include <cstdio>
using namespace std;

#define MAXN 1000010
#define MAXM 100010

struct node
{
	int cover;
	node* ls;
	node* rs;
};

node * root;
int n,m,maxl,w;
char ans[2*MAXN];
string word[MAXM];
vector <int> s[MAXN];

void newnode(node*& p)
{
	if(!p)
	{
		p=new node;
		p->ls=p->rs=NULL;
		p->cover=0;
	}
}

void insert(node*&p,int L,int R,int l,int r,string w)
{
	if(p->cover) return;
	if(L>=l && R<=r)
	{
		if(!p->cover)
		{
			p->cover=1;
			for(int i=L;i<=R;i++)
				ans[i]=w[i-l];
		}
		return;
	}
	if(L>r || R<l) return;
	else if(L!=R)
	{
		int mid=(L+R)/2;
		newnode(p->ls); newnode(p->rs);
		p->ls->cover+=p->cover;
		p->rs->cover+=p->cover;
		p->cover=0;
		insert(p->ls,L,mid,l,r,w);
		insert(p->rs,mid+1,R,l,r,w);
	}
}

int main()
{
	freopen("input","r",stdin);
	scanf("%d",&n);
	for(int i=1;i<=n;i++)
	{
		scanf("\n");
		cin>>word[i];
		int l=word[i].length();
		scanf("%d",&m);
		for(int j=1;j<=m;j++)
		{
			scanf("%d",&w);
			s[i].push_back(w);
			maxl=max(maxl,w+l-1);
		}
	}
	newnode(root);
	for(int i=1;i<=n;i++)
	{
		int l=word[i].length();
		for(int j=0;j<s[i].size();j++)
		{
			if(j+1!=s[i].size()) insert(root,1,maxl,s[i][j],min(s[i][j]+l-1,s[i][j+1]-1),word[i]);
			else insert(root,1,maxl,s[i][j],s[i][j]+l-1,word[i]);
		}
	}
	for(int i=1;i<=maxl;i++)
	{
		if(ans[i]) printf("%c",ans[i]);
		else printf("a");
	}
	return 0;
}