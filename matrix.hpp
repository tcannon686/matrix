#ifndef MATRIX_HPP
#define MATRIX_HPP

#include <algorithm>
#include <cmath>
#include <iostream>
#include <initializer_list>
#include <stdexcept>

namespace tmat
{
    using namespace std;
    template<int N, typename T>
    class Vector
    {
        private:
            static_assert(N > 0);
            T components[N];
        public:
            const static Vector<N, T> right;
            const static Vector<N, T> up;
            const static Vector<N, T> forward;
            const static Vector<N, T> zero;
            Vector()
            {
                for(int i = 0; i < N; i ++)
                {
                    components[i] = 0;
                }
            }
            Vector(const Vector &other)
            {
                for(int i = 0; i < N; i ++)
                {
                    components[i] = other.components[i];
                }
            }
            Vector(initializer_list<T> components)
            {
                if(components.size() > N)
                    throw invalid_argument("invalid number of arguments");
                int i = 0;
                for(auto it = components.begin();
                    it != components.end();
                    ++ it)
                {
                    this->components[i] = *it;
                    i ++;
                }
                
                /* Fill the rest with zeros. */
                while(i < N)
                {
                    this->components[i] = 0;
                    i ++;
                }
            }

            T &operator[](int i)
            {
                return components[i];
            }

            const T &operator[](int i) const
            {
                return components[i];
            }

            Vector<N, T> operator*(const T &right) const
            {
                Vector<N, T> ret;
                for(int i = 0; i < N; i ++)
                {
                    ret[i] = components[i] * right;
                }
                return ret;
            }
            void operator*=(const T &right)
            {
                Vector<N, T> ret;
                for(int i = 0; i < N; i ++)
                {
                    components[i] *= right;
                }
            }
            Vector<N, T> operator*(const Vector<N, T> &right) const
            {
                Vector<N, T> ret;
                for(int i = 0; i < N; i ++)
                {
                    ret[i] = components[i] * right[i];
                }
                return ret;
            }
            void operator*=(const Vector<N, T> &right)
            {
                Vector<N, T> ret;
                for(int i = 0; i < N; i ++)
                {
                    components[i] *= right[i];
                }
            }
            Vector<N, T> operator+(const Vector<N, T> &right) const
            {
                Vector<N, T> ret;
                for(int i = 0; i < N; i ++)
                {
                    ret[i] = components[i] + right[i];
                }
                return ret;
            }
            void operator+=(const Vector<N, T> &right)
            {
                for(int i = 0; i < N; i ++)
                {
                    components[i] += right[i];
                }
            }
            Vector<N, T> operator-(const Vector<N, T> &right) const
            {
                Vector<N, T> ret;
                for(int i = 0; i < N; i ++)
                {
                    ret[i] = components[i] - right[i];
                }
                return ret;
            }
            void operator-=(const Vector<N, T> &right)
            {
                Vector<N, T> ret;
                for(int i = 0; i < N; i ++)
                {
                    components[i] -= right[i];
                }
            }
            Vector<N, T> operator-() const
            {
                Vector<N, T> ret;
                for(int i = 0; i < N; i ++)
                {
                    ret[i] = -components[i];
                }
                return ret;
            }

            bool operator==(const Vector<N, T> &right) const
            {
                for(int i = 0; i < N; i ++)
                {
                    if(components[i] != right[i])
                        return false;
                }
                return true;
            }

            bool operator>(const Vector<N, T> &right) const
            {
                for(int i = 0; i < N; i ++)
                {
                    if(components[i] <= right[i])
                        return false;
                }
                return true;
            }

            bool operator<(const Vector<N, T> &right) const
            {
                for(int i = 0; i < N; i ++)
                {
                    if(components[i] >= right[i])
                        return false;
                }
                return true;
            }

            bool operator>=(const Vector<N, T> &right) const
            {
                for(int i = 0; i < N; i ++)
                {
                    if(components[i] < right[i])
                        return false;
                }
                return true;
            }

            bool operator<=(const Vector<N, T> &right) const
            {
                for(int i = 0; i < N; i ++)
                {
                    if(components[i] > right[i])
                        return false;
                }
                return true;
            }

            T dot(const Vector<N, T> &right) const
            {
                T ret = 0;
                for(int i = 0; i < N; i ++)
                {
                    ret += components[i] * right[i];
                }
                return ret;
            }

            T magnitude() const
            {
                T ret = 0;
                for(int i = 0; i < N; i ++)
                {
                    ret += components[i] * components[i];
                }
                return sqrt(ret);
            }

            Vector<N, T> cross(const Vector<N, T> &right) const
            {
                static_assert(N == 3);
                Vector<N, T> ret;
                for(int i = 0; i < N; i ++)
                {
                    int x = i, y = (i + 1) % N, z = (i + 2) % N;
                    /* xyzzy */
                    ret[x] = components[y] * right[z]
                        - components[z] * right[y];
                }
                return ret;
            }

            void normalize()
            {
                T length = this->magnitude();
                for(int i = 0; i < N; i ++)
                {
                    components[i] /= length;
                }
            }

            Vector<N, T> normalized() const
            {
                Vector<N, T> ret = *this;
                ret.normalize();
                return ret;
            }

            /* Cut the last element off the vector. */
            Vector<N - 1, T> cut() const
            {
                Vector<N - 1, T> ret;
                for(int i = 0; i < N - 1; i ++)
                {
                    ret[i] = components[i];
                }
                return ret;
            }

            /* Add another 1 to the end of the vector. */
            Vector<N + 1, T> homo() const
            {
                Vector<N + 1, T> ret;
                for(int i = 0; i < N; i ++)
                {
                    ret[i] = components[i];
                }
                ret[N] = 1;

                return ret;
            }

            template<typename U>
            void toArray(U ret[]) const
            {
                for(int i = 0; i < N; i ++)
                {
                    ret[i] = components[i];
                }
            }

            template<int M, typename U>
            friend ostream &operator<<(
                    ostream &stream,
                    const Vector<M, U> &vector);
    };
    template<int N, typename T>
    ostream &operator<<(ostream &stream, const Vector<N, T> &vector)
    {
        stream << "Vector { " << vector.components[0];
        for(int i = 1; i < N; i ++)
        {
            stream << ", " << vector.components[i];
        }
        stream << " } ";
        return stream;
    }

    typedef Vector<2, float> Vector2f;
    typedef Vector<3, float> Vector3f;
    typedef Vector<4, float> Vector4f;

    template<int N, typename T>
    const Vector<N, T> Vector<N, T>::right{1.0f};
    template<int N, typename T>
    const Vector<N, T> Vector<N, T>::up{0.0f, 1.0f};
    template<int N, typename T>
    const Vector<N, T> Vector<N, T>::forward{0.0f, 0.0f, 1.0f};
    template<int N, typename T>
    const Vector<N, T> Vector<N, T>::zero{};

    template<int M, int N, typename T>
    class Matrix
    {
        private:
            static_assert(N > 0);
            static_assert(M > 0);
            Vector<N, T> rows[M];
        public:
            static const Matrix<M, N, T> identity;
            /*
             * Create from a list of components, row major.
             */
            Matrix(initializer_list<initializer_list<T>> rows)
            {
                if(rows.size() != M)
                    throw invalid_argument("invalid number of arguments");

                int i = 0, j;
                for(auto it = rows.begin();
                    it != rows.end();
                    ++ it)
                {
                    if(it->size() != N)
                        throw invalid_argument("invalid number of arguments");
                    j = 0;
                    for(auto jt = it->begin();
                        jt != it->end();
                        ++ jt)
                    {
                        this->rows[i][j] = *jt;
                        j ++;
                    }
                    i++;
                }
            }

            /*
             * Create an identity matrix times scale.
             */
            Matrix(T scale)
            {
                for(int i = 0; i < M; i ++)
                {
                    for(int j = 0; j < N; j ++)
                    {
                        if(i == j)
                            rows[i][j] = scale;
                        else
                            rows[i][j] = 0;
                    }
                }
            }

            Matrix()
            {
                for(int i = 0; i < M; i ++)
                {
                    rows[i] = Vector<N, T>::zero;
                }
            }

            void getColumn(Vector<M, T> &out, int i) const
            {
                for(int j = 0; j < M; j ++)
                {
                    out[j] = rows[j][i];
                }
            }

            void setColumn(int i, Vector<M, T> column)
            {
                for(int j = 0; j < M; j ++)
                {
                    rows[j][i] = column[j];
                }
            }

            void getRow(Vector<N, T> &out, int i) const
            {
                out = rows[i];
            }

            void setRow(int i, Vector<N, T> row)
            {
                rows[i] = row;
            }

            Vector<M, T> column(int i) const
            {
                Vector<M, T> ret;
                for(int j = 0; j < M; j ++)
                {
                    ret[j] = rows[j][i];
                }
                return ret;
            }

            Vector<N, T> row(int i) const
            {
                return row[i];
            }

            /* Return the row vector at i. */
            Vector<N, T> &operator[](int i)
            {
                return rows[i];
            }

            const Vector<N, T> &operator[](int i) const
            {
                return rows[i];
            }

            Vector<M, T> operator*(const Vector<N, T> &other) const
            {
                Vector<M, T> ret;
                for(int i = 0; i < M; i ++)
                {
                    ret[i] = rows[i].dot(other);
                }
                return ret;
            }

            template<int L>
            Matrix<M, L, T> operator*(const Matrix<N, L, T> &other) const
            {
                Matrix<M, L, T> ret;
                for(int i = 0; i < M; i ++)
                {
                    for(int j = 0; j < L; j ++)
                    {
                        ret[i][j] = rows[i].dot(other.column(j));
                    }
                }
                return ret;
            }

            bool operator==(const Matrix<M, N, T> &other) const
            {
                for(int i = 0; i < M; i ++)
                {
                    for(int j = 0; j < N; j ++)
                    {
                        if(rows[i][j] != other.rows[i][j])
                            return false;
                    }
                }
                return true;
            }

            T determinant() const
            {
                static_assert(M == N);
                T ret = 0;
                for(int i = 0; i < M; i ++)
                {
                    T d0 = 1, d1 = 1;
                    for(int j = 0; j < N; j ++)
                    {
                        d0 *= rows[(i + j) % M][j];
                        d1 *= rows[(i + j) % M][N - j - 1];
                        if(d0 == 0 || d1 == 0)
                            break;
                    }
                    ret += d0 - d1;
                }
                return ret;
            }

            T trace() const
            {
                T ret = 0;
                for(int i = 0; i < min(M, N); i ++)
                {
                    ret += rows[i][i];
                }
                return ret;
            }

            void reduce()
            {
                int i = 0, j = 0;
                while(i < M && j < N)
                {
                    /* Find the row for the pivot column. */
                    int max_i = i;
                    for(int k = i + 1; k < M; k ++)
                    {
                        if(abs(rows[k][j]) > abs(rows[max_i][j]))
                        {
                            max_i = k;
                        }
                    }
                    if(rows[max_i][j] == 0)
                        j ++;
                    else
                    {
                        swap(rows[i], rows[max_i]);

                        T scale = 1 / rows[i][j];
                        rows[i] *= scale;

                        for(int k = i + 1; k < M; k ++)
                        {
                            rows[k] -= rows[i] * rows[k][j];
                        }
                        i ++;
                        j ++;
                    }
                }
                for(i = min(M, N) - 1; i >= 0; i --)
                {
                    for(j = i - 1; j >= 0; j --)
                    {
                        rows[j] -= rows[i] * rows[j][i];
                    }
                }
            }

            Matrix<M, N, T> reduced() const
            {
                Matrix<M, N, T> ret = *this;
                ret.reduce();
                return ret;
            }
        
            void invert()
            {
                static_assert(M == N);
                Matrix<M, N * 2, T> mat;
                for(int j = 0; j < N; j ++)
                {
                    mat.setColumn(j, column(j));
                }
                for(int j = 0; j < N; j ++)
                {
                    mat[j][j + N] = 1;
                }
                mat.reduce();
                for(int j = 0; j < N; j ++)
                {
                    setColumn(j, mat.column(j + N));
                }
            }

            Matrix<M, N, T> inverse() const
            {
                Matrix<M, N, T> mat = *this;
                mat.invert();
                return mat;
            }

            void transpose()
            {
                static_assert(M == N);
                for(int i = 0; i < M; i ++)
                {
                    for(int j = 0; j < i; j ++)
                    {
                        swap(rows[i][j], rows[j][i]);
                    }
                }
            }

            Matrix<N, M, T> transposed() const
            {
                Matrix<N, M, T> ret = *this;
                for(int i = 0; i < M; i ++)
                {
                    for(int j = 0; j < N; j ++)
                    {
                        ret[i][j] = rows[j][i];
                    }
                }
                return ret;
            }

            void sub(Matrix<M - 1, N - 1, T> &out, int m, int n) const
            {
                for(int i = 0; i < M - 1; i ++)
                {
                    for(int j = 0; j < N - 1; j ++)
                    {
                        out[i][j] = rows[i < m ? i : i + 1]
                                        [j < n ? j : j + 1];
                    }
                }
            }

            Matrix<M - 1, N - 1, T> sub(int m, int n) const
            {
                Matrix<M - 1, N - 1, T> ret;
                sub(ret, m, n);
                return ret;
            }

            /*
             * Put the matrix into an array, default column major order.
             */
            template<typename U>
            void toArray(U ret[], bool transpose) const
            {
                if(!transpose)
                {
                    for(int i = 0; i < M; i ++)
                    {
                        for(int j = 0; j < N; j ++)
                        {
                            ret[i + j * M] = rows[i][j];
                        }
                    }
                }
                else
                {
                    for(int i = 0; i < M; i ++)
                    {
                        for(int j = 0; j < N; j ++)
                        {
                            ret[j + i * N] = rows[i][j];
                        }
                    }
                }
            }

            template<typename U>
            void toArray(U ret[]) const
            {
                toArray(ret, false);
            }

            template<int I, int J, typename U>
            friend ostream &operator<<(
                    ostream &stream,
                    const Matrix<I, J, U> &vector);
    };
    template<int M, int N, typename T>
    ostream &operator<<(ostream &stream, const Matrix<M, N, T> &matrix)
    {
        stream << "Matrix { ";
        for(int i = 0; i < M; i ++)
        {
            cout << "{ " << matrix[i][0];
            for(int j = 1; j < N; j ++)
            {
                cout << ", " << matrix[i][j];
            }
            cout << " }";
            if(i + 1 < M)
                cout << ", ";
        }
        stream << " }";
        return stream;
    }

    template<int M, int N, typename T>
    const Matrix<M, N, T> Matrix<M, N, T>::identity(1);

    typedef Matrix<2, 2, float> Matrix2f;
    typedef Matrix<3, 3, float> Matrix3f;
    typedef Matrix<4, 4, float> Matrix4f;


    template<class T>
    Matrix<4, 4, T> getTranslateMatrix(Vector<3, T> t)
    {
        return Matrix<4, 4, T> {
            { 1, 0, 0, t[0] },
            { 0, 1, 0, t[1] },
            { 0, 0, 1, t[2] },
            { 0, 0, 0, 1 }
        };
    }

    template<class T>
    Matrix<4, 4, T> getTranslateMatrix(Vector<4, T> t)
    {
        return Matrix<4, 4, T> {
            { 1, 0, 0, t[0] },
            { 0, 1, 0, t[1] },
            { 0, 0, 1, t[2] },
            { 0, 0, 0, 1 }
        };
    }

    template<class T>
    Matrix<4, 4, T> getScaleMatrix(Vector<3, T> t)
    {
        return Matrix<4, 4, T> {
            { t[0],    0,    0,    0 },
            {    0, t[1],    0,    0 },
            {    0,    0, t[2],    0 },
            {    0,    0,    0,    1 }
        };
    }

    template<class T>
    Matrix<4, 4, T> getScaleMatrix(Vector<4, T> t)
    {
        return Matrix<4, 4, T> {
            { t[0],    0,    0,    0 },
            {    0, t[1],    0,    0 },
            {    0,    0, t[2],    0 },
            {    0,    0,    0,    1 }
        };
    }

    template<class T>
    Matrix<4, 4, T> getRotateMatrix(T angle, Vector<3, T> axis)
    {
        T s = sin(angle);
        T c = cos(angle);
        T x = axis[0];
        T y = axis[1];
        T z = axis[2];
        return Matrix<4, 4, T>{
            {   x*x*(1-c)+c, x*y*(1-c)-z*s, x*z*(1-c)+y*s,             0 },
            { y*x*(1-c)+z*s,   y*y*(1-c)+c, y*z*(1-c)-x*s,             0 },
            { x*z*(1-c)-y*s, y*z*(1-c)+x*s,   z*z*(1-c)+c,             0 },
            {             0,             0,             0,             1 }
        };
    }

    template<class T>
    Matrix<4, 4, T> getRotateMatrix(T angle, Vector<4, T> axis)
    {
        T s = sin(angle);
        T c = cos(angle);
        T x = axis.x;
        T y = axis.y;
        T z = axis.z;
        return Matrix<4, 4, T>{
            {   x*x*(1-c)+c, x*y*(1-c)-z*s, x*z*(1-c)+y*s,             0 },
            { y*x*(1-c)+z*s,   y*y*(1-c)+c, y*z*(1-c)-x*s,             0 },
            { x*z*(1-c)-y*s, y*z*(1-c)+x*s,   z*z*(1-c)+c,             0 },
            {             0,             0,             0,             1 }
        };
    }
};

#endif
