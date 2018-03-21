g++ -o mine bzoj2946.cpp
g++ -o random random.cpp
g++ -o ac ac.cpp

for i in `seq 1 10000`;do
	./random
	./mine > out1
	./ac > out2
	if diff out1 out2;then
		echo "success"
	else
		echo "wrong"
		exit
	fi
done