#include <cstdio>
#include <cstring>
#include <iostream>
#include <algorithm>
#define N 100100
#define lson l,mid,rt<<1
#define rson mid+1,r,rt<<1|1
using namespace std;
struct node
{
    int l,r;
    int lcnt[2],rcnt[2],mcnt[2],sum[2];
    int has_tag,cov,rev;
}seg[N<<2];
void swapp(int rt)
{
    swap(seg[rt].lcnt[0],seg[rt].lcnt[1]);
    swap(seg[rt].rcnt[0],seg[rt].rcnt[1]);
    swap(seg[rt].mcnt[0],seg[rt].mcnt[1]);
    swap(seg[rt].sum[0],seg[rt].sum[1]);
}
void pushup(int rt)
{
    for(int i=0;i<=1;i++)
    {
        if(seg[rt<<1].lcnt[i]==seg[rt<<1].r-seg[rt<<1].l+1)
            seg[rt].lcnt[i]=seg[rt<<1].lcnt[i]+seg[rt<<1|1].lcnt[i];
        else seg[rt].lcnt[i]=seg[rt<<1].lcnt[i];
        if(seg[rt<<1|1].rcnt[i]==seg[rt<<1|1].r-seg[rt<<1|1].l+1)
            seg[rt].rcnt[i]=seg[rt<<1|1].rcnt[i]+seg[rt<<1].rcnt[i];
        else seg[rt].rcnt[i]=seg[rt<<1|1].rcnt[i];
        seg[rt].sum[i]=seg[rt<<1].sum[i]+seg[rt<<1|1].sum[i];
        seg[rt].mcnt[i]=max(seg[rt<<1].mcnt[i],max(seg[rt<<1].rcnt[i]+seg[rt<<1|1].lcnt[i],seg[rt<<1|1].mcnt[i]));
    }
}
void pushdown(int rt)
{
    if(seg[rt].rev)
    {
        if(seg[rt<<1].has_tag&&seg[rt<<1].l!=seg[rt<<1].r)seg[rt<<1].cov^=1,swapp(rt<<1);
        else seg[rt<<1].rev^=1,swapp(rt<<1);
        if(seg[rt<<1|1].has_tag&&seg[rt<<1|1].l!=seg[rt<<1|1].r)seg[rt<<1|1].cov^=1,swapp(rt<<1|1);
        else seg[rt<<1|1].rev^=1,swapp(rt<<1|1);
        seg[rt].rev=0;
    }
    if(seg[rt].has_tag)
    {
        int tmp=seg[rt].cov; 
        seg[rt<<1].sum[tmp]=seg[rt<<1].lcnt[tmp]=seg[rt<<1].rcnt[tmp]=seg[rt<<1].mcnt[tmp]=seg[rt<<1].r-seg[rt<<1].l+1;
        seg[rt<<1].sum[tmp^1]=seg[rt<<1].lcnt[tmp^1]=seg[rt<<1].rcnt[tmp^1]=seg[rt<<1].mcnt[tmp^1]=0;
        seg[rt<<1].has_tag=1,seg[rt<<1].cov=tmp;
        seg[rt<<1|1].sum[tmp]=seg[rt<<1|1].lcnt[tmp]=seg[rt<<1|1].rcnt[tmp]=seg[rt<<1|1].mcnt[tmp]=seg[rt<<1|1].r-seg[rt<<1|1].l+1;
        seg[rt<<1|1].sum[tmp^1]=seg[rt<<1|1].lcnt[tmp^1]=seg[rt<<1|1].rcnt[tmp^1]=seg[rt<<1|1].mcnt[tmp^1]=0;
        seg[rt<<1|1].has_tag=1,seg[rt<<1|1].cov=tmp;
        seg[rt].has_tag=0,seg[rt].cov=0;
    }
}
void build(int l,int r,int rt)
{
    seg[rt].l=l,seg[rt].r=r;
    if(l==r)
    {
        int x;
        scanf("%d",&x);
        seg[rt].sum[x]=seg[rt].lcnt[x]=seg[rt].rcnt[x]=seg[rt].mcnt[x]=1;
        return ;
    }
    int mid=(l+r)>>1;
    build(lson);
    build(rson);
    pushup(rt);
}
void update_cov(int v,int L,int R,int l,int r,int rt)
{
    if(L<=l&&r<=R)
    {
        if(seg[rt].rev)
            seg[rt].rev=0;
        seg[rt].has_tag=1;
        seg[rt].cov=v;
        seg[rt].lcnt[v]=seg[rt].rcnt[v]=seg[rt].mcnt[v]=seg[rt].sum[v]=r-l+1;
        seg[rt].lcnt[v^1]=seg[rt].rcnt[v^1]=seg[rt].mcnt[v^1]=seg[rt].sum[v^1]=0;
        return;
    }
    int mid=(l+r)>>1;
    pushdown(rt);
    if(L<=mid)update_cov(v,L,R,lson);
    if(R>mid)update_cov(v,L,R,rson);
    pushup(rt);
}
void update_rev(int L,int R,int l,int r,int rt)
{
    if(L<=l&&r<=R)
    {
        if(seg[rt].has_tag&&l!=r){seg[rt].cov^=1;swapp(rt);return;}
        seg[rt].rev^=1;
        swapp(rt);
        return;
    }
    int mid=(l+r)>>1;
    pushdown(rt);
    if(L<=mid)update_rev(L,R,lson);
    if(R>mid)update_rev(L,R,rson);
    pushup(rt);
}
int query_has(int L,int R,int l,int r,int rt)
{
    int ret=0;
    if(L<=l&&r<=R)
    {
        return seg[rt].sum[1];
    }
    int mid=(l+r)>>1;
    pushdown(rt);
    if(L<=mid)ret+=query_has(L,R,lson);
    if(R>mid)ret+=query_has(L,R,rson);
    return ret;
}
struct Re
{
    int l,m,r;
};
Re query_con(int L,int R,int l,int r,int rt)
{
    if(L<=l&&r<=R)
    {
        Re tmp;
        tmp.l=seg[rt].lcnt[1];
        tmp.r=seg[rt].rcnt[1];
        tmp.m=seg[rt].mcnt[1];
        return tmp;
    }
    pushdown(rt);
    int mid=(l+r)>>1;
    if(L>mid)return query_con(L,R,rson);
    else if(R<=mid)return query_con(L,R,lson);
    else
    {
        Re tmp1=query_con(L,mid,lson);
        Re tmp2=query_con(mid+1,R,rson);
        Re ret;
        if(tmp1.l==mid-L+1)ret.l=tmp1.l+tmp2.l;
        else ret.l=tmp1.l;
        if(tmp2.r==R-mid)ret.r=tmp2.r+tmp1.r;
        else ret.r=tmp2.r;
        ret.m=max(tmp1.m,max(tmp2.m,tmp1.r+tmp2.l)); 
        return ret;
    }
}
int n,m;
int main()
{
    scanf("%d%d",&n,&m);
    build(1,n,1);
    for(int i=1;i<=m;i++)
    {
        int opt,l,r;
        scanf("%d%d%d",&opt,&l,&r);
        l++,r++; 
        switch(opt)
        {
            case 0:update_cov(0,l,r,1,n,1);break; 
            case 1:update_cov(1,l,r,1,n,1);break;
            case 2:update_rev(l,r,1,n,1);break;
            case 3:printf("%d\n",query_has(l,r,1,n,1));break;
            case 4:
                Re print=query_con(l,r,1,n,1);
                printf("%d\n",max(print.l,max(print.m,print.r))
                );
                break;
        }
    }
}