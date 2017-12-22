#include <cstdlib>
#include <cstdio>
#include <cstring>
#include <iostream>
#include <algorithm>
using namespace std;

#define MAXN 10010
#define ii pair<int,int>
#define INF 0x3f3f3f3f
typedef long long ll;

int n,m,f[MAXN],fa[MAXN],ans,ne[MAXN];
char s[MAXN];
char word[1010];

struct trie{
	struct node{
		int cnt;
		node *to[27];
	}*root;
	void newnode(node *&p){
		p=new node;p->cnt=0;
		for(int i=1;i<=26;i++)
			p->to[i]=NULL;
	}
	void insert(char s[]){
		node *p=root;
		for(int i=0;i<strlen(s);i++){
			int k=s[i]-'a'+1;
			if(!p->to[k])
				newnode(p->to[k]);
			p=p->to[k];
		}
		p->cnt++;
	}
	void dp(int x){
		if(!f[x]) return;
		node *cur=root;
		for(int i=x+1;i<=n;i++){
			int k=s[i]-'a'+1;
			if(!cur->to[k]) return;
			cur=cur->to[k];
			if(cur->cnt){
				f[i]=1;
				fa[i]=x;
			}
		}
	}
}t;

char change(char p){
	if(p>='A' && p<='Z')
		return p-'A'+'a';
	else return p;
}

void solve(char *cur){
	char tmp[1010];
	for(int i=0;i<strlen(cur);i++)
		tmp[i]=change(cur[strlen(cur)-1-i]);
	for(int i=0;i<strlen(cur);i++)
		cur[i]=tmp[i];
}

int main(){
    freopen("cf633c.in","r",stdin);
    t.newnode(t.root);
    scanf("%d\n",&n);
    for(int i=1;i<=n;i++)
    	scanf("%c",&s[i]);
    scanf("%d",&m);
    for(int i=1;i<=m;i++){
    	scanf("%s",word);
    	solve(word);
    	t.insert(word);
    }
    f[0]=1;
    for(int i=0;i<n;i++)
    	t.dp(i);
    for(int i=n;i;i=fa[i])
    	ne[fa[i]]=i;
    for(int i=0;i!=n;i=ne[i]){
    	for(int j=ne[i];j>=i+1;j--)
    		printf("%c",s[j]);
    	if(ne[i]!=n) printf(" ");
    }
    return 0;
}