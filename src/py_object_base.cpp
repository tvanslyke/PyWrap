#include "py_object_base.h"

namespace py{



py_new_reference py_object_base::GetAttr(PyObject* attr_name)
{
	return PyObject_GetAttr(self_, attr_name);
}
py_new_reference py_object_base::GetAttrString(const char* attr_name)
{
	return PyObject_GetAttrString(self_, attr_name);
}
py_borrowed_reference py_object_base::GenericGetAttr(PyObject* attr_name) 
{
	return PyObject_GenericGetAttr(self_, attr_name);	
}

py_borrowed_reference py_object_base::GenericGetDict(void* context)
{
	return PyObject_GenericGetDict(self_, context);
}
py_new_reference py_object_base::RichCompare(PyObject* other, int op)
{
	return PyObject_RichCompare(self_, other, op);
}
py_new_reference py_object_base::Repr()
{
	return PyObject_Repr(self_);
}
py_new_reference py_object_base::ASCII()
{
	return PyObject_ASCII(self_);
}
py_new_reference py_object_base::Str()
{
	return PyObject_Str(self_);
}
py_new_reference py_object_base::Bytes()
{
	return PyObject_Bytes(self_);
}
py_new_reference py_object_base::CallObject(PyObject* args)
{
	return PyObject_CallObject(self_, args);
}
py_new_reference py_object_base::Call(PyObject* args)
{
	return PyObject_CallObject(self_, args);
}
py_new_reference py_object_base::Call(PyObject* args, PyObject* kw)
{
	return PyObject_Call(self_, args, kw);
}

py_new_reference py_object_base::Type()
{
	return PyObject_Type(self_);
}
py_new_reference py_object_base::GetItem(PyObject* key)
{
	return PyObject_GetItem(self_, key);
}	
py_new_reference py_object_base::Dir()
{
	return PyObject_Dir(self_);
}
py_new_reference py_object_base::GetIter() 
{
	return PyObject_GetIter(self_);
}	
	
py_sequence AsSequence();
py_mapping AsMapping();
py_number AsNumber();
py_iter AsIter();




} /* namespace py */
