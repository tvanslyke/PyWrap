#ifndef PY_ITERATOR_H
#define PY_ITERATOR_H


#include <iterator>
#include <type_traits>
#include <Python.h>
#include <structmember.h>


namespace py{
class py_object;
class py_iter;
class py_new_reference;
class py_borrowed_reference;


class py_iterator
{
public:
	using iterator_category = std::input_iterator_tag;
	using value_type = PyObject*;
	using pointer = py_object*;
	using reference = py_object&;
	using difference_type = ptrdiff_t;
	using self_type = py_iterator;
	static const py_iterator& end_sentinal();
	py_iterator(PyObject* iterable);
	py_iterator(PyObject* iter, PyObject* value);
	self_type& operator++();
	self_type operator++(int);
	reference operator*();
	pointer operator->();
	bool operator !=(const py_iterator& other);
	
private:
	py_object iter_;
	py_object value_;
};


} /* namespace py */


#endif /* PY_ITERATOR_H */


