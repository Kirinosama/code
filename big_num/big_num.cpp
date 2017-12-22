#include <cstdlib>
#include <cstdio>
#include <cstring>
#include <iostream>
#include <algorithm>
using namespace std;

#define MAXN 10010

struct bign{
	int len,s[MAXN];
	void clean(){
		len=0;
		memset(s,0,sizeof(s));
	}
	void in(){
		clean();
		string t;
		cin>>t;len=t.length();
		for(int i=0;i<len;i++)
			s[i]=t[len-1-i]-'0';
	}
	void print(){
		for(int i=len-1;i>=0;i--)
			printf("%d",s[i]);
		cout<<endl;
	}
	bool operator < (const bign &b){
		if(len<b.len) return true;
		if(len>b.len) return false;
		for(int i=len-1;i>=0;i--)
			if(s[i]<b.s[i]) return true;
		return false;
	}
	bign operator + (const bign &b){
		bign c;c.clean();
		for(int i=0;i<max(len,b.len)+10;i++){
			c.s[i]+=s[i]+b.s[i];
			if(c.s[i]>=10){
				c.s[i+1]+=c.s[i]/10;
				c.s[i]%=10;
			}
		}
		for(int i=max(len,b.len)+10;i>=0;i--)
			if(c.s[i]){
				c.len=i+1;break;
			}
		return c;
	}
	bign operator - (const bign &b){
		bign c;c.clean();
		for(int i=0;i<len;i++){
			c.s[i]+=s[i]-b.s[i];
			if(c.s[i]<0){
				c.s[i]+=10;
				c.s[i+1]-=1;
			}
		}
		for(int i=len-1;i>=0;i--)
			if(c.s[i]){
				c.len=i+1;break;
			}
		return c;
	}
	//x+x/10<=MAX_INT
	bign operator * (int x){
		bign c;c.clean();
		for(int i=0;i<len+20;i++){
			c.s[i]+=x*s[i];
			if(c.s[i]>10){
				c.s[i+1]+=c.s[i]/10;
				c.s[i]%=10;
			}
		}
		for(int i=len+20;i>=0;i--){
			if(c.s[i]){
				c.len=i+1;break;
			}
		}
		return c;
	}
	bign operator / (int x){
		int res=0;bign c;c.clean();
		for(int i=0;i<len;i++){
			res=res*10+s[i];
			if(res>x){
				c.s[c.len++]=res/x;
				res%=x;
			}
		}
		for(int i=len-1;i>=0;i--){
			if(c.s[i]){
				len=i+1;break;
			}
		}
		return c;
	}
}a,b;

int main()
{
    freopen("big_num.in","r",stdin);
    a.in();b.in();
    return 0;
}