#include <cstdlib>
#include <cstdio>
#include <cstring>
#include <iostream>
#include <algorithm>
#include <vector>
#include <queue>
using namespace std;

#define MAXN 100010

int T,to[MAXN][11],nodecnt,fail[MAXN],ans[MAXN];
int wh[2000010],len;
string s;
vector <int> book[MAXN];

struct machine{
	int rt;
	void insert(string str,int ID){
		int now=rt;
		for(int i=0;i<str.length();i++){
			if(!to[now][str[i]-'0']) to[now][str[i]-'0']=++nodecnt;
			now=to[now][str[i]-'0'];
		}
		book[now].push_back(ID);
	}
	void getfail(){
		queue <int> Q;
		for(int i=0;i<=9;i++)if(to[rt][i])
			Q.push(to[rt][i]);
		while(!Q.empty()){
			int tp=Q.front();Q.pop();
			for(int i=0;i<10;i++){
				if(!to[tp][i]) to[tp][i]=to[fail[tp]][i];
				else fail[to[tp][i]]=to[fail[tp]][i],Q.push(to[tp][i]);
			}
		}
	}
	void make(string s){
		int now=0;
		for(int i=0;i<s.length();i++){
			int k=s[i]-'0';
			now=to[now][k];
			for(int &j=now;j && !book[j].empty();j=fail[j]){
				for(int l=0;l<book[j].size();l++) ans[book[j][l]]=wh[i];
				book[j].clear();
			}
		}
	}
}ac;

int main(){
	freopen("number.in","r",stdin);
	freopen("number.out","w",stdout);
	cin>>T;string str;
	ac.rt=0;
	for(int i=1;i<=T;i++){
		cin>>str;ac.insert(str,i);
	}
	ac.getfail();
	string s1;
	for(int i=200000;i>=1;i--){
		for(int j=i;j;j/=10){
			s1.push_back(j%10+'0');len++;
			wh[1088895-len]=i;
		}
	}
	for(int i=s1.length()-1;i>=0;i--)
		s.push_back(s1[i]);
	ac.make(s);
	for(int i=1;i<=T;i++)printf("%d\n",ans[i]);
	return 0;
}
