CXX=clang++
BRICKS != ls bricks/brick-*
CXXFLAGS = -g -O2

ex1: ./ex/mainqueue.cpp
	$(CXX) --std=c++14 -O2 -o ex1 ./ex/mainqueue.cpp

hw1: ./hw/mainhash.cpp
	$(CXX) --std=c++14 -O2 -o hw1 ./hw/mainhash.cpp

hw3: ./hw/matrix.cpp
	$(CXX) --std=c++14 -O2 -o hw3 ./hw/matrix.cpp

# hw2: BFS+benchmark
# ./hw2 | gnuplot

bench: bench.cpp $(BRICKS)

