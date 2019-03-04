
#ifndef MATRIX_HPP
#define MATRIX_HPP
#include "matrix.h"

/* C++ matrix functions. */

class Matrix;
class Vector;

Matrix operator*(Matrix &a, Matrix &b);
Vector operator*(Matrix &a, Vector &b);
Matrix operator*(Matrix &a, vecc_t b);
Matrix operator+(Matrix &a, Matrix &b);
Matrix operator-(Matrix &a, Matrix &b);

Vector operator*(Vector &a, vecc_t b);
Vector operator+(Vector &a, Vector &b);
Vector operator-(Vector &a, Vector &b);

class Matrix
{
	private:
		matrix_t mat;
	public:
		Matrix(matrix_t matrix);
		Matrix(
			vecc_t m11, vecc_t m12, vecc_t m13, vecc_t m14,
			vecc_t m21, vecc_t m22, vecc_t m23, vecc_t m24,
			vecc_t m31, vecc_t m32, vecc_t m33, vecc_t m34,
			vecc_t m41, vecc_t m42, vecc_t m43, vecc_t m44);
		friend Matrix operator*(Matrix &a, Matrix &b);
		friend Matrix operator*(Matrix &a, vecc_t b);
		friend Vector operator*(Matrix &a, Vector &b);
		friend Matrix operator+(Matrix &a, Matrix &b);
		friend Matrix operator-(Matrix &a, Matrix &b);
		
		Matrix inverse();
};


/* C++ vector functions. */

class Vector
{
	private:
		vector_t vec;
	public:
		Vector(vector_t vector);
		Vector(vecc_t x, vecc_t y, vecc_t z, vecc_t w);
		Vector(vecc_t x, vecc_t y, vecc_t z);
		Vector(vecc_t x, vecc_t y);
		Vector(vecc_t xyzw);
		friend Vector operator*(Matrix &a, Vector &b);
		friend Vector operator*(Vector &a, vecc_t b);
		friend Vector operator+(Vector &a, Vector &b);
		friend Vector operator-(Vector &a, Vector &b);
		
		vecc_t dot(Vector &b);
		Vector cross(Vector &b);
		vecc_t getX();
		vecc_t getY();
		vecc_t getZ();
		vecc_t getW();
};

#endif
