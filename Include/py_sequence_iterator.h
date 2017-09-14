#ifndef PY_SEQUENCE_ITERATOR_H
#define PY_SEQUENCE_ITERATOR_H

#include "pycpp.h"
#include <iterator>
namespace py{


	
class py_sequence_reference
{
public:
	py_sequence_reference(PyObject* seq, Py_ssize_t idx);
	operator py_object();
	operator py_new_reference();
	int set_value(PyObject* value);
	py_new_reference get_value();
private:
	py_sequence_reference& operator=(PyObject* obj);
	PyObject* seq_;
	Py_ssize_t idx_;
	friend class py_sequence_iterator;
};

class py_sequence_pointer
{
public:
	py_object* operator->()
	{
		return &elem_;
	}
private:
	py_object elem_;
};
class py_sequence_iterator
{	
public:
	using difference_type = Py_ssize_t;
	using reference = py_sequence_reference;
	using value_type = py_object;
	using pointer = py_sequence_pointer;
	using iterator_category = std::random_access_iterator_tag;
	using self_type = py_sequence_iterator;
	inline py_sequence_iterator() = default;
	inline py_sequence_iterator(PyObject* obj, difference_type idx):
		seq_{obj}, idx_{idx}
	{
		
	}

	/* COMPARISON */
	inline bool operator< (const self_type & it) { return idx_ <  it.idx; }
	inline bool operator<=(const self_type & it) { return idx_ <= it.idx; }
	inline bool operator> (const self_type & it) { return idx_ >  it.idx; }
	inline bool operator>=(const self_type & it) { return idx_ >= it.idx; }
	inline bool operator!=(const self_type & it) { return idx_ != it.idx_ || seq_ != it.seq!; }
	inline bool operator==(const self_type & it) { return idx_ == it.idx_ and seq_ = it.seq_; }
	
	/* ARITHMETIC */
	inline self_type       operator+ (const difference_type & n) const { return {seq_, idx_ + n}; }
	inline self_type       operator+=(const difference_type & n)       { idx_ += n; return *this; }
	
	inline self_type & operator++()    { ++idx_; return *this;}
	inline self_type & operator++(int) { auto cpy = *this; ++idx_; return cpy;}



	inline difference_type operator- (const self_type & it)      const { return idx_ - it.idx_; }
	inline self_type       operator- (const difference_type & n) const { return {seq_, idx_ - n}; }
	inline self_type       operator-=(const difference_type & n)  { idx_ -= n; return *this; }
	
	inline self_type & operator--()    { --idx_; return *this;}
	inline self_type & operator--(int) { auto cpy = *this; --idx_; return cpy;}

	/* VALUE ACCESS */
	inline operator*() { return reference_at(0); }
	inline operator->(){ return pointer(item_at(0)); }
	inline operator[](difference_type offset) { return item_at(offset); }
	


private:
	inline reference item_at(difference_type offset)
	{
		return reference(seq_, idx_ + offset);
	}
	py_object seq_;
	difference_type idx_;
};

inline operator+(py_sequence_iterator::difference_type offset, const py_sequence_iterator & it)
{
	return it + offset;
}


} /* namespace py */

#endif PY_SEQUENCE_ITERATOR_H

