#ifndef GEOMETRY_H
#define GEOMETRY_H

#include <iostream>
/****************************************************/
/*													*/
/*	This is a class for 3D vectors with standard	*/
/*	vector operations.								*/
/*													*/
/****************************************************/

using namespace std;

class Tuple
{
 public:

	// constructors
	Tuple() {data[0]=data[1]=data[2]=0;}					// default construcotr
	Tuple(const float x, const float y, const float z)	// constructor
		{data[0]=x, data[1]=y, data[2]=z;}
	Tuple(const Tuple& toCopy);							// copy constructor

	// destructor
	virtual ~Tuple() {};

	// operators
	Tuple&		operator =	(const Tuple& toCopy);			// assignment
	const bool	operator ==	(const Tuple& toCompare) const;	// equality
	const bool	operator !=	(const Tuple& toCompare) const;	// inequality
	const Tuple	operator +	(const Tuple& toAdd) const;		// addition
	Tuple&		operator +=	(const Tuple& toAdd);			// unary addition
	const Tuple	operator -	() const;						// negation 
	const Tuple	operator -	(const Tuple& toSub) const;		// subtraction
	Tuple&		operator -=	(const Tuple& toSub);			// unary subtraction
	Tuple&		operator *=	(float scaleFactor);			// scalar unary multiplication
	Tuple&		operator /=	(float scaleFactor);			// sclar division
	
	//tricky matrix multiply see comments in geometry.cpp
	Tuple matrixMultiply(float m[]);

	// accessors
	float&		operator[]	(const int index);				// index
	const float&	operator[]	(const int index) const;	// read only indexing

	// vector operations
	const float dot(const Tuple& toDot) const;				// dot product
	const Tuple cross(const Tuple& toCross) const;			// cross product
	Tuple& normalize(void);									// normalize
	const float length(void) const;							// compute length
  
 private:
	float data[3];

;
};

//  related functions
const Tuple	operator *(const Tuple& toMultiply, const float& scaleFactor);
const Tuple	operator *(const float& scaleFactor, const Tuple& toMultiply);
const Tuple operator /(const Tuple& toDivide, const float& scaleFactor);
ostream &operator<<(ostream &out_file, const Tuple& theTuple);

#endif // GEOMETRY_H

