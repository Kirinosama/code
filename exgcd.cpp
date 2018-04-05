void exgcd(int a,int b,int &d,int &x,int &y){
	if(!b){
		d=a,x=1,y=0;
	}else{
		exgcd(b,a%b,d,y,x);
		y-=(a/b)*x;
	}
} 

int inv(int p,int q){
	int d,x,y;
	exgcd(p,q,d,x,y);
	return d==1?(x+q)%q:-1;
}
