#include "py_object.h"
#include "py_utils.h"
#include "py_wrap_exception.h"
#include <ios>
#include <stdexcept>
namespace py{


py_exception::py_exception():
	exc_{PyErr_Occurred()}, errcode_{-1} 
{
	// debug assert
	assert(PyErr_Occurred() && "A py_exception must either be thrown with a python exception object + message or with a python exception already set.");
}


py_exception::py_exception(int errcode):
	py_exception()

{
	errcode_ = errcode;
}
py_exception::py_exception(py_object exc, const char* msg): 
	exc_{std::move(exc)}, errcode_{-1}
{
	PyErr_SetString(exc, msg);
}	
py_exception::py_exception(py_object exc, const char* msg, int errcode): 
	py_exception(std::move(exc), msg)
{
	errcode_ = errcode;
}

py_exception::py_exception(const std::exception& exc): 
	py_exception(PyExc_SystemError, exc.what())
{
	errcode_ = -1;
}

py_exception::py_exception(const std::bad_alloc& exc): 
	py_exception(PyExc_MemoryError, exc.what())
{
	errcode_ = -1;
}
py_exception::py_exception(const std::ios_base::failure& exc): 
	py_exception(PyExc_IOError, exc.what())
{
	errcode_ = -1;
}

const char* py_exception::what() const noexcept
{
	return error_message();
}

int py_exception::propogate_error_as_code(int subval) const
{
	if(subval)
		return subval;
	else
		return errcode_ * (errcode_ != 0) + -1 * (errcode_ == 0);
}
PyObject* py_exception::propogate_error_as_null_object() const
{
	return nullptr;
}
PyObject* py_exception::propogate_error_as_object(PyObject* subval) const
{
	return subval;
}

py_exception::operator PyObject*() const
{
	return propogate_error_as_null_object();
}
py_exception::operator int() const
{
	return propogate_error_as_code();
}

const char* py_exception::error_message() const
{
	PyObject *ptype, *pvalue, *ptraceback;
	PyErr_Fetch(&ptype, &pvalue, &ptraceback);
	const char* msg = (const char*)PyUnicode_DATA((PyObject*)steal(PyObject_Str(pvalue)));
	PyErr_Restore(ptype, pvalue, ptraceback);
	return msg;
}

py_borrowed_reference py_exception::exception_type() const
{
	return exc_;
}



py_new_reference throw_if_bad_new(PyObject* value)
{
	return throw_if_error(steal(value));
}
py_borrowed_reference throw_if_bad_borrow(PyObject* value)
{
	return throw_if_error(borrow(value));
}

py_new_reference throw_if_error(py_new_reference value)
{
	return steal(throw_if_error(value.release()));
}
py_borrowed_reference throw_if_error(py_borrowed_reference value)
{
	return throw_if_error(value);
}
py_object throw_if_error(const py_object & value)
{
	return throw_if_error(value.self());
}

py_object_base throw_if_error(PyObject* value)
{
	// exceptions are exceptional.
	bool except = not value; 
#ifdef __GNUC__
	if(__builtin_expect(long(except), 0l)){
#else
	if(except){
#endif
		throw py_exception();
	}
	return value;
}
int throw_if_error(int value)
{
	// exceptions are exceptional.
	bool except = value != 0; 
#ifdef __GNUC__
	if(__builtin_expect(long(except), 0l))
#else 
	if(except)
#endif
	{
		throw py_exception();
	}
	return value;
}


} /* namespace py */
