#ifndef PY_UTILS_CPP_H
#define PY_UTILS_CPP_H

#include "py_object_base.h"
#include "py_sequence.h"
#include "py_mapping.h"
#include "py_number.h"
#include "py_iter.h"
#include "py_iterator.h"
namespace py{



inline py_new_reference steal(py_object_base&& obj)
{
	return py_new_reference(std::move(obj));
}
inline py_new_reference steal(py_object_base& obj)
{
	return py_new_reference(std::move(obj));
}

inline py_borrowed_reference borrow(const py_object_base& obj)
{
	return py_borrowed_reference(obj);
}
inline py_borrowed_reference borrow(py_object_base&& obj) = delete;

using py_abstract_cast_tag = enum py_abstract_cast_tag_
{
	ITER,
	SEQUENCE,
	MAPPING,
	NUMBER
};
namespace { struct abstract_cast_error_bad_tag{}; }
template <py_abstract_cast_tag Tag>
using py_abstract_cast_tag_t = 	std::conditional_t<Tag == ITER, py_iter, 
      			 	std::conditional_t<Tag == SEQUENCE, py_sequence,
				std::conditional_t<Tag == MAPPING, py_mapping, 
				std::conditional_t<Tag == NUMBER, py_number,
				abstract_cast_error_bad_tag>>>>;
				

template <class T>
using py_castable_t = std::enable_if_t<std::is_base_of_v<py_object_base, std::decay_t<T>>>;
template <class T>
decltype(auto) abstract_cast(const py_object_base& obj)
{
	return dynamic_cast<const std::decay_t<T>&>(obj);
}
template <class T>
decltype(auto) abstract_cast(py_object_base& obj)
{
	return dynamic_cast<std::decay_t<T>&>(obj);
}
template <class T>
decltype(auto) abstract_cast(py_object_base&& obj)
{
	return dynamic_cast<std::decay_t<T>>(std::move(obj));
}

template <py_abstract_cast_tag Tag, class T>
decltype(auto) abstract_cast(T && obj)
{
	return abstract_cast<py_abstract_cast_tag_t<Tag>>(std::forward<T>(obj));
}
template <class T>
decltype(auto) sequence_cast(py_castable_t<T>&& obj)
{
	return abstract_cast<SEQUENCE>(std::forward<py_castable_t<T>>(obj));
}
template <class T>
decltype(auto) mapping_cast(py_castable_t<T>&& obj)
{
	return abstract_cast<MAPPING>(std::forward<py_castable_t<T>>(obj));
}
template <class T>
decltype(auto) iter_cast(py_castable_t<T>&& obj)
{
	return abstract_cast<ITER>(std::forward<py_castable_t<T>>(obj));
}
template <class T>
decltype(auto) number_cast(py_castable_t<T>&& obj)
{
	return abstract_cast<NUMBER>(std::forward<py_castable_t<T>>(obj));
}
} /* namespace py */

#endif 
