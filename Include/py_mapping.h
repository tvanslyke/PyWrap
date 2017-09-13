#ifndef PY_MAPPING_CPP_H
#define PY_MAPPING_CPP_H

#include "py_object.h"



namespace py{


class py_mapping: public py_object
{
public:
	using py_object::py_object;
	
	inline Py_ssize_t Size()	{ return PyMapping_Size(self()); }
	inline Py_ssize_t Length()	{ return PyMapping_Length(self()); }

	inline int DelItemString(const char *key)
	{
		return PyMapping_DelItemString(self(), key);
	}
	inline int DelItem(PyObject* key)
	{
		return PyMapping_DelItem(self(), key);
	}
	
	inline int HasKeyString(const char* key)
	{
		return PyMapping_HasKeyString(self(), key);
	}
	inline int HasKey(PyObject* key)
	{
		return PyMapping_HasKey(self(), key);	
	}

	inline py_new_reference Values()
	{
		return PyMapping_Values(self());
	}
	inline py_new_reference Keys()
	{
		return PyMapping_Keys(self());
	}
	inline py_new_reference Items()
	{
		return PyMapping_Items(self());
	}
	inline py_new_reference GetItemString(const char* key) 
	{
		return PyMapping_GetItemString(self(), key);
	}
	inline int SetItemString(const char* key, PyObject* value)
	{
		return PyMapping_SetItemString(self(), key, value);
	}
};


} /* namespace py */

#endif /* PY_MAPPING_CPP_H */
