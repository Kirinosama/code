g++ -o mine bzoj2908.cpp
g++ -o ac ac.cpp
g++ -o random random.cpp

for i in `seq 1 10000` ;do
	./random
	./ac < bzoj2908.in > out1
	./mine > out2
	if diff out1 out2;then
		echo "success"
	else
		echo "wrong"
		exit
	fi
done