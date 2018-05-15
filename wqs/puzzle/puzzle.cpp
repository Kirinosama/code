#include <cstdlib>
#include <cstdio>
#include <cstring>
#include <iostream>
#include <algorithm>
using namespace std;

#define ii pair<int,int>
#define INF 0x3f3f3f3f
typedef long long ll;

int n,f[30][210],T;
string s;

int getsum(int l,int r){
    int sum=0;
    for(int i=l;i<=r;i++){
        sum=sum*10+s[i]-'0';
        if(sum>200) return 201;
    }
    return sum;
}

int main(){
    freopen("puzzle.in","r",stdin);
    freopen("puzzle.out","w",stdout);
    while(1){
        cin>>s>>T;if(T<0) break;
        n=s.length();
        memset(f,0x3f,sizeof(f));
        for(int i=0;i<n;i++)if(getsum(0,i)<=T)
            f[i][getsum(0,i)]=0;
        for(int i=1;i<n;i++){
            for(int j=0;j<i;j++){
                for(int k=0;k<=T;k++){
                    if(k-getsum(j+1,i)>=0) f[i][k]=min(f[i][k],f[j][k-getsum(j+1,i)]+1);
                    if(j<i-1){
                        for(int z=j+1;z<=i-1;z++)if(k-getsum(j+1,z)*getsum(z+1,i)>=0){
                            f[i][k]=min(f[i][k],f[j][k-getsum(j+1,z)*getsum(z+1,i)]+2);
                        }
                    }
                }
            }
        }
        printf("%d\n",f[n-1][T]==INF?-1:f[n-1][T]);
    }
    return 0;
}
