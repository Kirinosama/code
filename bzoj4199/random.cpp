#include <iostream>
#include <cstring>
#include <cstdio>
#include <cstdlib>
#include <algorithm>
#include <ctime>
using namespace std;

int main(){
    freopen("bzoj4199.in","w",stdout);
    srand(time(0));
    int n=300000;
    cout<<n<<endl;
    for(int i=1;i<=n;i++)printf("%c",rand()%26+'a');
    cout<<endl;
    for(int i=1;i<=n;i++)printf("%d ",rand()%2000000001-1000000000);
    return 0;
}
