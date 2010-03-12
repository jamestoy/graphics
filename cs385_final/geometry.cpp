#include <math.h>
#include <assert.h>
#include "geometry.h"



// copy constructor
Tuple::Tuple (const Tuple& toCopy)
{
	data[0] = toCopy.data[0];
	data[1] = toCopy.data[1];
	data[2] = toCopy.data[2];
}

// assignment operator
Tuple& Tuple::operator = (const Tuple& toCopy)
{

	if (this != &toCopy) {
		data[0] = toCopy.data[0];
		data[1] = toCopy.data[1];
		data[2] = toCopy.data[2];
	}
	return *this;
}

// comparison
const bool Tuple::operator == (const Tuple& compare) const
{
	
	if (data[0]==compare.data[0] && data[1] == compare.data[1] && data[2] == compare.data[2])
		return true;
	return false;
}

// comparison - not
const bool Tuple::operator != (const Tuple& compare) const
{
	return !(*this==compare);
}


// addition
const Tuple Tuple::operator + (const Tuple& toAdd) const
{
	Tuple sum = *this;
	sum += toAdd;
	return sum;
}

// unary addition
Tuple& Tuple::operator += (const Tuple& toAdd)
{
	data[0] += toAdd.data[0];
	data[1] += toAdd.data[1];
	data[2] += toAdd.data[2];
	return *this;
}

// subtraction
const Tuple Tuple::operator - (const Tuple& toSub) const
{
	Tuple diff=*this;
	diff -= toSub;
	return diff;
}

// unary subtraction
Tuple& Tuple::operator -= (const Tuple& toSub)
{
	data[0] -= toSub.data[0];
	data[1] -= toSub.data[1];
 	data[2] -= toSub.data[2];
	return *this;
}


// negation
const Tuple Tuple::operator - () const
{
	Tuple neg = *this;
	neg *= -1;
	return neg;
}



// unary scalar multiplication
Tuple& Tuple::operator *= (float scaleFactor)
{
	data[0] *= scaleFactor;
	data[1] *= scaleFactor;
    data[2] *= scaleFactor;
	return *this;
}



// unary scalar multiplication
Tuple& Tuple::operator /= (float scaleFactor)
{
	assert(scaleFactor !=0);
	data[0] /= scaleFactor;
	data[1] /= scaleFactor;
	data[2] /= scaleFactor;
	return *this;
}


// index
float& Tuple::operator [] (const int i)
{
	assert(i>=0 && i < 3);
	return data[i];
}

// read-only index
const float& Tuple::operator [] (const int i) const
{
	assert(i>=0 && i < 3);
	return data[i];
}


// dot product
const float Tuple::dot (const Tuple& toDot) const
{
	float dotProduct = data[0]*toDot.data[0] + data[1]*toDot.data[1] + data[2]*toDot.data[2];
	return dotProduct;
}

// cross product
const Tuple Tuple::cross (const Tuple& toCross) const
{
  Tuple crossProduct;
  crossProduct.data[0] = data[1] * toCross.data[2] - data[2] * toCross.data[1];
  crossProduct.data[1] = data[2] * toCross.data[0] - data[0] * toCross.data[2];
  crossProduct.data[2] = data[0] * toCross.data[1] - data[1] * toCross.data[0];
  return crossProduct;
}


// normalize
Tuple& Tuple::normalize ()
{
  float len = this->length();

  assert(len!=0);
  data[0] /= len;
  data[1] /= len;
  data[2] /= len;
  
  return *this;
}


// get length
const float Tuple::length() const
{
  double sumSquares = data[0]*data[0] + data[1]*data[1] + data[2]*data[2];

  return (float) sqrt(sumSquares);
}


// scalar multiplication
const Tuple operator * (const Tuple& toMultiply, const float& factor)
{
  Tuple product = toMultiply;
  product *= factor;
  return product;
}

// scalar multiplication
const Tuple operator * (const float& factor,const Tuple& toMultiply)
{
  return toMultiply*factor;
}

// scalar division
const Tuple operator / (const Tuple& toDivide, const float& factor)
{
	Tuple quotient = toDivide;
	quotient /= factor;
	return quotient;
}

// write
ostream &operator<<(ostream &out_file, const Tuple& theTuple)
{
	out_file << theTuple[0] << ", " << theTuple[1] << ", " << theTuple[2];
	return out_file;
}

/********************************************************/
/*						       	*/
/*						       	*/
/*  This method transforms a Tuple based on a		*/
/*	tranformation matrix			*/
/********************************************************/

Tuple Tuple::matrixMultiply(float m[])
{
	// m is a 4x4 matrix stored in column-major order
	// in a length 16 array
	// 
	// to compute the multiplication we should convert
	// this into a 4-tuple with a 1 in the new dimension
	// perform the multiplication, then strip off the
	// last dimension
	//
	// the following achieves the same effect
	// without the conversion
	Tuple tmp(0,0,0);
	for (int j=0; j<3; j++) { // for each row of the matrix 
		for (int k=0; k<3; k++) {  // for each column
			tmp[j] += m[j+4*k]*data[k];  // the matrix is column-major
		}
		tmp[j]+=m[j+12];
	}

	return tmp;

}


