#ifndef PY_WRAP_EXCEPTION_CPP_H
#define PY_WRAP_EXCEPTION_CPP_H

#include <Python.h>
#include <stdexcept>
namespace py{

class py_exception: public std::exception
{
public:

	inline py_exception():
		exc_{PyErr_Occurred()}, errcode_{-1} 
	{
		// debug assert
		assert(PyErr_Occurred() && "A py_exception must either be thrown with a python exception object + message or with a python exception already set.");
	}
	
	virtual ~py_exception() = default;

	inline py_exception(int errcode):
		py_exception()

	{
		errcode_ = errcode;
	}
	inline py_exception(py_object exc, const char* msg): 
		exc_{std::move(exc)}, errcode_{-1}
	{
		PyErr_SetString(exc, msg);
	}	
	inline py_exception(py_object exc, const char* msg, int errcode): 
		py_exception(std::move(exc), msg)
	{
		errcode_ = errcode;
	}
	
	inline py_exception(const std::exception& exc): 
		py_exception(PyExc_SystemError, exc.what())
	{
		errcode_ = -1;
	}
	
	inline py_exception(const std::bad_alloc& exc): 
		py_exception(PyExc_MemoryError, exc.what())
	{
		errcode_ = -1;
	}
	inline py_exception(const std::ios_base::failure& exc): 
		py_exception(PyExc_IOError, exc.what())
	{
		errcode_ = -1;
	}

	inline virtual const char* what() const
	{
		return error_message();
	}
	
	inline int propogate_error_as_code(int subval = 0) const
	{
		if(subval)
			return subval;
		else
			return errcode_ * (errcode_ != 0) + -1 * (errcode_ == 0);
	}
	inline PyObject* propogate_error_as_null_object() const
	{
		return nullptr;
	}
	inline PyObject* propogate_error_as_object(PyObject* subval = nullptr) const
	{
		return subval;
	}

	inline operator PyObject*() const
	{
		return propogate_error_as_null_object();
	}
	inline operator int() const
	{
		return propogate_error_as_code();
	}
	
	inline const char* error_message() const
	{
		PyObject *ptype, *pvalue, *ptraceback;
		PyErr_Fetch(&ptype, &pvalue, &ptraceback);
		const char* msg = PyString_AsString(pvalue);
		PyErr_Restore(ptype, pvalue, ptraceback);
		return msg;
	}

private:
	py_object exc_;
	int errcode_;
};


PyObject* throw_if_error(PyObject* value)
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


#define PY_WRAP_TRY	try{ 

#define PY_WRAP_CATCH 								\
	} catch(const py::py_exception & PY__WRAP__CAUGHT__EXCEPTION__) { 	
	

#define PY_WRAP_PROPAGATE_ERROR 			\
		return PY__WRAP__CAUGHT__EXCEPTION__;

#define PY_WRAP_CURRENT_EXCEPTION PY__WRAP__CAUGHT__EXCEPTION__;


#define PY_WRAP_TRY_CATCH_END 	\
		PyErr_Clear();	\
	}

}

#endif /* PY_WRAP_EXCEPTION_CPP_H */
