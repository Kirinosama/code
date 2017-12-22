#include <cstdlib>
#include <cstdio>
#include <cstring>
#include <iostream>
#include <algorithm>
#include <queue>
using namespace std;

string s;
int ans,n;

struct trie{
	struct node{
		node *to[27];
		node *fail;
		int cnt;
	}*root;

	void newnode(node *&p){
		p=new node;
		p->cnt=0;p->fail=NULL;
		for(int i=1;i<=26;i++) p->to[i]=NULL;
	}

	void insert(string s){
		node *cur=root;
		for(int i=0;i<s.length();i++){
			int num=s[i]-'a'+1;
			if(!cur->to[num]) newnode(cur->to[num]);
			cur=cur->to[num];
			if(i==s.length()-1) cur->cnt++;
		}
	}

	void get_fail(){
		queue <node*> Q;
		for(int i=1;i<=26;i++)
			if(root->to[i]){
				root->to[i]->fail=root;
				Q.push(root->to[i]);
			}
		while(!Q.empty()){
			node *cur=Q.front();Q.pop();
			for(int i=1;i<=26;i++){
				if(cur->to[i]){
					cur->to[i]->fail=cur->fail->to[i];
					if(cur->to[i]->fail==NULL) cur->to[i]->fail=root;
					Q.push(cur->to[i]);
				}
				else cur->to[i]=cur->fail->to[i];
			}
		}
	}

	void solve(string s){
		node *cur=root;
		for(int i=0;i<s.length();i++){
			int num=s[i]-'a'+1;
			cur=cur->to[num];
			if(!cur) cur=root;
			for(node *i=cur;i!=root && i->cnt!=-1;i=i->fail){
				ans+=i->cnt;
				i->cnt=-1;
			}
		}
		cout<<ans;
	}
}t;

int main(){
	freopen("input","r",stdin);
	cin>>n;t.newnode(t.root);
	for(int i=1;i<=n;i++)
		cin>>s,t.insert(s);
	t.get_fail();
	cin>>s;t.solve(s);
	return 0;
}
