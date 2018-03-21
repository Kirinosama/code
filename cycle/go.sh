g++ -o cycle cycle.cpp
g++ -o ac ac.cpp
g++ -o random random.cpp

for i in `seq 1 10000`;do
	./random
	./cycle
	./ac > out
	if diff out cycle.out;then
		echo "success"
	else
		echo "wrong"
		exit
	fi
done