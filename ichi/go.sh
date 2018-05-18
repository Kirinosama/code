g++ ichi1.cpp -o lyc
g++ ichi.cpp -o wqs
g++ random.cpp -o random
for i in `seq 1 10000`;do
	./random
	time ./wqs > out1
	time ./lyc > out2
	if diff out1 out2;then
		echo "success"
	else
		echo "wrong"
		exit
	fi
done
