#ifndef PY_ITER_CPP_H
#define PY_ITER_CPP_H

#include "py_object.h"
namespace py{
class py_iter: public py_object
{
public:
	using py_object::py_object;
	inline int Check()
	{
		return PyIter_Check(self());
	}
	inline py_new_reference Next()
	{
		return PyIter_Next(self());
	}	
};

} /* namespace py */
#endif /* PY_ITER_CPP_H */
