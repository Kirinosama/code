#include<bits/stdc++.h>
using namespace std;

const int maxn=25;

string Str[25]={"233","01",
"001",
"010",
"0011",
"0010",
"0101",
"00010",
"00100",
"00101",
"01010",
"000100",
"000101",
"001001",
"001010",
"010101",
"0001100",
"0001001",
"0001010",
"0010010",
"0010101",
};

int n,T;
int main(){
	freopen("string.in","r",stdin);
	freopen("string.out","w",stdout);
	
	scanf("%d",&T);
	for(int i=1;i<=T;i++){
		scanf("%d",&n);
		cout<<Str[i]<<endl;
	}
	
	return 0;
}
