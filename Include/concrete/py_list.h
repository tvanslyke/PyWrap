#ifndef PY_LIST_CPP_H
#define PY_LIST_CPP_H

#include "pycpp.h"


namespace py{



class py_list: public py_object
{
public:
	inline py_list():
		py_object(PyList_New(0))
	{
		
	}
};


} /* namespace py */




#endif /* PY_LIST_CPP_H */
