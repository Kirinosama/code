#include <cstdlib>
#include <cstdio>
#include <cstring>
#include <iostream>
#include <algorithm>
#include <map>
using namespace std;

typedef long long ll;

map <char,int> mp;

int w[5][5],ans,l1,l2,a,b;
int f[3010][3010][4];
string s1,s2;

int main(){
	freopen("bzoj5107.in","r",stdin);
	cin>>s1>>s2;l1=s1.length(),l2=s2.length();
	s1=' '+s1;s2=' '+s2;
	for(int i=1;i<=4;i++)
		for(int j=1;j<=4;j++)
			scanf("%d",&w[i][j]);
	mp['A']=1,mp['T']=2,mp['G']=3,mp['C']=4;
	scanf("%d %d",&a,&b);
	memset(f,0xc0,sizeof(f));
	f[0][0][3]=0;
	for(int i=0;i<=l1;i++)
		for(int j=0;j<=l2;j++){
			int c=w[mp[s1[i]]][mp[s2[j]]];
			if(j-1>=0){
				f[i][j][1]=max(f[i][j][1],f[i][j-1][3]-a);
				f[i][j][1]=max(f[i][j][1],f[i][j-1][2]-a);
				f[i][j][1]=max(f[i][j][1],f[i][j-1][1]-b);
			}
			if(i-1>=0){
				f[i][j][2]=max(f[i][j][2],f[i-1][j][3]-a);
				f[i][j][2]=max(f[i][j][2],f[i-1][j][2]-b);
				f[i][j][2]=max(f[i][j][2],f[i-1][j][1]-a);
			}
			if(i-1>=0 && j-1>=0){
				f[i][j][3]=max(f[i][j][3],f[i-1][j-1][3]+c);
				f[i][j][3]=max(f[i][j][3],f[i-1][j-1][1]+c);
				f[i][j][3]=max(f[i][j][3],f[i-1][j-1][2]+c);
			}
		}
	ans=0xefefefef;
	ans=max(ans,f[l1][l2][3]);
	ans=max(ans,f[l1][l2][2]);
	ans=max(ans,f[l1][l2][1]);
	cout<<ans;
	return 0;
}
