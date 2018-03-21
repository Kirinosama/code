#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
#include<cmath>
using namespace std;
#define LL long long
inline int read()
{
    int x=0,f=1; char ch=getchar();
    while (ch<'0' || ch>'9') {if (ch=='-') f=-1; ch=getchar();}
    while (ch>='0' && ch<='9') {x=x*10+ch-'0'; ch=getchar();}
    return x*f;
}
#define MAXN 80010
#define P 19940417
int N,Q,C[MAXN][21];
namespace SegmentTree
{
    struct SumNode{int sum[25];};
    struct SegmentTreeNode{int l,r,size,tag; SumNode p; bool rev;}tree[MAXN<<2];
    #define ls now<<1
    #define rs now<<1|1
    inline void Add(int &x,int y) {x+=y; while (x>=P) x-=P; while (x<0) x+=P;}
    inline SumNode Merge(SegmentTreeNode x,SegmentTreeNode y)
    {
        SumNode re; re.sum[0]=1;
        for (int i=1; i<=20; i++)
            {
                re.sum[i]=(x.p.sum[i]+y.p.sum[i])%P;
                for (int j=1; j<=i-1; j++)
                    Add(re.sum[i],(LL)x.p.sum[j]*y.p.sum[i-j]%P);
            }
        return re;
    }   
    inline void Update(int now) {tree[now].p=Merge(tree[ls],tree[rs]);}
    inline void rever(int now)
    {
        tree[now].rev^=1;
        if (tree[now].tag) tree[now].tag=(P-tree[now].tag%P)%P;
        for (int i=1; i<=20; i++) if ((i&1) && tree[now].p.sum[i]) tree[now].p.sum[i]=(P-tree[now].p.sum[i])%P;
    }
    inline void change(int now,int D)
    {
        Add(tree[now].tag,D);
        for (int t=D,i=20; i; i--,t=D)
            {
                for (int j=i-1; j; j--,t=(LL)t*D%P) 
                    Add(tree[now].p.sum[i],(LL)t*tree[now].p.sum[j]%P*C[tree[now].size-j][i-j]%P);
                Add(tree[now].p.sum[i],(LL)t*C[tree[now].size][i]%P);
            }
    }
    inline void PushDown(int now)
    {
        if (tree[now].rev) {rever(ls); rever(rs); tree[now].rev=0;}
        if (tree[now].tag) {change(ls,tree[now].tag); change(rs,tree[now].tag); tree[now].tag=0;}
    }
    inline void BuildTree(int now,int l,int r)
    {
        tree[now].l=l; tree[now].r=r; tree[now].size=r-l+1; 
        tree[now].p.sum[0]=1; tree[now].tag=0; tree[now].rev=0;
        if (l==r) {tree[now].p.sum[1]=(read()+P)%P; return;}
        int mid=(l+r)>>1;
        BuildTree(ls,l,mid); BuildTree(rs,mid+1,r);
        Update(now);
    }
    inline void Reverse(int now,int L,int R)
    {
        int l=tree[now].l,r=tree[now].r;
        if (L<=l && R>=r) {rever(now); return;}
        PushDown(now);
        int mid=(l+r)>>1;
        if (L<=mid) Reverse(ls,L,R);
        if (R>mid) Reverse(rs,L,R);
        Update(now);
    }
    inline void Change(int now,int L,int R,int D)
    {
        int l=tree[now].l,r=tree[now].r;
        if (L<=l && R>=r) {change(now,D); return;}
        PushDown(now);
        int mid=(l+r)>>1;
        if (L<=mid) Change(ls,L,R,D);
        if (R>mid) Change(rs,L,R,D);
        Update(now);
    }
    inline SegmentTreeNode Query(int now,int L,int R,int D)
    {
        int l=tree[now].l,r=tree[now].r;
        if (L==l && R==r) return tree[now];
        PushDown(now);
        int mid=(l+r)>>1; SegmentTreeNode re;
        if (R<=mid) return Query(ls,L,R,D);
            else if (L>mid) return Query(rs,L,R,D);
                else return re.p=Merge(Query(ls,L,mid,D),Query(rs,mid+1,R,D)),re;
    }
}
void GetC()
{
    C[0][0]=1;
    for (int i=1; i<=N; i++)
        {
            C[i][0]=1;
            for (int j=1; j<=min(i,20); j++) C[i][j]=(C[i-1][j]+C[i-1][j-1])%P;
        }
}
using namespace SegmentTree;
int main()
{
  freopen("bzoj2962.in","r",stdin);
//  freopen("sequence.out","w",stdout);
    N=read(),Q=read();
    GetC();
    SegmentTree::BuildTree(1,1,N);
//  for (int i=1; i<=N; i++) printf("%I64d  ",Query(1,1,N,i).p.sum[i]); puts("");
//  puts("============================================"); 
    while (Q--)
        {
            char opt[2]; scanf("%s",opt); int x,y,z;
            switch (opt[0])
                {
                    case 'I' : x=read(),y=read(),z=(read()%P+P)%P; SegmentTree::Change(1,x,y,z); break;
                    case 'Q' : x=read(),y=read(),z=read(); printf("%d\n",SegmentTree::Query(1,x,y,z).p.sum[z]); break;
                    case 'R' : x=read(),y=read(); SegmentTree::Reverse(1,x,y); break;
                }
//          puts("============================================");      
//          for (int i=1; i<=N; i++) printf("%d\n",Query(1,1,N,i).p.sum[i]); puts("");
//          printf("%d %d %d\n",x,y,z);
//          puts("============================================"); 
        }
    return 0;
}