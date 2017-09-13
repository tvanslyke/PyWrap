#include "py_iter.h"
#include "py_object.h"
#include "py_iterator.h"
#include "py_utils.h"
namespace py{

py_iterator::py_iterator(PyObject* iterable):
	iter_{py_object_base(iterable).GetIter()}, value_{nullptr}
{
	if(not iter_)
		throw std::runtime_error("Null pointer recieved from "
					 "call to PyObject_GetIter in py_iterator constructor.");
	value_ = py_iter(iter_).Next();
}
py_iterator::py_iterator(PyObject* iter, PyObject* value):
	iter_{py_borrowed_reference(iter)}, value_{py_borrowed_reference(value)}
{

}
	
py_iterator::self_type& py_iterator::operator++()
{
	value_ = py_iter(iter_).Next();
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



const py_iterator& py_iterator::end_sentinal()
{
	static const py_iterator sentinal{nullptr, nullptr};
	return sentinal;
}
} /* namespace py */
