#include <cstdlib>
#include <cstdio>
#include <cstring>
#include <iostream>
#include <algorithm>
using namespace std;

int n;

int main(){
	freopen("win.in","r",stdin);
	freopen("win.out","w",stdout);
	while(1){
		cin>>n;
		if(!n) break;
		if(n%2) printf("Bob\n");
		else printf("Alice\n");
	}
	return 0;
}
