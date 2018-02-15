g++ -o mine bzoj3083.cpp
g++ -o ac ac.cpp
g++ -o random random.cpp

for i in `seq 1 10000`; do
	./random
	./ac < bzoj3083.in > out2
	./mine
	if diff out1 out2;then
		echo "success"
	else
		echo "wrong"
		exit
	fi
done