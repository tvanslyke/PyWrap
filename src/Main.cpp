#include "pycpp.h"

int main()
{
	Py_Initialize();
	py::py_object list = py::py_new_reference(PyList_New(3));
	PyList_SET_ITEM(list, 0, PyLong_FromLong(0));
	PyList_SET_ITEM(list, 1, PyLong_FromLong(2));
	PyList_SET_ITEM(list, 2, PyLong_FromLong(4));
	list.Print(stdout, Py_PRINT_RAW);
	printf("\n");
	py::py_object itm = list.CallMethod("pop", "");
	itm.Print(stdout, Py_PRINT_RAW);

	printf("\n");
	return 0;
}
