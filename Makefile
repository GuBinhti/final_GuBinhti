all: testbst

testbst:bst.cpp testbst.cpp
	g++ -std=c++11 -g bst.cpp testbst.cpp -o test
	
clean:
	rm *.o test