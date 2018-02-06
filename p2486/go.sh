g++ -o mine p2486.cpp
g++ -o random random.cpp
g++ -o ac ac.cpp

for i in `seq 1 10000`;do
	./random
	./ac < p2486.in > out2
	./mine > out1
	if diff out1 out2;then
		echo "success"
	else
		echo "wrong"
		exit
	fi
done