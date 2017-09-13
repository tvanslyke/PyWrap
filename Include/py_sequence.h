#ifndef PY_SEQUENCE_CPP_H
#define PY_SEQUENCE_CPP_H

#include "py_object.h"

namespace py{

class py_sequence: public py_object_base
{
public:
	using py_object_base::py_object_base;
	inline py_new_reference Concat(PyObject* other) 		{ return PySequence_Concat(self(), other); }
	inline py_new_reference Repeat(Py_ssize_t reps) 		{ return PySequence_Repeat(self(), reps); }
	inline py_new_reference InPlaceConcat(PyObject* other) 		{ return PySequence_InPlaceConcat(self(), other); }
	inline py_new_reference InPlaceRepeat(Py_ssize_t reps)		{ return PySequence_InPlaceRepeat(self(), reps); }

	inline py_new_reference GetItem(Py_ssize_t idx)			{ return PySequence_GetItem(self(), idx); }
	inline py_new_reference GetSlice(Py_ssize_t i1, Py_ssize_t i2) 	{ return PySequence_GetSlice(self(), i1, i2); }
	
	inline int SetItem(Py_ssize_t idx, PyObject* value) 		 
	{ 
		return PySequence_SetItem(self(), idx, value); 
	}
	inline int SetSlice(Py_ssize_t i1, Py_ssize_t i2, PyObject* value) 
	{ 
		return PySequence_SetSlice(self(), i1, i2, value); 
	}

	inline int DelItem(Py_ssize_t idx) 		 
	{ 
		return PySequence_DelItem(self(), idx); 
	}
	inline int DelSlice(Py_ssize_t i1, Py_ssize_t i2) 		 
	{ 
		return PySequence_DelSlice(self(), i1, i2); 
	}
	
	inline Py_ssize_t Count(PyObject* value) 	{ return PySequence_Count(self(), value); }
	inline Py_ssize_t Contains(PyObject* value) 	{ return PySequence_Contains(self(), value); }
	inline Py_ssize_t Index(PyObject* value) 	{ return PySequence_Index(self(), value); }

	inline py_new_reference List() 	{ return PySequence_List(self()); }
	inline py_new_reference Tuple()	{ return PySequence_Tuple(self()); }
	inline py_new_reference Fast(const char* msg) 	{ return PySequence_Fast(self(), msg); }


	inline py_borrowed_reference Fast_GET_ITEM(Py_ssize_t idx) 	
	{ 
		return PySequence_Fast_GET_ITEM(self(), idx);
	}
	inline PyObject** Fast_ITEMS()
	{ 
		return PySequence_Fast_ITEMS(self()); 
	}
	inline py_new_reference ITEM(Py_ssize_t idx)
	{ 
		return PySequence_ITEM(self(), idx); 
	}
	inline Py_ssize_t Fast_GET_SIZE()
	{
		return PySequence_Fast_GET_SIZE(self());
	}	
	
};



} /* namespace py */

#endif /* PY_SEQUENCE_CPP_H */
