CC=clang++

ex1: ./ex/mainqueue.cpp
	$(CC) --std=c++14 -O2 -o ex1 ./ex/mainqueue.cpp
