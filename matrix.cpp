
#include "matrix.hpp"
/* Bad coding but whatever. */
#include "matrix.c"

/* C++ matrix functions. */

Matrix::Matrix(
	matrix_t matrix)
	: mat(matrix)
{
}

Matrix::Matrix(
	vecc_t m11, vecc_t m12, vecc_t m13, vecc_t m14,
	vecc_t m21, vecc_t m22, vecc_t m23, vecc_t m24,
	vecc_t m31, vecc_t m32, vecc_t m33, vecc_t m34,
	vecc_t m41, vecc_t m42, vecc_t m43, vecc_t m44)
	: mat(
		NewMatrix(
			m11, m12, m13, m14,
			m21, m22, m23, m24,
			m31, m32, m33, m34,
			m41, m42, m43, m44)) 
{
}


Matrix operator*(Matrix &a, Matrix &b)
{
	return MatrixTimesMatrix(a.mat, b.mat);
}
Matrix operator*(Matrix &a, vecc_t b)
{
	return MatrixTimesScalar(a.mat, b);
}
Vector operator*(Matrix &a, Vector &b)
{
	return MatrixTimesVector(a.mat, b.vec);
}

Matrix operator+(Matrix &a, Matrix &b)
{
	return MatrixPlusMatrix(a.mat, b.mat);
}

Matrix operator-(Matrix &a, Matrix &b)
{
	return MatrixMinusMatrix(a.mat, b.mat);
}

Matrix Matrix::inverse()
{
	return MatrixInverse(this->mat);
}


/* C++ vector functions. */
Vector::Vector(vector_t vector)
	: vec(vector)
{
}

Vector::Vector(vecc_t x, vecc_t y, vecc_t z, vecc_t w)
	: vec(vec4(x, y, z, w))
{
}

Vector::Vector(vecc_t x, vecc_t y, vecc_t z)
	: vec(vec3(x, y, z))
{
}

Vector::Vector(vecc_t x, vecc_t y)
	: vec(vec2(x, y))
{
}

Vector::Vector(vecc_t xyzw)
	: vec(vec4(xyzw, xyzw, xyzw, xyzw))
{
}

Vector operator*(Vector &a, vecc_t b)
{
	return VectorTimesScalar(a.vec, b);
}

Vector operator+(Vector &a, Vector &b)
{
	return VectorPlusVector(a.vec, b.vec);
}

Vector operator-(Vector &a, Vector &b)
{
	return VectorMinusVector(a.vec, b.vec);
}

vecc_t Vector::dot(Vector &b)
{
	return VectorDotVector(this->vec, b.vec);
}

Vector Vector::cross(Vector &b)
{
	return VectorCrossVector(this->vec, b.vec);
}

vecc_t Vector::getX()
{
	return this->vec.x;
}

vecc_t Vector::getY()
{
	return this->vec.y;
}

vecc_t Vector::getZ()
{
	return this->vec.z;
}

vecc_t Vector::getW()
{
	return this->vec.w;
}

