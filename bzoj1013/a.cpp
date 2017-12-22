#include <cstdlib>
#include <cstdio>
#include <cstring>
#include <iostream>
#include <algorithm>
#include <vector>
using namespace std;
#define ii pair<int,int>
const int inf=233333333;
int i,j,m,n,t1,t2,t3,ans;
vector <ii> to[10010];
int d[10010];
bool vis[10010];
int q[666666],head,tail,k;
int Ts;
int main()
{
    //加入1->2边长为3的边 和 1->4边长为5的边
    //to[1].push_back(ii(2,3));
    //to[1].push_back(ii(4,5));
    //遍历一个点的所有边
    //for(int i=0;i<to[1].size();i++)
    //{
    //	ii edge=to[1][i];
    //	printf("%d %d\n",edge.first,edge.second);
    //}
    
    cin>>n;//n个点 
    cin>>m;//m条边
    cin>>Ts;//出发点 
	for(i=1;i<=m;i++)
	{
		cin>>t1>>t2>>t3;
		to[t1].push_back(ii(t2,t3));
	} 
	
	for(i=1;i<=n;i++) 
	{
		d[i]=inf;
	}
	
	d[Ts]=0;vis[Ts]=1;
	head=tail=1;
	q[head]=Ts;
	while(tail>=head)
    {
        int x=q[head];
        head++;
        vis[x]=0;                //注意这个 
        for(k=0;k<to[x].size();k++)
        {
            //int y=g[x][k];
            int y=to[x][k].second;
            //cout<<y<<endl;
            int kk=to[x][k].first;
            if(d[x]+y<d[kk])
            {
                d[kk]=d[x]+y;
                if(!vis[k])
                {
                    vis[kk]=1;
                    tail++;
                    q[tail]=k;
                }
            }
        }
    }
    //cout<<342432;
    for(i=1;i<=n;i++)
    {
		cout<<d[i]<<endl;
	}

	cout<<ans;
    return 0;
}