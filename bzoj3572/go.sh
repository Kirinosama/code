g++ -o mine bzoj3572.cpp
g++ -o ac ac.cpp
g++ -o random random.cpp

for i in `seq 1 10000`;do
	./random
	./mine
	./ac
	if diff out1 out2;then
		echo "success"
	else
		echo "wrong"
		exit
	fi
done