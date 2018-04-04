#include <cstdlib>
#include <cstdio>
#include <cstring>
#include <iostream>
#include <algorithm>
using namespace std;

#define ls p->ch[0]
#define rs p->ch[1]
#define ii pair<int,int>
#define INF 0x3f3f3f3f
typedef long long ll;

struct node{
    node *ch[2];
    int val_and,val_or,val_max;
    int tag_and,tag_or;
    node(){ch[0]=ch[1]=NULL;}
}*root;

int n,q,a[200010];
const int s=(1<<20)-1;

void update(node *p){
    p->val_and=ls->val_and & rs->val_and;
    p->val_or=ls->val_or | rs->val_or;
    p->val_max=max(ls->val_max,rs->val_max);
}

void build(node *&p,int l,int r){
    p=new node;p->tag_and=s;p->tag_or=0;
    if(l==r){
        p->tag_and=s,p->tag_or=0;
        p->val_and=p->val_or=p->val_max=a[l];
    }else{
        int mid=(l+r)>>1;
        build(ls,l,mid);build(rs,mid+1,r);
        update(p);
    }
}

void do_and(node *p,int x){
    p->tag_and &= x;
    p->tag_or &= x;
    p->val_and &= x;
    p->val_or &= x;
    p->val_max &= x;
}

void do_or(node *p,int x){
    p->tag_or |= x;
    p->val_and |= x;
    p->val_or |= x;
    p->val_max |= x;
}

void pushdown(node *p){
    if(p->tag_and!=s){
        do_and(ls,p->tag_and);
        do_and(rs,p->tag_and);
        p->tag_and=s;
    }
    if(p->tag_or){
        do_or(ls,p->tag_or);
        do_or(rs,p->tag_or);
        p->tag_or=0;
    }
}

void make(node *p,int l,int r,int L,int R,int opt,int x){
    if(l>R || r<L) return;
    if(l>=L && r<=R){
        if(opt==1){
            if(((x^s) & (p->val_and | (p->val_or^s) )) == (x^s)){
                do_and(p,x);return;
            }
        }else{
            if((x & (p->val_and | (p->val_or ^ s))) == x){
                do_or(p,x);return;
            }
        }
    }
    int mid=(l+r)>>1;
    pushdown(p);
    make(ls,l,mid,L,R,opt,x);make(rs,mid+1,r,L,R,opt,x);
    update(p);
}

int query(node *p,int l,int r,int L,int R){
    if(l>R || r<L) return 0;
    if(l>=L && r<=R) return p->val_max;
    int mid=(l+r)>>1;
    pushdown(p);
    int res=max(query(ls,l,mid,L,R),query(rs,mid+1,r,L,R));
    update(p);
    return res;
}

int main(){
    freopen("4.2a.in","r",stdin);
    cin>>n>>q;
    for(int i=1;i<=n;i++)scanf("%d",&a[i]);
    build(root,1,n);
    while(q--){
        int opt,l,r,x;
        scanf("%d%d%d",&opt,&l,&r);
        if(opt==3) cout<<query(root,1,n,l,r)<<endl;
        else{
            scanf("%d",&x);
            make(root,1,n,l,r,opt,x);
        }
    }
    return 0;
}
