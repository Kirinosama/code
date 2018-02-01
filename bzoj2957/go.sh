g++ -o mine bzoj2957.cpp
g++ -o ac ac.cpp
g++ -o random random.cpp

for i in `seq 1 10000`;do
	./random
	./mine > out1
	./ac < bzoj2957.in > out2
	if diff out1 out2;then
		echo "success"
	else
		echo "wrong"
		exit
	fi
done