#include <cstdlib>
#include <cstdio>
#include <cstring>
#include <algorithm>
#include <iostream>
#include <ctime>
using namespace std;

int main(){
    freopen("bzoj1492.in","w",stdout);
    srand(time(0));
    int n=rand()%100+1;int k=100;
    cout<<n<<' '<<k<<endl;
    for(int i=1;i<=n;i++){
        printf("%d %d %d\n",rand()%10+1,rand()%10+1,rand()%100+1);
    }
    return 0;
}
