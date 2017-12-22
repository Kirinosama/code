#include<bits/stdc++.h>
using namespace std;

#define ll long long
#define pi (4*atan(1.0))
#define eps 1e-14

const int N=2e5+10,M=1e6+10,inf=1e9+10,mod=1e9+7;
const ll INF=1e18+10;

struct is
{
    char a[5][5];
    int step;
};

char mp[5][5];
char ans[5][5];
int xx[4]={0,1,0,-1};
int yy[4]={1,0,-1,0};
map<string,int>m;

string check(char mp[][5])
{
    string a="";
    for(int i=0;i<4;i++)
        for(int t=0;t<4;t++)
            a+=mp[i][t];
    return a;
}

queue<is>q;

int ff(int x,int y)
{
    if(x<0||x>=4||y<0||y>=4)
        return 0;
    return 1;
}

int main()
{
    for(int i=0;i<4;i++)
        scanf("%s",mp[i]);
    for(int i=0;i<4;i++)
        scanf("%s",ans[i]);
    m[check(mp)]=1;
    is f;
    for(int i=0;i<4;i++)
        for(int t=0;t<4;t++)
        f.a[i][t]=mp[i][t];
    f.step=0;
    q.push(f);
    int out;
    while(!q.empty())
    {
        is b=q.front();
        q.pop();
        int flag=1;
        for(int i=0;i<4;i++)
        {
            for(int t=0;t<4;t++)
            if(b.a[i][t]!=ans[i][t])
            {
                flag=0;
                break;
            }
        }
        if(flag)
        {
            out=b.step;
            break;
        }
        for(int i=0;i<4;i++)
        {
            for(int t=0;t<4;t++)
            if(b.a[i][t]=='1')
            {
                for(int j=0;j<4;j++)
                {
                    int xxx=i+xx[j];
                    int yyy=t+yy[j];
                    //cout<<xxx<<" "<<yyy<<" "<<ff(xxx,yyy)<<endl;
                    if(ff(xxx,yyy)&&b.a[xxx][yyy]=='0')
                    {
                        b.a[xxx][yyy]='1';
                        b.a[i][t]='0';
                        b.step++;
                        if(m[check(b.a)]==0)
                        q.push(b),m[check(b.a)]=1;
                        b.step--;
                        b.a[xxx][yyy]='0';
                        b.a[i][t]='1';
                    }
                }
            }
        }
    }
    printf("%d\n",out);
    return 0;
}