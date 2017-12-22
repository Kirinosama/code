#include <cstdlib>
#include <cstdio>
#include <cstring>
#include <iostream>
#include <algorithm>
using namespace std;

inline int read(){
	int x,w=0;char ch=0;
	while(ch<'0' || ch>'9')
		w|=(ch=='-'),ch=getchar();
	while(ch>='0' && ch<='9')
		x=(x<<1)+(x<<3)+(ch^48),ch=getchar();
	return w ? -x : x;
}

int main(){
	int x=read();
	cout<<x;
	return 0;
}