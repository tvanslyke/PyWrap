#ifndef PY_ITER_CPP_H
#define PY_ITER_CPP_H

#include "py_object.h"

namespace py{
class py_iter: public virtual py_object_base
{
public:
	using py_object_base::py_object_base;
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
