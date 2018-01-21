#include <cstdlib>
#include <cstdio>
#include <cstring>
#include <iostream>
#include <algorithm>
#include <map>
#include <vector>
using namespace std;

#define ls p->ch[0]
#define rs p->ch[1]
#define MAXM 300010
#define ii pair<int,int>
#define INF 0x3f3f3f3f
typedef long long ll;

struct node{
	node *ch[2];
	int flag,sum,tot;
	void update(){
		tot=0;
		if(ch[0])tot+=ch[0]->tot;
		if(ch[1])tot+=ch[1]->tot;
	}
}*root;

struct query{
	int l,r,k;
}q[MAXM];

int n,m,cnt;
vector <int> v;
map <int,int> mp;
map <int,int> mp1;

void build(node *&p,int l,int r){
	p=new node;p->ch[0]=p->ch[1]=NULL;
	p->sum=p->tot=mp1[r]-mp1[l]+1;p->flag=2;;
	if(l==r)return;
	int mid=(l+r)>>1;
	build(p->ch[0],l,mid);
	build(p->ch[1],mid+1,r);
}

void change(node *&p,int l,int r,int L,int R,int k){
	if(l>R || r<L) return;
	else if(l>=L && r<=R){
		p->flag=k;
		if(k==2) p->sum=p->tot=mp1[r]-mp1[l]+1;
		else p->sum=p->tot=0;
		return;
	}
	else if(l!=r){
		int mid=(l+r)>>1;
		if(p->flag){
			if(p->flag==1){
				ls->flag=1,ls->sum=ls->tot=0;
				rs->flag=1,rs->sum=rs->tot=0;
			}
			else{
				ls->flag=2,ls->sum=ls->tot=mp1[mid]-mp1[l]+1;
				rs->flag=2,rs->sum=rs->tot=mp1[r]-mp1[mid+1]+1;
			}
			p->flag=0;
		}
		change(p->ch[0],l,mid,L,R,k);
		change(p->ch[1],mid+1,r,L,R,k);
		p->update();
	}
}

int main(){
    freopen("cf36.in","r",stdin);
    cin>>n>>m;
    for(int i=1;i<=m;i++){
    	scanf("%d %d %d",&q[i].l,&q[i].r,&q[i].k);
    	v.push_back(q[i].l),v.push_back(q[i].r);
    }
    v.push_back(1),v.push_back(n);
   	sort(v.begin(),v.end());
   	for(int i=0;i<v.size();i++)
   		if(!mp[v[i]]){
   			mp[v[i]]=++cnt;
   			mp1[cnt]=v[i];
   		}
   	build(root,1,cnt);
   	for(int i=1;i<=m;i++){
   		change(root,1,cnt,mp[q[i].l],mp[q[i].r],q[i].k);
   		printf("%d\n",root->tot);
   	}
    return 0;
}