#include <cstdlib>
#include <cstdio>
#include <cstring>
#include <algorithm>
#include <iostream>
#include <ctime>
using namespace std;

int main(){
	freopen("number.in","w",stdout);
	srand(time(0));
	int t=10000;
	cout<<t<<endl;
	for(int i=1;i<=t;i++)printf("%d\n",rand()%200001);
	return 0;
}
