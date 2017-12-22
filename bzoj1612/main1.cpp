#include<iostream>
#include<algorithm>
#include<stdio.h>
#include<set>
using namespace std;
typedef long long ll;
const ll inf=1e16;
struct node{
    ll x;ll y;int id;
}a[100005];
int c,n,fa[100005],cnt[100005];
multiset<node>s;
node jia(ll xx,ll yy,int idd)
{
    node tmp;
    tmp.x=xx;tmp.y=yy;tmp.id=idd;
    return tmp;
}
int cmp(node x,node y)
{
    if (x.x!=y.x)
    return x.x<y.x;
    return x.y<y.y;
}
bool operator < (const node a, const node b)
{
    return a.y < b.y;
}
int find(int x)
{
    if (fa[x]==x)return x;
    return fa[x]=find(fa[x]);
}
int num;
void unio(int x,int y)
{
    //cout<<x<<' '<<y<<endl;
    int X=find(x);
    int Y=find(y);
    if (X!=Y)
    {
        fa[X]=Y;
        num--;
    }
}
int main()
{
    scanf("%d%d",&n,&c);num=n;
    for (int i=1;i<=n;i++)
    {
        ll x,y;
        fa[i]=i;
        scanf("%lld%lld",&x,&y);
        a[i].x=x+y;a[i].y=x-y;
        a[i].id=i;
    }
    sort(a+1,a+1+n,cmp);
    s.insert(jia(0,inf,0));
    s.insert(jia(0,-inf,0));
    s.insert(a[1]);
    int head=1;
    node l,r;
    for (int i=2;i<=n;i++)
    {
        while(a[i].x-a[head].x>c)
        {
            s.erase(s.find(a[head]));
            head++;
        }
        set <node> ::iterator it=s.lower_bound(a[i]);
        r=*it;it--;l=*it;
        if (a[i].y-l.y<=c)
        unio(a[i].id,l.id);
        if (r.y-a[i].y<=c)
        unio(a[i].id,r.id);
        s.insert(a[i]);
    }
    int sum=-1;
    for (int i=1;i<=n;i++)
    {
        int tmp=find(i);
        cnt[tmp]++;
        sum=max(sum,cnt[tmp]);
    }
    printf("%d %d\n",num,sum);
}