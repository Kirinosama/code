#include <cstdlib>
#include <cstdio>
#include <cstring>
#include <iostream>
#include <algorithm>
#include <vector>
using namespace std;

vector<char>STRING(int n);

int main()
{
	int n;
	while (~scanf("%d", &n))
	{
	   	vector<char>s = STRING(n);
       		int len=s.size(); int m = 0;
		for(int i = 0, j = 0; i < len; i++)
			if(!i || s[i] == s[i - 1]) j++;
			else m += (len - i) * j, j = 1;
		if(m != n) cout << "Wrong Answer!" << endl;
		else {
			cout << "Your Answer is ok, but I'm not sure if it is the shortest one" << endl;
		}
	}
	return 0;
}

