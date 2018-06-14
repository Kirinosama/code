#include <bits/stdc++.h>
using namespace std;

struct node{
	node *ls,*rs;
	int val;
}*rt;

int main(){
	rt=new node;
	node *&p=rt;
	p=NULL;
	printf("%d",rt?1:0);
	return 0;
}
