#include <cstdlib>
#include <cstdio>
#include <cstring>
#include <iostream>
#include <algorithm>
#include <queue>
using namespace std;

#define MAXN 200010
#define ii pair<int,int>
#define INF 0x3f3f3f3f
typedef long long ll;

struct cmp{
	bool operator()(const ii &a,const ii &b){
		if(a.second==b.second) return a.first>b.first;
		return a.second<b.second;
	}
};

priority_queue <ii,vector<ii>,cmp> q;
int L[MAXN],R[MAXN],father[MAXN],n,size[MAXN],l[MAXN],r[MAXN],a[MAXN],ans;
bool book[MAXN];

int find(int x){
	return father[x]==x?x:father[x]=find(father[x]);
}

void merge(int x,int y){
	int fx=find(x);
	int fy=find(y);
	if(fx==fy) return;
	if(fx>fy) swap(fx,fy);
	father[fy]=fx;size[fx]+=size[fy];r[fx]=r[fy];
}

int main(){
    freopen("cf452.in","r",stdin);
    scanf("%d",&n);
    for(int i=1;i<=n;i++){
    	father[i]=i;l[i]=r[i]=i;size[i]=1;
    	scanf("%d",&a[i]);
    	L[i]=i-1,R[i]=i+1;
    }
    for(int i=2;i<=n;i++){
    	if(a[i]==a[i-1])
    		merge(i,i-1);
    }
    for(int i=1;i<=n;i++)
    	if(father[i]==i)
    		q.push(ii(i,size[i]));
    while(n){
    	ii tp=q.top();q.pop();
    	int p=tp.first;
    	if(!book[p]){
	    	ans++;
	    	n-=size[p];
	    	int x=L[l[p]],y=R[r[p]];
	    	R[x]=y,L[y]=x;
	    	if(a[x]==a[y]){
	    		merge(x,y);book[y]=true;
	    		q.push(ii(find(x),size[find(x)]));
	    	}
	    }
	    book[p]=true;
    }
	cout<<ans;
    return 0;
}