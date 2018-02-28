g++ -o baoli bzoj3620baoli.cpp
g++ -o mine bzoj3620.cpp
g++ -o random random.cpp

for i in `seq 1 10000`;do
	./random
	./baoli > out2
	./mine > out1
	if diff out1 out2;then
		echo "success"
	else
		echo "wrong"
		exit
	fi
done