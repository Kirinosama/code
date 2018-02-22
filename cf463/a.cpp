#include <cstdlib>
#include <cstdio>
#include <cstring>
#include <iostream>
#include <algorithm>
using namespace std;

#define ii pair<int,int>
#define INF 0x3f3f3f3f
typedef long long ll;

string s;

int main(){
    freopen("cf463.in","r",stdin);
    cin>>s;cout<<s;
    for(int i=s.length()-1;i>=0;i--) cout<<s[i];
    return 0;
}