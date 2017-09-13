#include "py_iter.h"
#include "py_object.h"
#include "py_iterator.h"

namespace py{

py_iterator::py_iterator(PyObject* iterable):
	iter_{py_new_reference(PyObject_GetIter(iterable))}
{
	value_ = PyIter_Next(iter_);
}
py_iterator::py_iterator(PyObject* iter, PyObject* value):
	iter_{py_borrowed_reference(iter)}, value_{py_borrowed_reference(value)}
{

}
	
py_iterator::self_type& py_iterator::operator++()
{
	value_ = iter_.Next();
	return *this;
}
py_iterator::self_type py_iterator::operator++(int)
{
	auto cpy = *this;
	++(*this);
	return cpy;
}

py_iterator::reference py_iterator::operator*()
{
	return value_;
}
py_iterator::pointer py_iterator::operator->()
{
	return &(value_);
}

bool py_iterator::operator!=(const py_iterator& other)
{
	return value_ != other.value_;
}
	
} /* namespace py */
