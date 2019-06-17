nsmallest: nsmallest.cpp
	g++ -O3 -Wall -shared -std=c++11 -fPIC `python3 -m pybind11 --includes` nsmallest.cpp -o nsmallest`python3-config --extension-suffix`

clean:
	rm nsmallest`python3-config --extension-suffix`