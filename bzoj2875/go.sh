g++ -o run1 bzoj2875.cpp
g++ -o run2 ac.cpp
g++ -o test test.cpp

for i in `seq 1 10000` ; do
	./run1 > out1
	./run2 > out2
	./test
	if diff out1 out2 ;then
		echo "success"
	else
		echo "wrong" 
		exit
	fi
done	