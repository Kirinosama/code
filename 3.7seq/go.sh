g++ -o mine 3.7seq.cpp

./mine < seq1.in > out1
	if diff out1 seq1.out;then
		echo "success"
	else
		echo "wrong"
	fi

	./mine < seq2.in > out1
	if diff out1 seq2.out;then
		echo "success"
	else
		echo "wrong"
	fi

	./mine < seq3.in > out1
	if diff out1 seq3.out;then
		echo "success"
	else
		echo "wrong"
	fi

	./mine < seq4.in > out1
	if diff out1 seq4.out;then
		echo "success"
	else
		echo "wrong"
	fi

	./mine < seq5.in > out1
	if diff out1 seq5.out;then
		echo "success"
	else
		echo "wrong"
	fi

	./mine < seq6.in > out1
	if diff out1 seq6.out;then
		echo "success"
	else
		echo "wrong"
	fi


	./mine < seq7.in > out1
	if diff out1 seq7.out;then
		echo "success"
	else
		echo "wrong"
	fi

	./mine < seq8.in > out1
	if diff out1 seq8.out;then
		echo "success"
	else
		echo "wrong"
	fi

	./mine < seq9.in > out1
	if diff out1 seq9.out;then
		echo "success"
	else
		echo "wrong"
	fi

	./mine < seq10.in > out1
	if diff out1 seq10.out;then
		echo "success"
	else
		echo "wrong"
	fi

