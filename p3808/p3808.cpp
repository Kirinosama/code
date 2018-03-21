#include <cstdlib>
#include <cstdio>
#include <cstring>
#include <iostream>
#include <algorithm>
#include <queue>
using namespace std;

#define MAXN 1000010
#define ii pair<int,int>
#define INF 0x3f3f3f3f
typedef long long ll;

int n;
string str[MAXN];

struct node{
	node *to[27],*fail;
	int cnt;
	node(){for(int i=0;i<=26;i++)to[i]=NULL;fail=NULL;cnt=0;}
}*root;

struct trie{
	node *root;
	void insert(string s){
		node *p=root;
		for(int i=0;i<s.length();i++){
			int c=s[i]-'a'+1;
			if(!p->to[c])p->to[c]=new node;
			p=p->to[c];
		}
		p->cnt++;
	}
	void premake(){
		queue <node*> Q;
		for(int i=1;i<=26;i++)if(root->to[i])
			root->to[i]->fail=root,Q.push(root->to[i]);
		while(!Q.empty()){
			node *tp=Q.front();Q.pop();
			for(int i=1;i<=26;i++){
				if(tp->to[i]) tp->to[i]->fail=tp->fail->to[i],Q.push(tp->to[i]);
				else tp->to[i]=tp->fail->to[i];
			}
		}
	}
	int solve(){
		string s;int ans=0;
		cin>>s;
		node *p=root;
		for(int i=0;i<s.length();i++){
			int c=s[i]-'a'+1;
			p=p->to[c]?p->to[c]:root;
			for(node *cur=p;cur->cnt && cur!=root;cur=cur->fail) ans+=cur->cnt,cur->cnt=0;
		}
		return ans;
	}
}t;

int main(){
    freopen("p3808.in","r",stdin);
    cin>>n;t.root=new node;
    for(int i=1;i<=n;i++){
    	cin>>str[i];
    	t.insert(str[i]);
    }
   	t.premake();
   	cout<<t.solve();
    return 0;
}