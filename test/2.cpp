#include<bits/stdc++.h>
#define maxn 205
#define inf 0x3f3f3f3f
using namespace std;
int f[205][205]; 
struct node{
	int to;
	int next;
}e[maxn];
int cnt,head[maxn];
int du[maxn];
int w[maxn];
int n,m;
void add(int u,int v){
	e[++cnt].to=v;
	e[cnt].next=head[u];
	head[u]=cnt;
} 
int num[maxn];
map<string,int> fw;
void dfs(int u){
	f[u][0]=0;
	num[u]=1;
	for(int i=head[u];i;i=e[i].next){
		int v=e[i].to;
		dfs(v);
		num[u]+=num[v];
		for(int j=m+1;j>=1;j--){
			for(int k=0;k<j;k++){
				f[u][j]=min(f[u][j],f[v][k]+f[u][j-k]);
			}
		} 
	}
	f[u][num[u]]=w[u];
	return;
}

int main(){
	char x[20];
	while(scanf("%s",x)!=EOF){
		if(x[0]=='#') break;
		scanf("%d%d",&n,&m);
		memset(w,0,sizeof(w));
		memset(head,0,sizeof(head));
		memset(f,inf,sizeof(f));
		memset(du,0,sizeof(du));
		cnt=0;
		for(int i=1;i<=n;i++){
			char s[20];
			cin>>s;
			fw[s]=i;
			scanf("%d",&w[i]);
			while(scanf("%s",s)){
				add(i,fw[s]);
				du[fw[s]]++;
			}
		}
		for(int i=1;i<=n;i++){
			if(!du[i]) add(0,i);
		}
		dfs(0);
		printf("%d\n",f[0][m+1]);
	}	
}


