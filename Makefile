CXX=clang++

ex1: ./ex/mainqueue.cpp
	$(CXX) --std=c++14 -O2 -o ex1 ./ex/mainqueue.cpp

hw1: ./hw/mainhash.cpp
	$(CXX) --std=c++14 -O2 -o hw1 ./hw/mainhash.cpp

