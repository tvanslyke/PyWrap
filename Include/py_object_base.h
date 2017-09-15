#ifndef PY_OBJECT_BASE_CPP_H 
#define PY_OBJECT_BASE_CPP_H

#include <Python.h>
#include <structmember.h>
#include <type_traits>

namespace py{
class py_object_base;
struct py_borrowed_reference;
struct py_new_reference;
class py_iter;
class py_sequence;
class py_mapping;
class py_number;



template <class T, class = int>
struct is_py_object: std::false_type
{

};

template <class T>
struct is_py_object<T, decltype((void) T::ob_base, 0)>: std::true_type
{
	static constexpr bool value = 	std::is_same<decltype(T::ob_base), PyObject>::value or
				 	std::is_same<decltype(T::ob_base), PyVarObject>::value;
};


template <class T>
static constexpr const bool is_py_object_v = is_py_object<T>::value;


class py_object_base
{
public:
	inline py_object_base(): self_{nullptr} 
	{
	
	}
	inline py_object_base(PyObject* slf): self_{slf}
	{
		
	}

	virtual ~py_object_base() = default;
	
	inline PyObject* get(){ return self_; }
	virtual inline operator PyObject*()
	{
		return self_;
	}

	template <class T>
	operator T*()
	{
		static_assert(is_py_object_v<std::remove_cv_t<T>>, "Cannot convert PyObject* to non PyObject type.");
		return (T*)self_;
	}
	inline operator bool() const
	{
		return (bool)self_;
	}

	template <class T> inline bool operator< (const T & other) const { return self_ < other; }
	template <class T> inline bool operator<=(const T & other) const { return self_ <= other; }
	template <class T> inline bool operator> (const T & other) const { return self_ > other; }
	template <class T> inline bool operator>=(const T & other) const { return self_ >= other; }
	template <class T> inline bool operator==(const T & other) const { return self_ == other; }
	template <class T> inline bool operator!=(const T & other) const { return self_ != other; }











	inline int Print(FILE* fp, int flags)
	{
		return PyObject_Print(self_, fp, flags);
	}
	inline int HasAttr(PyObject* attr_name)
	{
		return PyObject_HasAttr(self_, attr_name);
	}
	inline int HasAttrString(const char* attr_name)
	{
		return PyObject_HasAttrString(self_, attr_name);
	}
	
	py_new_reference GetAttr(PyObject* attr_name);
	py_new_reference GetAttrString(const char* attr_name);
	py_borrowed_reference GenericGetAttr(PyObject* attr_name);
	
	inline int SetAttr(PyObject* attr_name, PyObject* v)
	{
		return PyObject_SetAttr(self_, attr_name, v);
	}
	inline int SetAttr(const char* attr_name, PyObject* v)
	{
		return PyObject_SetAttrString(self_, attr_name, v);
	}
	inline int GenericSetAttr(PyObject* attr_name, PyObject* v)
	{
		return PyObject_GenericSetAttr(self_, attr_name, v);
	}
	
	inline int DelAttr(PyObject* attr_name)
	{
		return PyObject_DelAttr(self_, attr_name);
	}
	inline int DelAttr(const char* attr_name)
	{
		return PyObject_DelAttrString(self_, attr_name);
	}

	py_borrowed_reference GenericGetDict(void* context);
	inline int GenericSetDict(PyObject* value, void* context)
	{
		return PyObject_GenericSetDict(self_, value,  context);
	}

	py_new_reference RichCompare(PyObject* other, int op);
	inline int RichCompareBool(PyObject* other, int op)
	{
		return PyObject_RichCompareBool(self_, other, op);
	}

	py_new_reference Repr();
	py_new_reference ASCII();
	py_new_reference Str();
	py_new_reference Bytes();

	inline int IsSubclass(PyObject* other)
	{
		return PyObject_IsSubclass(self_, other);
	}
	inline int IsInstance(PyObject* other)
	{
		return PyObject_IsInstance(self_, other);
	}

	inline int Callable_Check()
	{
		return PyCallable_Check(self_);
	}

	py_new_reference CallObject(PyObject* args);
	py_new_reference Call(PyObject* args);
	py_new_reference Call(PyObject* args, PyObject* kw);
	template <class ... T>	
	py_new_reference CallFunction(const char* format, T && ... args);

	template <class ... T>	
	py_new_reference CallMethod(const char* method, const char* format, T && ... args);

	template <class ... T>	
	py_new_reference CallFunctionObjArgs(T && ... args);

	template <class ... T>	
	py_new_reference CallMethodObjArgs(PyObject* method, T && ... args);

	inline Py_hash_t Hash()
	{
		return PyObject_Hash(self_);
	}
	// for completeness
	inline Py_hash_t HashNotImplemented()
	{
		return PyObject_HashNotImplemented(self_);
	}

	inline int IsTrue()
	{
		return PyObject_IsTrue(self_);			
	}
	inline int Not()
	{
		return PyObject_Not(self_);	
	}
	
	py_new_reference Type();
	inline int TypeCheck(PyTypeObject* tp)
	{
		return PyObject_TypeCheck(self_, tp);
	}

	inline Py_ssize_t Size()
	{
		return PyObject_Size(self_);
	}
	inline Py_ssize_t Length()
	{
		return PyObject_Length(self_);
	}
	inline Py_ssize_t LengthHint(Py_ssize_t default_len)
	{
		return PyObject_LengthHint(self_, default_len);
	}
	py_new_reference GetItem(PyObject* key);
	inline int SetItem(PyObject* key, PyObject* value)
	{
		return PyObject_SetItem(self_, key, value);
	}
	inline int DelItem(PyObject* key)
	{
		return PyObject_DelItem(self_, key);
	}
	inline int SequenceCheck()
	{
		return PySequence_Check(self_);
	}
	inline int MappingCheck()
	{
		return PyMapping_Check(self_);
	}
	inline int NumberCheck()
	{
		return PyNumber_Check(self_);
	}
	inline int IterCheck()
	{
		return PyIter_Check(self_);
	}
	py_sequence AsSequence();
	py_mapping AsMapping();
	py_number AsNumber();
	py_iter AsIter();
	py_new_reference Dir();
	py_new_reference GetIter();
	inline void incref()
	{
		Py_INCREF(self_);
	}
	inline void decref()
	{
		Py_DECREF(self_);
	}
	inline void xincref()
	{
		Py_XINCREF(self_);
	}
	inline void xdecref()
	{
		Py_XDECREF(self_);
	}
	inline Py_ssize_t refcount() const
	{
		return Py_REFCNT(self_);
	}
	inline PyTypeObject* type() const
	{
		return Py_TYPE(self_);
	}
	inline PyObject* operator->()
	{
		return self_;
	}
	inline PyObject*& self()
	{
		return self_;
	}
	inline PyObject* const & self() const
	{
		return self_;
	}
	
private:
	PyObject* self_;
};





struct py_borrowed_reference: public py_object_base
{
	py_borrowed_reference(py_object_base&&) = delete;
	py_borrowed_reference(const py_object_base& slf): py_object_base(slf)
	{
			
	}
	using py_object_base::py_object_base;
};

struct py_new_reference: public py_object_base
{
	using py_object_base::py_object_base;
	virtual inline ~py_new_reference()
	{
		xdecref();
	}
	py_new_reference(py_new_reference&& obj):
		py_object_base(obj.release())
	{
		
	}
	py_new_reference(const py_new_reference&) 		= delete;
	py_new_reference& operator=(const py_new_reference&) 	= delete;
	py_new_reference& operator=(py_new_reference&&) 	= delete;
	
	inline operator PyObject*() 	{ return release(); };
	inline PyObject* release()
	{
		PyObject* tmp = self();
		self() = nullptr;
		return tmp;
	}
};





template <class ... T>	
py_new_reference py_object_base::CallFunction(const char* format, T && ... args)
{
	return PyObject_CallFunction(self_, format, static_cast<PyObject*>(std::forward<T>(args))...);
}

template <class ... T>	
py_new_reference py_object_base::CallMethod(const char* method, const char* format, T && ... args)
{
	return PyObject_CallMethod(self_, method, format, static_cast<PyObject*>(std::forward<T>(args))...);
}

template <class ... T>	
py_new_reference py_object_base::CallFunctionObjArgs(T && ... args)
{
	return PyObject_CallFunctionObjArgs(self_, static_cast<PyObject*>(std::forward<T>(args))..., NULL);
}

template <class ... T>	
py_new_reference py_object_base::CallMethodObjArgs(PyObject* method, T && ... args)
{
	return PyObject_CallMethodObjArgs(self_, method, (PyObject*)(std::forward<T>(args))..., NULL);
}


template <> inline bool 
py_object_base::operator<  <py_object_base>(const py_object_base & other) const { return self() <  other.self(); }
template <> inline bool 
py_object_base::operator<= <py_object_base>(const py_object_base & other) const { return self() <= other.self();  }
template <> inline bool 
py_object_base::operator>  <py_object_base>(const py_object_base & other) const { return self() >  other.self(); }
template <> inline bool 
py_object_base::operator>= <py_object_base>(const py_object_base & other) const { return self() >= other.self(); }
template <> inline bool 
py_object_base::operator== <py_object_base>(const py_object_base & other) const { return self() == other.self(); }
template <> inline bool 
py_object_base::operator!= <py_object_base>(const py_object_base & other) const { return self() != other.self(); }

template <class T, class = std::enable_if_t<not std::is_base_of_v<py_object_base, T>>> 
bool operator< (const T & other, const py_object_base& obj) { return other >= obj.self(); }
template <class T, class = std::enable_if_t<not std::is_base_of_v<py_object_base, T>>> 
bool operator<=(const T & other, const py_object_base& obj) { return other >= obj.self(); }
template <class T, class = std::enable_if_t<not std::is_base_of_v<py_object_base, T>>> 
bool operator> (const T & other, const py_object_base& obj) { return other >= obj.self(); }
template <class T, class = std::enable_if_t<not std::is_base_of_v<py_object_base, T>>> 
bool operator>=(const T & other, const py_object_base& obj) { return other >= obj.self(); }
template <class T, class = std::enable_if_t<not std::is_base_of_v<py_object_base, T>>>
bool operator==(const T & other, const py_object_base& obj) { return other == obj.self(); }
template <class T, class = std::enable_if_t<not std::is_base_of_v<py_object_base, T>>> 
bool operator!=(const T & other, const py_object_base& obj) { return other != obj.self(); }

} /* namespace py */




#endif /* PY_OBJECT_BASE_CPP_H */



