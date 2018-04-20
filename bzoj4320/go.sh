g++ random.cpp -o random
g++ bzoj4320.cpp -o mine
g++ ac.cpp -o ac

for i in `seq 1 10000`;do
    ./random
    ./mine > out1
    ./ac > out2
    if diff out1 out2;then
        echo "success"
    else
        echo "wrong"
        exit
    fi
done
