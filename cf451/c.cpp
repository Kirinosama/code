#include <cstdlib>
#include <cstdio>
#include <cstring>
#include <iostream>
#include <algorithm>
#include <map>
#include <vector>
using namespace std;

#define ii pair<int,int>
#define INF 0x3f3f3f3f
typedef long long ll;

map <string,int> mp1;
map <int,string> mp2;
vector <string> v[25];

string s,s1;
int x,n,name_cnt;

bool cmp(const string &a,const string &b){
	return a.length()>b.length();
}

bool belong (string t1,string t2){
	int l=t1.length()-1,r=t2.length()-1;
	while(l>=0 && t1[l]==t2[r])
		l--,r--;
	if(l==-1) return true;
	return false;
}

void solve(vector <string> v,string s2){
	vector <string> t;
	cout<<s2<<' ';
	for(int i=0;i<v.size();i++){
		bool flag=false;
		for(int j=0;j<i;j++)
			if(belong(v[i],v[j])){
				flag=true;break;
			}
		if(!flag)
			t.push_back(v[i]);
	}
	cout<<t.size()<<' ';
	for(int i=0;i<t.size();i++){
		cout<<t[i];
		if(i!=t.size()-1) cout<<' ';
	}
	cout<<endl;
}

int main(){
    freopen("cf451.in","r",stdin);
    scanf("%d",&n);
    for(int i=1;i<=n;i++){
    	cin>>s;
    	if(!mp1[s]){
    		mp1[s]=++name_cnt;
    		mp2[name_cnt]=s;
    	}
    	scanf("%d",&x);
    	for(int j=1;j<=x;j++){
    		cin>>s1;
    		v[mp1[s]].push_back(s1);
    	}
    }
    cout<<name_cnt<<endl;
    for(int i=1;i<=name_cnt;i++){
    	sort(v[i].begin(),v[i].end(),cmp);
		solve(v[i],mp2[i]);
	}
    return 0;
}