#include <cstdlib>
#include <cstdio>
#include <cstring>
#include <vector>
#include <queue>
#include <iostream>
using namespace std;

const int MOD=10007;

#define MAXN 6010

struct node
{
	int id;
	int cnt;
	node* fail;
	node* to[27];
};

node* root;

int n,m,id_cnt,ans;
int f[110][6010],res;
char s[10010];
node * S[MAXN];

queue <node*> Q;
vector <char> v;

void newnode(node*& p)
{
	p=new node;
	p->cnt=0;
	p->fail=NULL;
	for(int i=0;i<=26;i++)
		p->to[i]=NULL;
	p->id=++id_cnt;
	S[id_cnt]=p;
}

void dfs(node* p,char *s,int pos)
{
	if(pos>=strlen(s))
		return;
	int num=s[pos]-'A'+1;
	if(!p->to[num])
		newnode(p->to[num]);
	if(pos==strlen(s)-1)
		p->to[num]->cnt++;
	dfs(p->to[num],s,pos+1);
}

void getfail(node* p)
{
	Q.push(root);
	while(!Q.empty())
	{
		node* tp=Q.front();
		Q.pop();
		for(int i=1;i<=26;i++)
			if(tp->to[i])
			{
				if(tp==root)
					tp->to[i]->fail=root;
				else
				{
					node* tmp=tp->fail;
					while(tmp && !tmp->to[i])
						tmp=tmp->fail;
					if(!tmp) tp->to[i]->fail=root;
					else tp->to[i]->fail=tmp->to[i];
				}
				Q.push(tp->to[i]);
			}
	}
}

int main()
{
	freopen("input","r",stdin);
	scanf("%d %d",&n,&m);
	newnode(root);
	for(int i=1;i<=n;i++)
	{
		scanf("%s",s);
		dfs(root,s,0);
	}
	getfail(root);
	f[0][1]=1;
	for(int i=0;i<m;i++)
	{
		for(int j=1;j<=id_cnt;j++)
		{
			node* cur=S[j];
			if(cur->cnt) continue;
			for(int k=1;k<=26;k++)
				if(cur->to[k])
					f[i+1][cur->to[k]->id]=(f[i+1][cur->to[k]->id]+f[i][j])%MOD;
		}
	}
	res=1;
	for(int i=1;i<=m;i++)
		res=(res*26)%MOD;
	for(int i=2;i<=id_cnt;i++)
		if(!S[i]->cnt)
			ans=(ans+f[m][i])%MOD;
	printf("%d",(res+MOD-ans)%MOD);`````````````````````````
	return 0;	
}
