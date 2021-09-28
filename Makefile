main:
	c++ -O3 -Wall -shared -std=c++17 -undefined dynamic_lookup `python3 -m pybind11 --includes` main.cpp -o nano2`python3-config --extension-suffix`