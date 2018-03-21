#include<cstdio>
#include<iostream>
using namespace std;
#define mod 51061
int n,q,father[100001],c[100001][2],st[100001];
bool rev[100001];
unsigned int sum[100001],add[100001],mul[100001],size[100001],val[100001];

int read()
{
    int w=0,f=1; char ch=getchar();
    while (ch<'0' || ch>'9')
      {
        if (ch=='-') f=-1;
        ch=getchar();
      }
    while (ch>='0' && ch<='9')
      w=w*10+ch-'0',ch=getchar();
    return w*f;
}

bool isroot(int x)
{
    return c[father[x]][0]!=x && c[father[x]][1]!=x;
}

void cal(int x,int m,int a)
{
    if (!x) return;
    val[x]=(val[x]*m+a)%mod;
    sum[x]=(sum[x]*m+a*size[x])%mod;
    add[x]=(add[x]*m+a)%mod;
    mul[x]=(mul[x]*m)%mod;
}

void update(int x)
{
    int l=c[x][0],r=c[x][1];
    sum[x]=(sum[l]+sum[r]+val[x])%mod;
    size[x]=(size[l]+size[r]+1)%mod;
}

void pushdown(int k)
{
    int l=c[k][0],r=c[k][1],m=mul[k],a=add[k];
    if (rev[k]) rev[k]^=1,rev[l]^=1,rev[r]^=1,swap(c[k][0],c[k][1]);
    mul[k]=1,add[k]=0;
    if (m!=1 || a!=0) cal(l,m,a),cal(r,m,a);
}

void rotate(int x)
{
    int y=father[x],z=father[y],l,r;
    if (c[y][0]==x) l=0;
    else l=1;
    r=l^1;
    if (!isroot(y))
      if (c[z][0]==y) c[z][0]=x;
      else c[z][1]=x;
    father[x]=z,father[y]=x,father[c[x][r]]=y;
    c[y][l]=c[x][r],c[x][r]=y;
    update(y),update(x);
}

void splay(int x)
{
    int i,top=0,y,z;
    top++,st[top]=x;
    for (i=x;!isroot(i);i=father[i])
      top++,st[top]=father[i];
    for (i=top;i;i--)
      pushdown(st[i]);
    while (!isroot(x))
      {
        y=father[x],z=father[y];
        if (!isroot(y))
          if (c[y][0]==x^c[z][0]==y) rotate(x);
          else rotate(y);
        rotate(x);
      }
}

void access(int x)
{
    int t;
    for (t=0;x;t=x,x=father[x])
      splay(x),c[x][1]=t,update(x);
}

void rever(int x)
{
    access(x),splay(x),rev[x]^=1;
}

void link(int x,int y)
{
    rever(x),father[x]=y;
}

void cut(int x,int y)
{
    rever(x),access(y),splay(y),c[y][0]=father[x]=0;
}

void split(int x,int y)
{
    rever(y),access(x),splay(x);
}

int main()
{
    freopen("bzoj2631.in","r",stdin);
    freopen("bzoj26311.out","w",stdout);
    char s[10];
    int i,x,y,z;
    n=read(),q=read();
    for (i=1;i<=n;i++)
      sum[i]=mul[i]=size[i]=val[i]=1;
    for (i=1;i<=n-1;i++)
      x=read(),y=read(),link(x,y);
    for (i=1;i<=q;i++)
      {
        scanf("%s",&s),x=read(),y=read();
        if (s[0]=='+')
          z=read(),split(x,y),cal(x,1,z);
        if (s[0]=='-')
          cut(x,y),x=read(),y=read(),link(x,y);
        if (s[0]=='*')
          z=read(),split(x,y),cal(x,z,0);
        if (s[0]=='/')
          split(x,y),printf("%d\n",sum[x]);
      }
    return 0;
}