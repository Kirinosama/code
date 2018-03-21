g++ -o random random.cpp
g++ -o mine bzoj3631.cpp

for i in `seq 1 10000`;do
	./random
	./mine > out1
	echo "success"
done