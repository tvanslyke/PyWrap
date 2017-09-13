#ifndef PY_OBJECT_CPP_H
#define PY_OBJECT_CPP_H

#include <python3.5/Python.h>
#include <python3.5/structmember.h>
#include <type_traits>

namespace py{

struct py_borrowed_reference
{
	inline py_borrowed_reference(): self_{nullptr} {}
	inline py_borrowed_reference(PyObject* slf): self_{slf} {}
	inline operator PyObject*() 	{ return self_; };
	PyObject* self_;
};

struct py_new_reference
{
	inline py_new_reference(): self_{nullptr} {}
	inline py_new_reference(PyObject* slf): self_{slf} {}
	inline operator PyObject*() 	{ return release(); };
	inline py_new_reference(const py_new_reference&) 		= delete;
	inline py_new_reference(py_new_reference&&) 			= delete;
	inline py_new_reference& operator=(const py_new_reference&) 	= delete;
	inline py_new_reference& operator=(py_new_reference&&) 	= delete;
	inline PyObject* release()
	{
		PyObject* tmp = self_;
		self_ = nullptr;
		return tmp;
	}
	inline ~py_new_reference()
	{
		Py_XDECREF(self_);
	}
	PyObject* self_;
};


/*template <typename T> 
struct is_py_object 
{ 
	struct Fallback { int ob_type; }; 
	struct Derived : T, Fallback { };
	template<typename C, C> struct ChT; 
        template<typename C> static char (&f(ChT<int Fallback::*, &C::ob_type>*))[1]; 
	template<typename C> static char (&f(...))[2]; 
        static bool const value = sizeof(f<Derived>(0)) == 2;
}; */


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


class py_object
{
public:
	inline py_object(): self_{nullptr} 
	{
	
	}
	inline py_object(PyObject* slf): self_{slf} 
	{
		xincref();
	}
	inline py_object(py_new_reference slf): self_{slf.release()} 	
	{
		
	}
	py_object(py_borrowed_reference slf): self_{(PyObject*)slf} 	
	{
		xincref();
	}

	inline py_object(PyObject* slf, bool new_reference): self_{slf} 
	{
		if(not new_reference)
			xincref();
	}
	py_object(const py_object& other)
	{
		self_ = other.self_;
		xincref();
	}
	py_object(py_object&& other)
	{
		self_ = other.self_;
		other.self_ = nullptr;
	}
	virtual ~py_object(){ Py_XDECREF(self_); }
	py_object& operator=(const py_object& other)
	{
		xdecref();
		self_ = other.self_;
		xincref();
	}
	py_object& operator=(py_object&& other)
	{
		xdecref();
		self_ = other.self_;
		other.self_ = nullptr;
	}
	PyObject* get(){ return self_; }
	inline operator PyObject*()
	{
		return self_;
	}
	template <class T>
	operator T*()
	{
		static_assert(is_py_object_v<std::remove_cv_t<T>>, "Cannot convert PyObject* to non PyObject.");
		return (T*)self_;
	}
	inline operator bool() const
	{
		return (bool)self_;
	}



	
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
	
	inline py_new_reference GetAttr(PyObject* attr_name)
	{
		return PyObject_GetAttr(self_, attr_name);
	}
	inline py_new_reference GetAttrString(const char* attr_name)
	{
		return PyObject_GetAttrString(self_, attr_name);
	}
	inline py_borrowed_reference GenericGetAttr(PyObject* attr_name) 
	{
		return PyObject_GenericGetAttr(self_, attr_name);	
	}
	
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

	inline py_borrowed_reference GenericGetDict(void* context)
	{
		return PyObject_GenericGetDict(self_, context);
	}
	inline int GenericSetDict(PyObject* value, void* context)
	{
		return PyObject_GenericSetDict(self_, value,  context);
	}

	inline py_new_reference RichCompare(PyObject* other, int op)
	{
		return PyObject_RichCompare(self_, other, op);
	}
	inline int RichCompareBool(PyObject* other, int op)
	{
		return PyObject_RichCompareBool(self_, other, op);
	}

	inline py_new_reference Repr()
	{
		return PyObject_Repr(self_);
	}
	inline py_borrowed_reference ASCII()
	{
		return PyObject_ASCII(self_);
	}
	inline py_new_reference Str()
	{
		return PyObject_Str(self_);
	}
	inline py_borrowed_reference Bytes()
	{
		return PyObject_Bytes(self_);
	}

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

	inline py_new_reference CallObject(PyObject* args)
	{
		return PyObject_CallObject(self_, args);
	}
	inline py_new_reference Call(PyObject* args)
	{
		return PyObject_CallObject(self_, args);
	}
	inline py_new_reference Call(PyObject* args, PyObject* kw)
	{
		return PyObject_Call(self_, args, kw);
	}
	template <class ... T>	
	inline py_new_reference CallFunction(const char* format, T && ... args)
	{
		return PyObject_CallFunction(self_, format, std::forward<T>(args)...);
	}

	template <class ... T>	
	inline py_new_reference CallMethod(const char* method, const char* format, T && ... args)
	{
		return PyObject_CallMethod(self_, method, format, std::forward<T>(args)...);
	}

	template <class ... T>	
	inline py_new_reference CallFunctionObjArgs(T && ... args)
	{
		return PyObject_CallFunctionObjArgs(self_, std::forward<T>(args)..., NULL);
	}

	template <class ... T>	
	inline py_new_reference CallMethodObjArgs(PyObject* method, T && ... args)
	{
		return PyObject_CallMethodObjArgs(self_, method, std::forward<T>(args)..., NULL);
	}

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
	
	inline py_new_reference Type()
	{
		return PyObject_Type(self_);
	}
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
	inline py_new_reference GetItem(PyObject* key)
	{
		return PyObject_GetItem(self_, key);
	}	
	inline int SetItem(PyObject* key, PyObject* value)
	{
		return PyObject_SetItem(self_, key, value);
	}
	inline int DelItem(PyObject* key)
	{
		return PyObject_DelItem(self_, key);
	}
	inline py_new_reference Dir()
	{
		return PyObject_Dir(self_);
	}
	inline py_new_reference GetIter() 
	{
		return PyObject_GetIter(self_);
	}	
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
	inline PyObject* operator->()
	{
		return self_;
	}
	inline PyObject*& self()
	{
		return self_;
	}
	
private:
	PyObject* self_;
};


} /* namespace py */



#endif /* PY_OBJECT_CPP_H */
