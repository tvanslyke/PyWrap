#ifndef PY_UTILS_CPP_H
#define PY_UTILS_CPP_H

#include "py_object_base.h"
#include "py_sequence.h"
#include "py_mapping.h"
#include "py_number.h"
#include "py_iter.h"
#include "py_iterator.h"
#include "py_sequence_iterator.h"
namespace py{



template <class T>
inline py_new_reference steal(T&& obj)
{
	return py_new_reference(std::forward<T>(obj));
}

template <class T>
inline py_borrowed_reference borrow(T&& obj)
{
	return py_borrowed_reference(std::forward<T>(obj));
}


inline auto begin(py_sequence iterable) 	{ return py_sequence_iterator(iterable, 0); }
inline auto begin(py_object iterable) 		{ return py_iterator(iterable); }
inline auto begin(py_fast_sequence seq) 	{ return seq.begin(); }


inline auto end(py_sequence iterable) 		{ return py_sequence_iterator(iterable, iterable.Size()); }
inline auto end(py_object iterable) 		{ return py_iterator::end_sentinal(); }
inline auto end(py_fast_sequence seq) 		{ return seq.end(); }


} /* namespace py */

#endif 
