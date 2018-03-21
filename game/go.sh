g++ -o game game.cpp
g++ -o ac ac.cpp
g++ -o random random.cpp

for i in `seq 1 10000`;do
	./random
	./game
	./ac > out
	if diff out game.out;then
		echo "success"
	else
		echo "wrong"
		exit
	fi
done