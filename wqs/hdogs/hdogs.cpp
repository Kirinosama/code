#include <cstdlib>
#include <cstdio>
#include <cstring>
#include <iostream>
#include <algorithm>
using namespace std;

#define ii pair<int,int>
#define INF 0x3f3f3f3f
typedef long long ll;

int T;

int f(int x,int y){
    if(x%y==0) return 0;
    if(y==1) return 0;
    if(x>y) return f(x%y,y);
    if(y%x==0) return x*(y/x-1);
    else return y/x*x+f(x,y-y/x*x);
}

int main(){
    freopen("hdogs.in","r",stdin);
    freopen("hdogs.out","w",stdout);
    cin>>T;
    while(T--){
        int x,y;scanf("%d%d",&x,&y);
        cout<<f(x,y)<<endl;
    }
    return 0;
}
