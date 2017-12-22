#include <cstdlib>
#include <cstdio>
#include <cstring>
#include <iostream>
#include <algorithm>
#include <map>
using namespace std;

#define MAXN 500010

map <char,int> mp;
int n,cnt,to[2][20],ans;
int num[4];

struct opearation{
	int type,x;
	void in(){
		char c;
		scanf("%c %d\n",&c,&x);
		type=mp[c];
	}
}s[MAXN];

int solve(int x){
	for(int i=1;i<=n;i++){
		if(s[i].type==1) x=x&s[i].x;
		else if(s[i].type==2) x=x|s[i].x;
		else x=x^s[i].x;
	}
	return x;
}

int main()
{
    freopen("ShortProgram.in","r",stdin);
    scanf("%d\n",&n);mp['&']=1;mp['|']=2;mp['^']=3;
    for(int i=1;i<=n;i++) s[i].in();
    for(int i=1;i<=512;i<<=1){
    	cnt++;
    	if(solve(0)&i) to[0][cnt]=1;
    	else to[0][cnt]=0;
    	if(solve(i)&i) to[1][cnt]=1;
    	else to[1][cnt]=0;
    }
    int mul=1;num[1]=1023;
    for(int i=1;i<=10;i++){
    	if(to[0][i] && to[1][i]) num[2]+=mul;
    	else if(!to[0][i] && !to[1][i]) num[1]-=mul;
    	else if(to[0][i] && !to[1][i]) num[3]+=mul;
    	mul<<=1;
    }
    ans=1;
    for(int i=2;i<=3;i++){
    	if(num[i]) ans++;
    }
    cout<<ans<<endl;
    cout<<'&'<<' '<<num[1]<<endl;
    if(num[2]) cout<<'|'<<' '<<num[2]<<endl;
    if(num[3]) cout<<'^'<<' '<<num[3]<<endl;
    //for(int i=0;i<=1023;i++)
  // cout<<solve(3)<<' '<<(((3&num[1])|num[2])^num[3])<<endl;
    return 0;
}