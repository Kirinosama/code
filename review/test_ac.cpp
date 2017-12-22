#include <cstdlib>
#include <cstdio>
#include <cstring>
#include <iostream>
#include <algorithm>
#include <queue>
using namespace std;

string s;
int n;

struct trie{
	struct node{
		node *to[27];
		node *fail;
		int cnt;
	}*root;

	void newnode(node *&p){
		p=new node;
		p->cnt=0;
		for(register int i=1;i<=26;i++) 
			p->to[i]=NULL;
		p->fail=NULL;
	}

	void insert(string s){
		node *cur=root;
		for(register int i=0;i<s.length();i++){
			int num=s[i]-'a'+1;
			if(!cur->to[num]) newnode(cur->to[num]);
			cur=cur->to[num];
			if(i==s.length()-1) cur->cnt++;
		}
	}

	void get_fail(){
		queue <node*> Q;
		root->fail=root;
		for(register int i=1;i<=26;i++)
			if(root->to[i]){
				root->to[i]->fail=root;
				Q.push(root->to[i]);
			}
		while(!Q.empty()){
			node *cur=Q.front();Q.pop();
			for(register int i=1;i<=26;i++){
				if(!cur->to[i]){
					cur->to[i]=cur->fail->to[i];
				}
				else{
					Q.push(cur->to[i]);
					cur->to[i]->fail=cur->fail->to[i];
					if(!cur->to[i]->fail)
						cur->to[i]->fail=root;
				}
			}
		}
	}

	void solve(string s){
		node *cur=root;int ans=0;
		for(register int i=0;i<s.length();i++){
			int num=s[i]-'a'+1;
			cur=cur->to[num];
			if(!cur) cur=root;
			for(node* j=cur;j!=root && j->cnt!=-1;j=j->fail){
				ans+=j->cnt;
				j->cnt=-1;
			}
		}
		cout<<ans;
	}
}t;

int main(){
	freopen("input","r",stdin);
	cin>>n;t.newnode(t.root);
	for(register int i=1;i<=n;i++){
		cin>>s;t.insert(s);
	}
	t.get_fail();
	cin>>s;t.solve(s);
	return 0;
}