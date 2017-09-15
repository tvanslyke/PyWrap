objects = py_iterator.o Main.o py_object_base.o py_wrap_exception.o py_sequence_iterator.o
objects_no_main = py_iterator.o  py_object_base.o py_wrap_exception.o py_sequence_iterator.o

pycpp: $(objects)
	g++-7 -I./Include -I/usr/include/python3.5 -std=c++17 $(objects) -lpython3.5m -o pycpp
Main.o: ./src/Main.cpp $(objects_no_main) ./Include/py_object.h
	g++-7 -I./Include -I/usr/include/python3.5 -std=c++17 $(objects_no_main) src/Main.cpp -lpython3.5m -c
py_iterator.o: ./Include/py_iterator.h ./src/py_iterator.cpp
	g++-7 -I./Include -I/usr/include/python3.5 -std=c++17 src/py_iterator.cpp -lpython3.5m -c
py_object_base.o: ./Include/py_object_base.h src/py_object_base.cpp 
	g++-7 -I./Include -I/usr/include/python3.5 -std=c++17 src/py_object_base.cpp -lpython3.5m -c
py_wrap_exception.o: ./Include/py_wrap_exception.h py_object_base.o 
	g++-7 -I./Include -I/usr/include/python3.5 -std=c++17 src/py_wrap_exception.cpp -lpython3.5m -c
	
py_sequence_iterator.o: ./Include/py_sequence_iterator.h ./Include/py_sequence.h ./Include/py_utils.h py_wrap_exception.o 
	g++-7 -I./Include -I/usr/include/python3.5 -std=c++17 py_wrap_exception.o src/py_sequence_iterator.cpp -lpython3.5m -c


clean:
	rm $(objects)
	
