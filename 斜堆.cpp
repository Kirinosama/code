#include <bits/stdc++.h>
using namespace std;

#define MAXN 100010

int n,m,val[MAXN],ls[MAXN],rs[MAXN],fa[MAXN];
int book[MAXN];

int find(int x){
	if(book[x]) return 0;
	if(fa[x]) return find(fa[x]);
	else return x;
}

int merge(int x,int y){
	if(!x) return y;
	if(!y) return x;
	if(val[x]<val[y] || (val[x]==val[y] && x<y)){
		swap(ls[x],rs[x]);
		ls[x]=merge(ls[x],y);
		if(ls[x])fa[ls[x]]=x;
		return x;
	}else{
		ls[y]=merge(ls[y],x);
		if(ls[y])fa[ls[y]]=y;
		return y;
	}
}

int main(){
	freopen("input","r",stdin);
	cin>>n>>m;
	for(int i=1;i<=n;i++){
		scanf("%d",&val[i]);
	}
	while(m--){
		int opt,x,y;
		scanf("%d",&opt);
		if(opt==1){
			scanf("%d%d",&x,&y);	
			int fx=find(x),fy=find(y);
			if(fx!=fy)merge(fx,fy);
		}else{
			scanf("%d",&x);
			if(book[x]) cout<<-1<<endl;
			else{
				int fx=find(x);
				printf("%d\n",val[fx]);
				book[fx]=1;
				fa[ls[fx]]=fa[rs[fx]]=0;
				merge(ls[fx],rs[fx]);
			}
		}
	}
	return 0;
}
