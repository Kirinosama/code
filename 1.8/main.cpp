#include <cstdlib>
#include <cstdio>
#include <cstring>
#include <iostream>
#include <algorithm>
using namespace std;

int n;

int main(){
	freopen("input","r",stdin);
	while(1){
		cin>>n;
		if(!n) break;
		if(n%2) printf("Bob\n");
		else printf("Alice\n");
	}
	return 0;
}
