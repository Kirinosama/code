#include <cstdlib>
#include <cstdio>
#include <cstring>
#include <iostream>
#include <algorithm>
#include <map>
using namespace std;
   
#define MOD 40031
#define MAXN 2010
#define ii pair<int,int>
#define INF 0x3f3f3f3f
typedef long long ll;
   
int n,maxlen;
int Pow1[MAXN],Pow2[MAXN];
int a[6][3][MAXN];
string s[6];
   
void solve(string s,int *A1,int *A2){
    int cur1=0,cur2=0;
    for(int i=0;i<s.length();i++){
        cur1=(cur1*241+s[i])%MOD;
        cur2=(cur2*307+s[i])%MOD;
        A1[i]=cur1,A2[i]=cur2;
    }
}
   
int gethash1(int *A,int l,int r){
    if(!l) return A[r];
    else{
        int sum=A[r]-(A[l-1]*Pow1[r-l+1])%MOD;
        if(sum<0) sum+=MOD;
        return sum;
    }
}
   
int gethash2(int *A,int l,int r){
    if(!l) return A[r];
    else{
        int sum=A[r]-(A[l-1]*Pow2[r-l+1])%MOD;
        if(sum<0) sum+=MOD;
        return sum;
    }
}
  
bool judge(int len){
    map <ii,int> mp;
    if(n==1) return true;
    for(int i=0;i<=s[1].length()-len;i++)
        mp[ii(gethash1(a[1][1],i,i+len-1),gethash2(a[1][2],i,i+len-1))]=1;
    for(int i=2;i<=n;i++){
        for(int j=0;j<=s[i].length()-len;j++){
            int cur1=gethash1(a[i][1],j,j+len-1);
            int cur2=gethash2(a[i][2],j,j+len-1);
            map <ii,int> :: iterator it=mp.find(ii(cur1,cur2));
            if(it!=mp.end()){
                if(it->second<i){
                    if(it->second==i-1){
                        it->second=i;
                        if(i==n) return true;
                    }
                    else mp.erase(it);
                }
            }
        }
    }
    return false;
}
   
int main(){
    //freopen("bzoj2946.in","r",stdin);
    cin>>n;maxlen=INF;Pow1[0]=Pow2[0]=1;
    for(int i=1;i<=2000;i++){
        Pow1[i]=(Pow1[i-1]*241)%MOD;
        Pow2[i]=(Pow2[i-1]*307)%MOD;
    }
    for(int i=1;i<=n;i++){
        cin>>s[i],solve(s[i],a[i][1],a[i][2]);
        maxlen=min(maxlen,(int)s[i].length());
    }
    for(int i=maxlen;i>=1;i--)if(judge(i)){
        printf("%d\n",i);return 0;
    }
    printf("0\n");
    return 0;
}
