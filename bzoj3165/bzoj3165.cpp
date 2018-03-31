#include <cstdlib>
#include <cstdio>
#include <cstring>
#include <iostream>
#include <algorithm>
using namespace std;

#define eps 1e-8
#define MAXN 100010
#define ls p->ch[0]
#define rs p->ch[1]
#define ii pair<int,int>
#define INF 0x3f3f3f3f
typedef long long ll;

int T,lastans,cnt;

struct point{
    int x,y;
    point(int a=0,int b=0){x=a,y=b;}
};

struct line{
    point a,b;
    line(int x=0,int y=0,int X=0,int Y=0){a=point(x,y),b=point(X,Y);}
}L[MAXN];

struct node{
    node *ch[2];
    int ID;
    node(int x=0){ch[0]=ch[1]=NULL,ID=x;}
}*root;

void build(node *&p,int l,int r){
    p=new node;
    if(l==r) return;
    int mid=(l+r)>>1;
    build(ls,l,mid);
    build(rs,mid+1,r);
}

double cal(line &a,int pos){
    return (double)a.a.y+(double)(a.b.y-a.a.y)/(double)(a.b.x-a.a.x)*(double)(pos-a.a.x);
}

int judge(line &a,line &b,int p,int q,int r){
    return (cal(a,p)>cal(b,p)+eps)*4+(cal(a,q)>cal(b,q)+eps)*2+(cal(a,r)>cal(b,r)+eps);
}

void add(node *p,int l,int r,int cur){
    if(L[cur].a.x>r || L[cur].b.x<l) return;
    if(L[cur].a.x<=l && L[cur].b.x>=r){
        int mid=(l+r)>>1;
        if(!p->ID){
            //printf("%d %d %d\n",l,r,cur);
            p->ID=cur;return;
        }else{
            int c=judge(L[cur],L[p->ID],l,mid,r);
            if(!c) return;
            else if(c==7){p->ID=cur;return;}
            else if(c==1 && r>mid) add(rs,mid+1,r,cur);
            else if(c==4 && l<mid) add(ls,l,mid,cur);
            else if(c==3){
                if(l<mid) add(ls,l,mid,p->ID);
                p->ID=cur;
            }else if(c==6){
                if(r>mid) add(rs,mid+1,r,p->ID);
                p->ID=cur;
            }
        }        
    }else{
        int mid=(l+r)>>1;
        add(ls,l,mid,cur);
        add(rs,mid+1,r,cur);
    }
}

int Max(int x,int y,int z){
    if(!x) return y;
    if(!y) return x;
    if(x>y) swap(x,y);
    if(cal(L[x],z)>=cal(L[y],z)-eps) return x;
    return y;
}

int query(node *p,int l,int r,int z){
    int mid=(l+r)>>1,c;
    if(l==r) return p->ID;
    if(z<=mid) c=query(ls,l,mid,z);
    else c=query(rs,mid+1,r,z);
    return Max(c,p->ID,z);
}

void solve(){
    int opt,x,y,a,b;
    scanf("%d",&opt);
    if(!opt){
        scanf("%d",&x);x=(x+lastans-1)%39989+1;
        lastans=query(root,1,39989,x);printf("%d\n",lastans);
    }else{
        scanf("%d%d%d%d",&x,&y,&a,&b);
        if(x>a) swap(x,a),swap(y,b);
        x=(x+lastans-1)%39989+1,y=(y+lastans-1)%1000000000+1;
        a=(a+lastans-1)%39989+1,b=(b+lastans-1)%1000000000+1;
        L[++cnt]=line(x,y,a,b);add(root,1,39989,cnt);
    }
}

int main(){
    freopen("bzoj3165.in","r",stdin);
    scanf("%d",&T);
    build(root,1,39989);
    while(T--)solve();
    return 0;
}
