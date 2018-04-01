#include <cstdlib>
#include <cstdio>
#include <cstring>
#include <iostream>
#include <algorithm>
#include <cmath>
#include <set>
using namespace std;

#define MAXN 100010
#define MAXM 200010
#define ii pair<int,int>
#define INF 0x3f3f3f3f
typedef long long ll;

struct node{
    int x,y;
    node(int a=0,int b=0){x=a,y=b;}
    double dis(const node &a){
        return sqrt((x-a.x)*(x-a.x)+(y-a.y)*(y-a.y));
    }
    node operator - (const node &a)const{
        return node(x-a.x,y-a.y);
    }
    int operator * (const node &a)const{
        return x*a.y-y*a.x;
    }
    bool operator < (const node &a)const{
        return *this*a>0;
    }
}p[MAXN],tmp[MAXN];

struct query{
    int type,x;
    double ans;
    node point;
}q[MAXM];

bool book[MAXN];
int n,m,x,y;
double ans;
set <node> s;

void graham(){
    int cnt=0,now=0;
    for(int i=1;i<=n;i++)if(!book[i])
        p[++cnt]=p[i];
    sort(p+2,p+cnt+1);
    tmp[++now]=p[1];tmp[++now]=p[2];
    for(int i=3;i<=cnt;i++){
        while(now>1 && (p[i]-p[now-1])*(p[now]-p[now-1])>=0) now--;
        tmp[++now]=p[i];
    }tmp[now+1]=p[1];
    s.insert(p[1]);
    for(int i=2;i<=now;i++){
        ans+=tmp[i].dis(tmp[i+1]);
        s.insert(tmp[i]);
    }
    for(set<node>::iterator it=s.begin();it!=s.end();it++)
        printf("%d %d\n",it->x,it->y);
}

void add(node x){
    
}

void solve(query &cur){
    if(cur.type==2) cur.ans=ans;
    else add(cur.point);
}

int main(){
    freopen("bzoj2300.in","r",stdin);
    cin>>n>>x>>y;
    p[1]=node(0,0);p[2]=node(n,0);p[3]=node(x,y);
    cin>>n;n+=3;
    for(int i=4;i<=n;i++)scanf("%d%d",&p[i].x,&p[i].y);
    cin>>m;
    for(int i=1;i<=m;i++){
        scanf("%d",&q[i].type);
        if(q[i].type==1){
            scanf("%d",&q[i].x),q[i].x+=3,book[q[i].x]=true;
            q[i].point=p[q[i].x];
        }
    }
    graham();
    for(int i=m;i>=1;i--)solve(q[i]);
    for(int i=1;i<=m;i++)if(q[i].type==2)
        printf("%.2f\n",q[i].ans);
    return 0;
}
