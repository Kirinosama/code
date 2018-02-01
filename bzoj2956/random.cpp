#include <iostream>
#include <ctime>
using namespace std;

int main(){
	freopen("bzoj2956.in","w",stdout);
	srand(time(0));
	cout<<rand()%(1000000000)+1<<' '<<rand()%(1000000000)+1<<endl;
	return 0;
}