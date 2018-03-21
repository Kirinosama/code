g++ -o random random.cpp
g++ -o baoli2 baoli2.cpp
g++ -o baoli baoli.cpp
g++ -o bzoj1023 bzoj1023.cpp

for i in `seq 1 10000`; do
	./random
	./bzoj1023
	./baoli2
	./baoli
	if diff out1 out2 && diff out1 out3;then
		echo "success"
	else 
		echo "wrong"
		exit
	fi
done
