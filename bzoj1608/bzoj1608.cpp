#include<bits/stdc++.h>  
using namespace std;  
const int maxn = 200000+5;  
int T,n,a[maxn],pre[maxn],nex[maxn];  
map<int,int> cur ;  
bool is_unique(int p,int l,int r){  
    return pre[p]<l&&nex[p]>r;  
}  
bool check(int l,int r){  
    if(l>=r) return true;  
    for(int i=l;i-l<=r-i;i++){ //折半递归  
        if(is_unique(i,l,r)){  
            return check(i+1,r)&&check(l,i-1);  
        }  
        if(is_unique(r-i+l,l,r))  
            return check(r-i+l+1,r)&&check(l,r-i+l-1);  
    }  
    return false;  
}  
int main(){  
    scanf("%d",&T);  
    while(T--){  
        scanf("%d",&n);  
        for(int i=0;i<n;i++) scanf("%d",&a[i]);  
        cur.clear();  
        for(int i=0;i<n;i++){  
            if(!cur.count(a[i])) pre[i] = -1;  
            else pre[i] = cur[a[i]];  
            cur[a[i]] = i;  
        }  
        cur.clear();  
        for(int i=n-1;i>=0;i--){  
            if(!cur.count(a[i])) nex[i] = n;  
            else nex[i] = cur[a[i]];  
            cur[a[i]] = i;  
        }  
        if(check(0,n-1)) printf("non-boring\n");  
        else printf("boring\n");  
    }  
    return 0;  
}  

