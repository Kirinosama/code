#include <cstdlib>
#include <cstdio>
#include <cstring>
#include <iostream>
#include <algorithm>
#include <queue>
using namespace std;

struct node{
	int cnt;
	node *to[27],*fail;
	node(){for(int i=1;i<=26;i++)to[i]=NULL;fail=NULL,cnt=0;}
};

struct trie{
	node* root;
	trie(){root=new node;}
	void insert(){
		string s1;
		cin>>s1;node *cur=root;
		for(int i=0;i<s1.length();i++){
			int c=s1[i]-'a'+1;
			if(!cur->to[c]) cur->to[c]=new node;
			cur=cur->to[c];
		}
		cur->cnt++;
	}	
	void build(){
		queue <node*> q;
		for(int i=1;i<=26;i++)if(root->to[i])
			root->to[i]->fail=root,q.push(root->to[i]);
		while(!q.empty()){
			node* cur=q.front();q.pop();
			for(int i=1;i<=26;i++){
				if(cur->to[i]) cur->to[i]->fail=cur->fail->to[i]?cur->fail->to[i]:root,q.push(cur->to[i]);
				else cur->to[i]=cur->fail->to[i];
			}
		}
	}
	void comp(string s){
		node* cur=root;int ans=0;
		for(int i=0;i<s.length();i++){
			int c=s[i]-'a'+1;
			cur=cur->to[c]?cur->to[c]:root;
			while(cur!=root && cur->cnt){
				ans+=cur->cnt;cur->cnt=0;cur=cur->fail;
			}
		}
		cout<<ans;
	}
}t;

int n;
string s;

int main(){
	freopen("acmachine.in","r",stdin);
	cin>>n;
	for(int i=1;i<=n;i++)t.insert();
	t.build();cin>>s;
	t.comp(s);
	return 0;
}
