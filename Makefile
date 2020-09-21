opt = -std=c++11

a: *.cpp
	g++ $^ -o $@ $(opt)
