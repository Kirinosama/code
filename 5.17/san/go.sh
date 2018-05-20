g++ san.cpp -o wqs
g++ san1.cpp -o lyc
g++ random.cpp -o random

for i in `seq 1 10000`;do
	 ./random
	 time ./wqs > out1
	 ./lyc > out2
	 if diff out1 out2;then
		echo "success"
	else
		echo "wrong"
		exit
	fi
done
