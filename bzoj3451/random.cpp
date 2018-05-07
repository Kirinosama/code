#include <iostream>
#include <cstring>
#include <cstdio>
#include <cstdlib>
#include <algorithm>
#include <ctime>
using namespace std;

int main(){
    freopen("bzoj3451.in","w",stdout);
    srand(time(0));
    int n=300;cout<<n<<endl;
    for(int i=1;i<n;i++){
        printf("%d %d\n",i,rand()%i);
    }
    return 0;
}
