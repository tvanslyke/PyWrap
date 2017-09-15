#ifndef PY_NUMBER_CPP_H
#define PY_NUMBER_CPP_H
#include "py_object.h"

namespace py{


class py_number: public virtual py_object_base
{
public:
	
	using py_object_base::py_object_base;
	inline py_new_reference Add(PyObject* other) 			{ return PyNumber_Add(self(), other); }
	inline py_new_reference Subtract(PyObject* other) 		{ return PyNumber_Subtract(self(), other); }
	inline py_new_reference Multiply(PyObject* other) 		{ return PyNumber_Multiply(self(), other); }
	inline py_new_reference MatrixMultiply(PyObject* other) 	{ return PyNumber_MatrixMultiply(self(), other); }
	
	inline py_new_reference FloorDivide(PyObject* other) 		{ return PyNumber_FloorDivide(self(), other); }
	inline py_new_reference TrueDivide(PyObject* other) 		{ return PyNumber_TrueDivide(self(), other); }
	inline py_new_reference Remainder(PyObject* other) 		{ return PyNumber_Remainder(self(), other); }
	inline py_new_reference Divmod(PyObject* other) 		{ return PyNumber_Divmod(self(), other); }

	inline py_new_reference Power(PyObject* other, PyObject* p) 	{ return PyNumber_Power(self(), other, p); }

	inline py_new_reference Negative() 	{ return PyNumber_Negative(self()); }
	inline py_new_reference Positive() 	{ return PyNumber_Positive(self()); }
	inline py_new_reference Absolute() 	{ return PyNumber_Absolute(self()); }
	inline py_new_reference Invert() 	{ return PyNumber_Invert(self()); }
	
	inline py_new_reference Lshift(PyObject* other) 	{ return PyNumber_Lshift(self(), other); }
	inline py_new_reference Rshift(PyObject* other) 	{ return PyNumber_Rshift(self(), other); }

	inline py_new_reference And(PyObject* other) 		{ return PyNumber_And(self(), other); }
	inline py_new_reference Xor(PyObject* other) 		{ return PyNumber_Xor(self(), other); }
	inline py_new_reference Or(PyObject* other) 		{ return PyNumber_Or(self(), other); }

	inline py_new_reference InPlaceAdd(PyObject* other) 			{ return PyNumber_InPlaceAdd(self(), other); }
	inline py_new_reference InPlaceSubtract(PyObject* other) 		{ return PyNumber_InPlaceSubtract(self(), other); }
	inline py_new_reference InPlaceMultiply(PyObject* other) 		{ return PyNumber_InPlaceMultiply(self(), other); }
	inline py_new_reference InPlaceMatrixMultiply(PyObject* other) 		{ return PyNumber_InPlaceMatrixMultiply(self(), other); }
	
	inline py_new_reference InPlaceFloorDivide(PyObject* other) 		{ return PyNumber_InPlaceFloorDivide(self(), other); }
	inline py_new_reference InPlaceTrueDivide(PyObject* other) 		{ return PyNumber_InPlaceTrueDivide(self(), other); }
	inline py_new_reference InPlaceRemainder(PyObject* other) 		{ return PyNumber_InPlaceRemainder(self(), other); }
	inline py_new_reference InPlacePower(PyObject* other, PyObject* p) 	{ return PyNumber_InPlacePower(self(), other, p); }


	inline py_new_reference InPlaceLshift(PyObject* other)	{ return PyNumber_InPlaceLshift(self(), other); }
	inline py_new_reference InPlaceRshift(PyObject* other)	{ return PyNumber_InPlaceRshift(self(), other); }
	inline py_new_reference InPlaceAnd(PyObject* other) 	{ return PyNumber_InPlaceAnd(self(), other); }
	inline py_new_reference InPlaceXor(PyObject* other) 	{ return PyNumber_InPlaceXor(self(), other); }
	inline py_new_reference InPlaceOr(PyObject* other) 	{ return PyNumber_InPlaceOr(self(), other); }
	
	inline py_new_reference Long() 			{ return PyNumber_Long(self());  }
	inline py_new_reference Float() 		{ return PyNumber_Float(self()); }
	inline py_new_reference Index() 		{ return PyNumber_Index(self()); }
	inline py_new_reference ToBase(int base) 	{ return PyNumber_ToBase(self(), base); }

	inline Py_ssize_t AsSsize_t(PyObject* exc) 	{ return PyNumber_AsSsize_t(self(), exc); }
	inline int Index_Check(PyObject* exc) 		{ return PyIndex_Check(self()); }

	
};






} /* namespace py */


#endif /* PY_NUMBER_CPP_H */
