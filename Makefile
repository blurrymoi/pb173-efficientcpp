CXX=clang++
BRICKS != ls bricks/brick-*
CXXFLAGS = --std=c++14 -g -O2

ex1: ./ex/mainqueue.cpp
	$(CXX) $(CXXFLAGS) -o ex1 ./ex/mainqueue.cpp

hw1: ./hw/mainhash.cpp
	$(CXX) $(CXXFLAGS) -o hw1 ./hw/mainhash.cpp

hw3: ./hw/matrix.cpp ./hw/matrix.hpp
	$(CXX) $(CXXFLAGS) -Ibricks -o hw3 ./hw/matrix.cpp

# hw2: BFS+benchmark
# ./hw2 | gnuplot

bench: bench.cpp $(BRICKS)

