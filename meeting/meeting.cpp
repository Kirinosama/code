#include <cstdlib>
#include <cstdio>
#include <cstring>
#include <iostream>
#include <algorithm>
using namespace std;

#define ii pair<int,int>
#define INF 0x3f3f3f3f
typedef long long ll;

string s;
int n,t;

int make(int gap){
    int res=0;
    if(gap*3==n){
        for(int i=0;i<n/3;i++)if(s[i]==s[(i+gap)%n] && s[i]==s[(i+2*gap)%n])
            res++;
    }else{
        for(int i=0;i<n;i++)if(s[i]==s[(i+gap)%n] && s[i]==s[(i+2*gap)%n])
            res++;
    }
    return res;
}

int main(){
    freopen("meeting.in","r",stdin);
    freopen("meeting.out","w",stdout);
    cin>>t;
    for(int j=1;j<=t;j++){
        int ans=0;
        cin>>s;n=s.length();
        for(int i=1;i<(n+1)/2;i++)ans+=make(i);
        printf("Case %d: %d\n",j,ans);
    }
    return 0;
}
