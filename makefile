objects = py_iterator.o Main.o

pycpp: $(objects)
	g++-7 -I./Include -std=c++17 $(objects) -lpython3.5m -o pycpp
Main.o: ./src/Main.cpp py_iterator.o ./Include/py_object.h
	g++-7 -I./Include -std=c++17 py_iterator.o src/Main.cpp -lpython3.5m -c
py_iterator.o: ./Include/py_iterator.h ./src/py_iterator.cpp
	g++-7 -I./Include -std=c++17 src/py_iterator.cpp -lpython3.5m -c

clean:
	rm $(objects)
	
