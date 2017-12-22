#include <cstdlib>
#include <cstdio>
#include <cstring>
#include <iostream>
using namespace std;

//节点1为哨兵节点为方便查询1-n
//故node2对应x^0系数

#define MAXN 200015
#define MAXM 100015
#define MOD 20130426
typedef long long ll;

ll ans,base,v[MAXN],add[MAXN],mul[MAXN];
int n,tot,fa[MAXN],son[MAXN][2],soncnt[MAXN];
int t1,t2,root;

void update(int x,ll ad,ll mu)
{
    if(!x) return;
    v[x]=(v[x]*mu+ad)%MOD;
    add[x]=(add[x]*mu+ad)%MOD;
    mul[x]=(mul[x]*mu)%MOD;
}

void push_down(int x)
{
    if(!x) return;
    if(mul[x]==1 && add[x]==0) return;
    int l=son[x][0]; int r=son[x][1];
    update(l,add[x],mul[x]);update(r,add[x],mul[x]);    
    mul[x]=1;add[x]=0;
}

void push_up(int x)
{
    soncnt[x]=soncnt[son[x][0]]+soncnt[son[x][1]]+1;
}

void rot(int x,int f)
{
    int y=fa[x];
    if(y!=root){
        if(son[fa[y]][0]==y) son[fa[y]][0]=x;
        else son[fa[y]][1]=x;
    }else root=x; 
    fa[x]=fa[y]; fa[y]=x;
    son[y][f]=son[x][!f];
    if(son[x][!f]) fa[son[x][!f]]=y;
    son[x][!f]=y;
    push_up(y);push_up(x);
}

void splay(int x,int &k)
{
    while(x!=k)
    {
        int y=fa[x];int z=fa[y];
        if(y==k){
            if(son[y][0]==x) rot(x,0);
            else rot(x,1);
        }
        else if(son[z][0]==y)
        {
            if(son[y][0]==x) rot(y,0),rot(x,0);
            else rot(x,1),rot(x,0);
        }
        else
        {
            if(son[y][1]==x) rot(y,1),rot(x,1);
            else rot(x,0),rot(x,1);
        }
    }
}

int init(int l,int r,int f)
{
    if(l>r) return 0;
    int mid=(l+r)>>1;
    fa[mid]=f;v[mid]=add[mid]=0;mul[mid]=1;
    son[mid][0]=init(l,mid-1,mid);
    son[mid][1]=init(mid+1,r,mid);
    push_up(mid);
    return mid;
}

int find(int x,int k)
{
    push_down(x);
    int lcnt=soncnt[son[x][0]];
    if(k==lcnt+1) return x;
    else if(k<=lcnt) return find(son[x][0],k);
    else return find(son[x][1],k-lcnt-1);
}

void split(int l,int r)
{
    t1=find(root,l);  t2=find(root,r);
    splay(t1,root);splay(t2,son[t1][1]); 
}

void getans(int cur)
{
    if(!cur) return;
    push_down(cur);
    getans(son[cur][1]);
    if(cur!=1) ans=(ans*base+v[cur])%MOD;
    getans(son[cur][0]);
}

void MUL()
{
    int l,r;ll v;
    scanf("%d %d %lld",&l,&r,&v);
    l+=2,r+=2,v%=MOD;
    split(l-1,r+1);
    int x=son[t2][0];
    int ad=0;int mu=v;
    update(x,ad,mu);  
}

void ADD()
{
    int l,r;ll v;
    scanf("%d %d %lld",&l,&r,&v);
    l+=2,r+=2,v%=MOD;
    split(l-1,r+1);
    int x=son[t2][0];
    int ad=v;int mu=1;
    update(x,ad,mu);  
}

void query()
{
    ans=0;cin>>base;
    base%=MOD;
    getans(root);
    cout<<ans<<endl;
}

void mulx()
{
    int l,r;
    scanf("%d %d",&l,&r);
    l+=2,r+=2;
    split(r-1,r+2);
    int z=son[t2][0];int zz=son[z][0]+son[z][1];
    push_down(t1);push_down(t2);push_down(z);
    v[z]=(v[z]+v[zz])%MOD;son[z][0]=son[z][1]=fa[zz]=0;soncnt[z]=1;
    push_up(t2);push_up(t1);
    split(l-1,l);
    push_down(t1);push_down(t2);
    son[t2][0]=++tot;v[tot]=add[tot]=0;mul[tot]=soncnt[tot]=1;
    son[tot][0]=son[tot][1]=0;fa[tot]=t2;
    push_up(t2);push_up(t1);
}

int main()
{
    freopen("input","r",stdin);
    cin>>n;
    root=init(1,MAXM,0);tot=MAXM;
    while(n--)
    {
        string s;cin>>s;
        if(s[0]=='m' && s[3]!='x') MUL();
        if(s[0]=='m' && s[3]=='x') mulx(); 
        if(s[0]=='a')ADD();
        if(s[0]=='q') query(); 
    }
    return 0;
}