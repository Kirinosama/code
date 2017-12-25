#include<iostream>
#include<cstring>
#include<cstdio>
using namespace std;

const int max_n=500005;
const int max_e=max_n*2;
const int max_tree=max_n*4;
const int MININF=-2147483647;

int n,m,x,y,z,u,t,k,w,N,ans;
int tot,point[max_n],next[max_e],v[max_e],c[max_e];
int father[max_n],son[max_n],faedge[max_n],sonedge[max_n],h[max_n],size[max_n];
int top[max_n],num[max_n],val[max_n];
int maxn[max_tree],cover[max_tree],add[max_tree];
char opt[10];

inline void addedge(int x,int y,int z){
    ++tot; next[tot]=point[x]; point[x]=tot; v[tot]=y; c[tot]=z;
    ++tot; next[tot]=point[y]; point[y]=tot; v[tot]=x; c[tot]=z;
}

inline void dfs_1(int x,int fa,int dep){
    size[x]=1; h[x]=dep; father[x]=fa;
    int maxson=0;
    for (int i=point[x];i;i=next[i])
      if (v[i]!=fa){
        faedge[v[i]]=i;
        dfs_1(v[i],x,dep+1);
        size[x]+=size[v[i]];
        if (size[v[i]]>maxson){
            maxson=size[v[i]];
            son[x]=v[i];
            sonedge[x]=i;
        }
      } 
}

inline void dfs_2(int x,int fa){
    if (son[fa]!=x) top[x]=x;
    else top[x]=top[fa];
    if (son[x]){
        num[sonedge[x]]=++N;
        val[N]=c[sonedge[x]];
        dfs_2(son[x],x);
    }
    for (int i=point[x];i;i=next[i])
      if (v[i]!=fa&&v[i]!=son[x]){
        num[i]=++N;
        val[N]=c[i];
        dfs_2(v[i],x);
      }
}

inline void update(int now){
    maxn[now]=max(maxn[now<<1],maxn[now<<1|1]); 
}

inline void pushdown(int now,int l,int r,int mid){
    if (cover[now]!=-1){
        add[now<<1]=add[now<<1|1]=0; 
        maxn[now<<1]=cover[now];
        cover[now<<1]=cover[now];
        maxn[now<<1|1]=cover[now];
        cover[now<<1|1]=cover[now];

        cover[now]=-1;
    }
    if (add[now]){
        maxn[now<<1]+=add[now];
        if (cover[now<<1]!=-1) cover[now<<1]+=add[now];
        else add[now<<1]+=add[now];
        maxn[now<<1|1]+=add[now];
        if (cover[now<<1|1]!=-1) cover[now<<1|1]+=add[now];
        else add[now<<1|1]+=add[now];

        add[now]=0;
    }
}

inline void build(int now,int l,int r){
    int mid=(l+r)>>1;
    cover[now]=-1; add[now]=0;
    if (l==r){
        maxn[now]=val[l];
        return;
    }
    build(now<<1,l,mid);
    build(now<<1|1,mid+1,r);
    update(now);
}

inline void point_change(int now,int l,int r,int x,int v){
    int mid=(l+r)>>1;
    if (l==r){
        maxn[now]=v;
        return;
    }
    pushdown(now,l,r,mid);
    if (x<=mid)
      point_change(now<<1,l,mid,x,v);
    else
      point_change(now<<1|1,mid+1,r,x,v);
    update(now);
}

inline void interval_change(int now,int l,int r,int lrange,int rrange,int v,int opt){
    int mid=(l+r)>>1;
    if (lrange<=l&&r<=rrange){
        if (opt==0){
            maxn[now]=v; cover[now]=v;
            if (add[now]) add[now]=0;
        }
        else{
            maxn[now]+=v;
            if (cover[now]!=-1) cover[now]+=v;
            else add[now]+=v;
        }
        return; 
    }
    pushdown(now,l,r,mid);
    if (lrange<=mid)
      interval_change(now<<1,l,mid,lrange,rrange,v,opt);
    if (mid+1<=rrange)
      interval_change(now<<1|1,mid+1,r,lrange,rrange,v,opt);
    update(now);
}

inline int query(int now,int l,int r,int lrange,int rrange){
    int mid=(l+r)>>1,ans=MININF;
    if (lrange<=l&&r<=rrange) return maxn[now];
    pushdown(now,l,r,mid);
    if (lrange<=mid)
      ans=max(ans,query(now<<1,l,mid,lrange,rrange));
    if (mid+1<=rrange)
      ans=max(ans,query(now<<1|1,mid+1,r,lrange,rrange));
    return ans;
}

inline void Change(int u,int t,int w,int opt){
    int f1=top[u],f2=top[t];
    while (f1!=f2){
        if (h[f1]<h[f2]){
            swap(u,t);
            swap(f1,f2);
        }
        interval_change(1,1,N,num[faedge[f1]],num[faedge[u]],w,opt);
        u=father[f1];
        f1=top[u];
    }
    if (u==t) return;
    if (h[u]>h[t]) swap(u,t);
    interval_change(1,1,N,num[sonedge[u]],num[faedge[t]],w,opt);
}

inline int Query(int u,int t){
    int ans=MININF;
    int f1=top[u],f2=top[t];
    while (f1!=f2){
        if (h[f1]<h[f2]){
            swap(u,t);
            swap(f1,f2);
        }
        if (num[faedge[f1]]==0&&num[faedge[u]]==0) cout<<u<<"!"<<t<<endl;
        ans=max(ans,query(1,1,N,num[faedge[f1]],num[faedge[u]]));
        u=father[f1];
        f1=top[u];
    }
    if (u==t) return ans;
    if (h[u]>h[t]) swap(u,t);
    if (num[sonedge[u]]==0&&num[faedge[t]]==0) cout<<u<<" "<<t<<endl;
    ans=max(ans,query(1,1,N,num[sonedge[u]],num[faedge[t]]));
    return ans;
}

int main(){
    freopen("bzoj1984.in","r",stdin);
    freopen("out2","w",stdout);
    scanf("%d",&n);
    for (int i=1;i<n;++i){
        scanf("%d%d%d",&x,&y,&z);
        addedge(x,y,z);
    }
    dfs_1(1,0,1);
    dfs_2(1,0);
    build(1,1,N);
    while (~scanf("%s",opt)){
        if (opt[0]=='S') return 0;
        switch(opt[1]){
            case 'h':{
                scanf("%d%d",&k,&w);
                if (num[2*k-1]) point_change(1,1,N,num[2*k-1],w);
                else point_change(1,1,N,num[2*k],w);
                break;
            }
            case 'o':{
                scanf("%d%d%d",&u,&t,&w);
                if (u==t) continue;
                Change(u,t,w,0);
                break;
            }
            case 'd':{
                scanf("%d%d%d",&u,&t,&w);
                if (u==t) continue;
                Change(u,t,w,1);
                break;
            }
            case 'a':{
                scanf("%d%d",&u,&t);
                ans=Query(u,t);
                printf("%d\n",ans);
                break;
            }
        }
    }
} 
