g++ -o mine bzoj1316.cpp
g++ -o ac ac.cpp
g++ -o random random.cpp

for i in `seq 1 10000`;do
	./random
	time ./ac < bzoj1316.in > out2
	time ./mine > out1
	if diff out1 out2;then
		echo "success"
	else
		echo "wrong"
		exit
	fi
done