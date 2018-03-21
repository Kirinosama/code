#include<iostream>  
#include<cstdio>  
#include<vector>  
#include<stack>   
#include<cstring>  
#include<algorithm>  
using namespace std;  
const int maxn=10000+10;  
typedef pair<int,int> Edge;   
int Index=0,nblock=0;    
vector<bool> vis(maxn);      
vector<int> dfn(maxn),low(maxn);  
vector<vector<int> > G(maxn);  
vector<vector<Edge> > block(maxn);  
vector<Edge> st;  
void Tarjan(int u,int father)  
{  
    dfn[u]=low[u]=++Index;  
    vis[u]=true;  
    for(int i=0;i<G[u].size();i++)  
    {  
        int v=G[u][i];  
        if(!vis[v])  
        {  
            st.push_back(Edge(u,v));  
            Tarjan(v,u);  
            low[u]=min(low[u],low[v]);  
            if(dfn[u]<=low[v])       //发现u是割点   
            {  
                Edge tmp; nblock++;  
                do{  
                    tmp=st.back(); st.pop_back();  
                    block[nblock].push_back(tmp);  
                }while(!(tmp.first==u&&tmp.second==v));  
            }  
        }  
        else if(v!=father)  //不要父子边   
        {   
            low[u]=min(low[u],dfn[v]);  
            if(dfn[u]>dfn[v])  //连接到儿子的边已经入栈过了   
                st.push_back(Edge(u,v));  
        }  
    }  
}  
int main()  
{  
    freopen("123.in","r",stdin);
    int n,m;  
    cin>>n>>m;  
    while(m--){  
        int u,v;  
        cin>>u>>v;  
        G[u].push_back(v);  
        G[v].push_back(u);  
    }  
    Tarjan(1,0);  //联通的  
    for(int i=1;i<=nblock;i++)  
    {  
        cout<<"Block No:"<<i<<endl;  
        for(int j=0;j<block[i].size();j++)  
            cout<<block[i][j].first<<','<<block[i][j].second<<endl;  
    }  
    return 0;  
}   