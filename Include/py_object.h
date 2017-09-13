#ifndef PY_OBJECT_CPP_H
#define PY_OBJECT_CPP_H

#include "py_object_base.h"
namespace py{


class py_object: public py_object_base
{
public:
	inline py_object(): py_object_base()
	{
	
	}
	inline py_object(PyObject* slf): py_object_base(slf)
	{
		xincref();
	}
	inline py_object(py_new_reference slf): py_object_base(slf.release())
	{

	}
	inline py_object(py_borrowed_reference slf): py_object_base((PyObject*)slf)
	{
		xincref();	
	}

	inline py_object(PyObject* slf, bool new_reference): py_object_base(slf) 
	{
		if(not new_reference)
			xincref();
	}

	inline py_object(const py_object_base& other): py_object_base(other)
	{
		xincref();
	}
	inline py_object(py_object_base&& other): py_object_base(std::move(other))
	{
		// redundant, but may refactor py_object_base in future to not do this for you...
		other.self() = nullptr;
	}
	inline py_object(const py_object& other)
	{
		self() = other.self();
		xincref();
	}
	inline py_object(py_object&& other)
	{
		self() = other.self();
		other.self() = nullptr;
	}
	inline virtual ~py_object()
	{ 
		xdecref(); 
	}
	inline py_object& operator=(const py_object& other)
	{
		py_object_base tmp(self());
		self() = other.self();
		xincref();
		tmp.xdecref();
		return *this;
	}
	inline py_object& operator=(py_object&& other)
	{
		py_object_base tmp(self());
		self() = other.self();
		other.self() = nullptr;
		tmp.xdecref();
		return *this;
	}
	inline py_object& operator=(const py_object_base& other)
	{
		py_object_base tmp(self());
		self() = other.self();
		xincref();
		tmp.xdecref();
		return *this;
	}
	inline py_object& operator=(py_object_base&& other)
	{
		py_object_base tmp(self());
		self() = other.self();
		other.self() = nullptr;
		tmp.xdecref();
		return *this;
	}
};




} /* namespace py */




#endif /* PY_OBJECT_CPP_H */
