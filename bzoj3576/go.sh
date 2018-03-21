g++ -o mine bzoj3576.cpp
g++ -o ac ac.cpp
g++ -o random random.cpp

for i in `seq 1 10000`;do
	./random
	./ac < bzoj3576.in > out2
	./mine > out1
	if diff out1 out2;then
		echo "success"
	else
		echo "wrong"
		exit
	fi
done