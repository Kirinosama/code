#include <cstdlib>
#include <cstdio>
#include <cstring>
#include <iostream>
#include <algorithm>
#include <vector>
using namespace std;

#define MAXN 1000010
#define MAXM 2*MAXN

int n,m,t,cnt;
int to[MAXM],cannot[MAXM],flag;
vector <int> must[MAXM];

struct node{
	int len;
	vector <int> s;
	void in(){
		scanf("%d",&len);s.clear();
		for(int i=1;i<=len;i++){
			scanf("%d",&t);
			s.push_back(t+n);
		}
	}
}word[MAXN];

bool dfs(int x){
	if(cannot[x]) return false;
	for(int i=0;i<must[x].size();i++)
		if(dfs(must[x][i])==false)
			return false;
	if(x>n && to[x]==x){
		to[x]-=n;
		cnt++;
	}
	return true;
}

void solve(int x){
	node &word1=word[x];
	node &word2=word[x+1];
	for(int i=0;i<min(word1.len,word2.len);i++){
		int &p=word1.s[i];
		int &q=word2.s[i];
		p=to[p];q=to[q];
		if(p<q){
			if(cannot[p]) cannot[q]=1;
			if(p>q-n) must[q].push_back(p);
			return;
		}
		else if(p==q) continue;
		else{
			if(!cannot[p]){
				if(p<=n){
					flag=1;return;
				}
				else{
					if(dfs(p)){
						p=to[p];
						cannot[q]=1;
						return;
					}
					else{
						flag=1;return;
					}
				}
			}
			else{
				flag=1;return;
			}
		}
	}
	if(word2.len<word1.len)	flag=1;
	return;
}

//两种bug 必须修改不能改的 和 b为a的前缀

void init(){
	for(int i=1;i<=n;i++) to[i]=i,cannot[i]=1;
	for(int i=n+1;i<=2*n;i++) to[i]=i;
}

int main()
{
	freopen("input","r",stdin);
	cin>>n>>m;
	init();
	for(int i=1;i<=n;i++){
		word[i].in();
	}
	for(int i=1;i<n;i++){
		solve(i);
		if(flag) break;
	}
	if(flag) cout<<"No";
	else{
		cout<<"Yes"<<endl<<cnt<<endl;
		for(int i=n+1;i<=2*n;i++) 
			if(to[i]!=i) cout<<i-n<<' ';
	}
	return 0;
}