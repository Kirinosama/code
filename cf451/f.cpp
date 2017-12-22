#include <cstdlib>
#include <cstdio>
#include <cstring>
#include <iostream>
#include <algorithm>
using namespace std;

#define num(x) (x==-1?0:(s[x]-'0'))
#define MAXN 1000010
#define ii pair<int,int>
#define INF 0x3f3f3f3f
typedef long long ll;

string s;
int n;

bool add(int mid1,int mid2){
	int p1=mid1,p2=mid2,p3=n;
	int cur=0;
	while(p1!=-1 || p2!=-1 || p3!=-1){
		cur+=num(p1)+num(p2);
		if(cur%10!=num(p3)) return false;
		cur/=10;
		if(p1!=-1) p1--;
		if(p2!=-1) p2--;
		if(p3!=-1) p3--;
		if(p1==0) p1=-1;
		if(p2==mid1) p2=-1;
		if(p3==mid2) p3=-1;
	}
	if(!cur) return true;
	return false;
}

void print(int mid1,int mid2){
	for(int i=1;i<=mid1;i++) cout<<s[i];
	cout<<"+";
	for(int i=mid1+1;i<=mid2;i++) cout<<s[i];
	cout<<"=";
	for(int i=mid2+1;i<=n;i++) cout<<s[i];
}

int main(){
    freopen("cf451.in","r",stdin);
    cin>>s;n=s.length();s=' '+s;
    for(int i=1;i<=n-2;i++){
    	if(n-2*i<=i && add(i,n-i)){
    		print(i,n-i);return 0;
    	}
    	if(n-2*i-1<=i && add(i,n-i-1)){
    		print(i,n-i-1);return 0;
    	}
    	int rem=n-i;
    	if(rem/2>=i && add(i,i+rem/2)){
    		print(i,i+rem/2);return 0;
    	}
    }
    return 0;
}