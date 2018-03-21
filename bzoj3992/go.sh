g++ -o zhengjie bzoj3994.cpp
g++ -o baoli baoli2.cpp
g++ -o random random.cpp

for i in `seq 1 10000`;do
	./random
	./zhengjie > out1
	./baoli > out2
	if diff out1 out2 ; then
		echo "success"
	else 
		echo "wrong"
	fi
done