#include <cstdlib>
#include <cstdio>
#include <cstring>
#include <iostream>
#include <algorithm>
using namespace std;

int main()
{
	freopen("input","r",stdin);
	int a=1048576;
	int b=1048575;
	int c=a^b;
	cout<<c;
	return 0;
}