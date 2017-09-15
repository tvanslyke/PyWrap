#include "pycpp.h"
#include <iostream>
using namespace py;

int main()
{
	const char* words[6] = {"Hi", "my", "name", "is", "Slim", "Shady"};
	Py_Initialize();
	
	Py_ssize_t idx = 0;
	py_object tup;
	PY_WRAP_TRY
		tup = throw_if_bad_new(PyTuple_New(6));
		for(auto& item: py_fast_sequence(tup))
		{
			item = throw_if_bad_new(PyUnicode_FromString(words[idx++]));
		}
		throw_if_error(tup.Print(stdout, Py_PRINT_RAW));
		std::cout << '\n';

		for(py_object item:py_sequence(tup))
		{
			std::cout << (const char*)(PyUnicode_DATA((PyObject*)steal(item.Repr()))) << '\n';
		}
		py_object join_str = throw_if_bad_new(PyUnicode_FromString(" "));
		py_object method_name = throw_if_bad_new(PyUnicode_FromString("join"));
		py_object joined = throw_if_bad_new(join_str.CallMethodObjArgs(method_name, tup, (PyObject*)nullptr));
		joined = throw_if_bad_new(py_sequence(joined).Concat(throw_if_bad_new(PyUnicode_FromString("!!!\n"))));
		throw_if_error(joined.Print(stdout, Py_PRINT_RAW));

		throw py_exception(PyExc_RuntimeError, "This is a fake error message, nothing actually went wrong.");
	
	PY_WRAP_CATCH
		const py_exception & current_exception = PY_WRAP_CURRENT_EXCEPTION;
		tup = nullptr; // implicit Py_XDECREF(self); before assignment
		std::cerr << "Unexpected error occurred.  Propogating to caller." << std::endl;
		std::cerr << current_exception.what() << std::endl;
		PY_WRAP_PROPAGATE_ERROR
	PY_WRAP_TRY_CATCH_END
	std::cout << "DONE!" << std::endl;
			
	return 0;
}
