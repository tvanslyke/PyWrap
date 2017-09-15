#ifndef PY_WRAP_EXCEPTION_CPP_H
#define PY_WRAP_EXCEPTION_CPP_H

#include <stdexcept>
#include <ios>
#include <Python.h>
namespace py{
	class py_object;
	class py_borrowed_reference;
	class py_new_reference;
class py_exception: public std::exception
{
public:

	py_exception();
	py_exception(int errcode);
	py_exception(py_object exc, const char* msg);
	py_exception(py_object exc, const char* msg, int errcode);
	py_exception(const std::exception& exc);
	py_exception(const std::bad_alloc& exc); 
	py_exception(const std::ios_base::failure& exc);
	virtual ~py_exception() = default;
	
	virtual const char* what() const noexcept;
	int propogate_error_as_code(int subval = 0) const;
	PyObject* propogate_error_as_null_object() const;
	PyObject* propogate_error_as_object(PyObject* subval = nullptr) const;
	operator PyObject*() const;
	operator int() const;
	const char* error_message() const;
	py_borrowed_reference exception_type() const;

private:
	py_object exc_;
	int errcode_;
};


int throw_if_error(int value);
py_object_base throw_if_error(PyObject* value);

py_new_reference throw_if_error(py_new_reference value);
py_borrowed_reference throw_if_error(py_borrowed_reference value);
py_object throw_if_error(const py_object & value);

py_new_reference throw_if_bad_new(PyObject* value);
py_borrowed_reference throw_if_bad_borrow(PyObject* value);


#define PY_WRAP_TRY	try{ 

#define PY_WRAP_CATCH 								\
	} catch(const py::py_exception & PY__WRAP__CAUGHT__EXCEPTION__) { 	
	

#define PY_WRAP_PROPAGATE_ERROR 			\
		return PY__WRAP__CAUGHT__EXCEPTION__;

#define PY_WRAP_RETHROW_ERROR 				\
		throw PY__WRAP__CAUGHT__EXCEPTION__;

#define PY_WRAP_CURRENT_EXCEPTION PY__WRAP__CAUGHT__EXCEPTION__;


#define PY_WRAP_TRY_CATCH_END 	\
		PyErr_Clear();	\
	}

}

#endif /* PY_WRAP_EXCEPTION_CPP_H */
