g++ -o mine zkw_seg.cpp
g++ -o ac ac.cpp
g++ -o random random.cpp

for i in `seq 1 10000`;do
	./random
	time ./ac > out2
	time ./mine > out1
	if diff out1 out2;then
		echo "success"
	else
		echo "wrong"
		exit
	fi
done