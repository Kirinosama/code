g++ random.cpp -o random
g++ point.cpp -o ac
g++ baoli.cpp -o baoli

for i in `seq 1 10000`;do
	./random
	./ac > out1
	./baoli > out2
	if diff out1 out2;then
		echo "success"
	else
		echo "wrong"
		exit
	fi
done
