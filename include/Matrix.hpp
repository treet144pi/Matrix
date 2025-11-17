#pragma once
#include "MyVector.hpp"
#include "GeoVector.hpp"
namespace matrix
{
    template <typename T>
    class Matrix
    {
        private:
            size_t                                      columns_;
            size_t                                      rows_;
            My_vector::vector<My_vector::vector<T>>     matrix_;

        public:
            Matrix(): rows_(0), columns_(0), matrix_() {};


            Matrix(size_t rows,size_t columns);
            Matrix(size_t rows,size_t columns,T value);
            Matrix(size_t n): Matrix(n,n) {};

            ~Matrix() = default;

            Matrix(const Matrix& other_matrix ):  rows_(other_matrix.rows_), columns_(other_matrix.columns_),
                                                  matrix_(other_matrix.matrix_) {};

            Matrix(Matrix&& other_matrix) noexcept: rows_(other_matrix.rows_), columns_(other_matrix.columns_),
                                                    matrix_(std::move(other_matrix.matrix_))
            {
                other_matrix.rows_ = 0;
                other_matrix.columns_ = 0;
            };


            Matrix& operator=(const Matrix& other_matrix);
            Matrix& operator=(Matrix&& other_matrix) noexcept;

        public:
            Matrix operator-() const;

            Matrix operator+(const Matrix& other_matrix) const;
            Matrix operator-(const Matrix& other_matrix) const;
            Matrix operator*(const T& a)                 const;


            Matrix& operator+=(const Matrix& other_matrix);
            Matrix& operator-=(const Matrix& other_matrix);
        public:
            Matrix& operator[](size_t index) { return matrix_[index];}
            const Matrix& operator[](size_t index) const {return matrix_[index];}

            size_t rows() const { return rows_; }
            size_t cols() const { return columns_; }
    };
//-----------------------------------------------------------------------------------------------------------------------------------
        template <typename T>
        Matrix<T> Matrix<T>::operator-() const
        {
            Matrix<T> res{*this};
            for (size_t i = 0; i < rows_; ++i)
                for (size_t j = 0; j < columns_; ++j)
                    res[i][j] = -res[i][j];
            return res;
        }

        template <typename T>
        Matrix<T> Matrix<T>::operator+(const Matrix& other_matrix) const
        {
            Matrix<T> res{*this};
            res += other_matrix.matrix_;
            return res;
        }

        template <typename T>
        Matrix<T> Matrix<T>::operator-(const Matrix& other_matrix) const
        {
            Matrix<T> res{*this};
            res += -other_matrix.matrix_;
            return res;
        }


        template <typename T>
        Matrix<T> Matrix<T>::operator*(const T& a) const
        {
            Matrix res(*this);
            for (size_t i = 0; i < rows_; ++i)
                for (size_t j = 0; j < columns_; ++j)
                    res[i][j] *= a;
            return res;
        }

        template <typename T>
        inline Matrix<T> operator*(const T& a,const Matrix<T> m) { return m*a; }

        template <typename T>
        Matrix<T>& Matrix<T>::operator+=(const Matrix<T>& other_matrix)
        {

            for (size_t i = 0; i < rows_; ++i)
                for (size_t j = 0; j < columns_; ++j)
                    matrix_[i][j] += other_matrix[i][j];
            return *this;
        }

        template <typename T>
        Matrix<T>& Matrix<T>::operator-=(const Matrix<T>& other_matrix)
        {
            for (size_t i = 0; i < rows_; ++i)
                for (size_t j = 0; j < columns_; ++j)
                    matrix_[i][j] -= other_matrix[i][j];
            return *this;
        }






//-----------------------------------------------------------------------------------------------------------------------------------
    template <typename T>
    Matrix<T>::Matrix(size_t rows,size_t columns): rows_(rows), columns_(columns), matrix_(rows)
    {
        for (size_t i = 0; i < columns;  ++i)
            matrix_[i] = My_vector::vector<T> {columns_};
    }

    template <typename T>
    Matrix<T>::Matrix(size_t rows,size_t columns, T value): rows_(rows), columns_(columns), matrix_(columns)
    {
        for (size_t i = 0; i < columns;  ++i)
            matrix_[i] = My_vector::vector<T> {columns_,value};
    }


    template <typename T>
    Matrix<T>& Matrix<T>::operator=(const Matrix& other_matrix)
    {
        if (this == &other_matrix) return *this;

        matrix_ = other_matrix.matrix_;
        rows_   = other_matrix.rows_;
        columns_= other_matrix.columns_;
        return *this;
    }

    template <typename T>
    Matrix<T>& Matrix<T>::operator=(Matrix&& other_matrix) noexcept
    {
        if (this == &other_matrix) return *this;

        matrix_               = std::move(other_matrix.matrix_);
        other_matrix.columns_ = 0;
        other_matrix.rows_    = 0;
        rows_                 = other_matrix.rows_;
        columns_              = other_matrix.columns_;
        return *this;
    }


//--------------------------------------------------------------------------------------------------------------------
    template <typename T> // y = Ax
    GeoVector::Geo_Vector<T> operator*(const Matrix<T>& A, const GeoVector::Geo_Vector<T>& x)
    {
        if (A.cols() != x.size()) {
            throw std::runtime_error("Matrix * Geo_Vector: dimension mismatch");
        }


        GeoVector::Geo_Vector<T> y(A.rows());

        for (size_t i = 0; i < A.rows(); ++i) {
            T sum{};
            for (size_t j = 0; j < A.cols(); ++j) {
                sum += A[i][j] * x[j];
            }
            y[i] = sum;
        }

        return y;




    }


    template <typename T> //w = vt A
    GeoVector::Geo_Vector<T> operator*(const GeoVector::Geo_Vector<T>& v,
                                       const Matrix<T>& A)
    {
        if (A.rows() != v.size()) {
            throw std::runtime_error("Geo_Vector * Matrix: dimension mismatch");
        }

        GeoVector::Geo_Vector<T> w(A.cols());

        for (size_t j = 0; j < A.cols(); ++j) {
            T sum{};
            for (size_t i = 0; i < A.rows(); ++i) {
                sum += v[i] * A[i][j];
            }
            w[j] = sum;
        }

        return w;


}




}
