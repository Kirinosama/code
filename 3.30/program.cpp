#include <cstdlib>
#include <cstdio>
#include <cstring>
#include <iostream>
#include <algorithm>
#include <map>
using namespace std;

#define MAXN 200010

int n,m,go[MAXN][2];
int f[MAXN],g[MAXN];
int ans[MAXN][2][10];
string str;

void del(int x){
    go[go[x][0]][1]=go[x][1];
    go[go[x][1]][0]=go[x][0];
}

void move(int &pos,int &c,int ti,int *cnt){
    int tmp;
    if(str[pos]=='<' || str[pos]=='>')
        c=str[pos]=='>';
    if(c==1){
        tmp=go[pos][1];
        for(int i=pos+1;i<=tmp;i++)if(!f[i]){
            f[i]=ti;
            for(int j=0;j<10;j++)ans[i][0][j]=cnt[j];
        }
    }else{
        tmp=go[pos][0];
        for(int i=pos;i>tmp;i--)if(!g[i]){
            g[i]=ti;
            for(int j=0;j<10;j++)ans[i][1][j]=cnt[j];
        }
    }
    if(tmp<2*n && (str[pos]=='<' || str[pos]=='>' ) && (str[tmp]=='>' || str[tmp]=='<'))
        del(pos);
    pos=tmp;
}

void solve(){
    int pos=n-1,c=1,ti=2;
    int cnt[10]={0};
    move(pos,c,1,cnt);
    while(pos>=0 && pos<2*n){
        if(str[pos]>='0' && str[pos]<='9'){
            if(str[pos]=='0') cnt[0]++,del(pos),move(pos,c,ti,cnt);
            else cnt[str[pos]-'0']++,str[pos]--,move(pos,c,ti,cnt);
        }else move(pos,c,ti,cnt);
        ti++;
    }
    /*for(int i=0;i<2*n;i++){
        if(f[i]){
            printf("f[%d]:",i);
            for(int j=0;j<10;j++)printf("%d ",ans[i][0][j]);
            cout<<endl;
        }
        if(g[i]){
            printf("g[%d]:",i);
            for(int j=0;j<10;j++)printf("%d ",ans[i][1][j]);
            cout<<endl;
        }
    }*/
}

int main(){
    freopen("program.in","r",stdin);
    freopen("program.out","w",stdout);
    cin>>n>>m>>str;
    for(int i=1;i<=n;i++) str='>'+str;
    for(int i=0;i<2*n;i++)go[i][0]=i-1,go[i][1]=i+1;
    solve();
    for(int i=1;i<=m;i++){
        int l,r;scanf("%d%d",&l,&r);
        l+=n-1,r+=n-1;
        if(f[r+1]<g[l]) for(int i=0;i<10;i++){
            printf("%d ",ans[r+1][0][i]-ans[l][0][i]);
        }else for(int i=0;i<10;i++){
            printf("%d ",ans[l][1][i]-ans[l][0][i]);
        }
        cout<<endl;
    }
    return 0;
}
