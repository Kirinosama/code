g++ bzoj1895.cpp -o ac
g++ new.cpp -o mine
g++ random.cpp -o random

for i in `seq 1 10000`;do
	./random
	./ac > out1
	./mine > out2
	if diff out1 out2;then
		echo "success"
	else
		echo "wrong"
		exit
	fi
done
