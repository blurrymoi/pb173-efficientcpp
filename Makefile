CC=clang++

ex1: ./ex/mainqueue.cpp
	$(CC) --std=c++14 -O2 -o ex1 ./ex/mainqueue.cpp

hw1: ./hw/mainhash.cpp
	$(CC) --std=c++14 -O2 -o hw1 ./hw/mainhash.cpp

