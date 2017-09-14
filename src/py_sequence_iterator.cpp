#include "py_sequence_iterator.h"
#include "py_wrap_exception.h"


namespace py{

	py_sequence_reference::py_sequence_reference(PyObject* seq, Py_ssize_t idx);
	py_sequence_reference& py_sequence_reference::operator=(PyObject* obj)
	{

	}

	py_sequence_reference::operator py_object()
	{
		return get_value();
	}
	py_sequence_reference::operator py_new_reference()
	{
		return get_value();
	}
	
	int py_sequence_reference::set_value(PyObject* value)
	{
		return PySequence_SetItem(seq_, idx_, value);
	}
	py_sequence_reference& py_sequence_reference::operator=(PyObject* obj)
	{
		throw_if_error(set_value(obj));
		return *this;
	}

	py_new_reference get_value()
	{
		return steal(PySequence_GetItem(seq_, idx_);
	}

} /* namespace py */
