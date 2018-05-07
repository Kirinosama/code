#include <cstdlib>
#include <cstdio>
#include <cstring>
#include <iostream>
#include <algorithm>
using namespace std;

#define MAXN 3010
#define ii pair<int,int>
#define INF 0x3f3f3f3f
typedef long long ll;

int cnt[MAXN],rk[MAXN],sa[MAXN],sa2[MAXN],height[MAXN];
int n;
string s;

bool same(int *a,int x,int y,int z){
    return a[x]==a[y] && a[x+z]==a[y+z];
}

void build_sa(int m){
    for(int i=0;i<m;i++)cnt[i]=0;
    for(int i=0;i<n;i++)cnt[rk[i]=s[i]]++;
    for(int i=1;i<m;i++)cnt[i]+=cnt[i-1];
    for(int i=n-1;i>=0;i--)sa[--cnt[rk[i]]]=i;
    for(int gap=1;gap<n;gap<<=1){
        int p=0;
        for(int i=n-gap;i<n;i++)sa2[p++]=i;
        for(int i=0;i<n;i++)if(sa[i]>=gap)
            sa2[p++]=sa[i]-gap;
        for(int i=0;i<m;i++)cnt[i]=0;
        for(int i=0;i<n;i++)cnt[rk[i]]++;
        for(int i=1;i<m;i++)cnt[i]+=cnt[i-1];
        for(int i=n-1;i>=0;i--)sa[--cnt[rk[sa2[i]]]]=sa2[i];
        swap(rk,sa2);rk[sa[0]]=0;
        for(int i=1;i<n;i++)rk[sa[i]]=rk[sa[i-1]]+!same(sa2,sa[i],sa[i-1],gap);
        m=rk[sa[n-1]]+1;if(n==m) return;
    }
}

void build_height(){
    for(int i=0;i<n;i++)rk[sa[i]]=i;
    int k=0;
    for(int i=0;i<n-1;i++){
        if(k)k--;
        int j=sa[rk[i]-1];
        while(s[i+k]==s[j+k])k++;
        height[rk[i]]=k;
    }
}

int main(){
    freopen("bzoj2251.in","r",stdin);
    cin>>n>>s;s+='\n';n++;
    build_sa('1'+1);
    build_height();
    for(int i=1;i<n;i++){
        for(int j=sa[i];j<n-1;j++)
            printf("%c",s[j]);
        printf(" %d",height[i]);
        cout<<endl;
    }
    return 0;
}