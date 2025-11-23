#pragma once
#include "MyVector.hpp"
#include <cmath>
#include <cstddef>
#include <stdexcept>
#include <utility>
#include <type_traits>
#include <limits>

namespace matrix
{
    template <typename T>
    class Matrix
    {
        private:
            size_t                                      rows_;
            size_t                                      columns_;
            My_vector::vector<My_vector::vector<T>>     matrix_;

        public: // RULE OF FIVE
            Matrix(): rows_(0), columns_(0), matrix_() {};

            Matrix(size_t rows,size_t columns);
            Matrix(size_t rows,size_t columns,T value);
            Matrix(size_t n): Matrix(n,n) {};

            ~Matrix() = default;

            Matrix(const Matrix<T>& other): rows_(other.rows_), columns_(other.columns_),
                                                       matrix_(other.rows_)
            { for (size_t i = 0; i < rows_; ++i) matrix_[i] = other.matrix_[i]; }

            template<typename U>
            Matrix(const Matrix<U>& other_matrix );


            Matrix(Matrix&& other_matrix) noexcept: rows_(other_matrix.rows_), columns_(other_matrix.columns_),
                                                    matrix_(std::move(other_matrix.matrix_))
            {
                other_matrix.rows_ = 0;
                other_matrix.columns_ = 0;
            };


            Matrix& operator=(const Matrix& other_matrix);
            Matrix& operator=(Matrix&& other_matrix) noexcept;

        public: //operation with matrix
            Matrix operator-() const;

            Matrix operator+(const Matrix& other_matrix) const;
            Matrix operator-(const Matrix& other_matrix) const;
            Matrix operator*(const T& a)                 const;


            Matrix& operator+=(const Matrix& other_matrix);
            Matrix& operator-=(const Matrix& other_matrix);

        public: //Element access
            My_vector::vector<T>& operator[](size_t pivot) { return matrix_[pivot];}
            const My_vector::vector<T>& operator[](size_t pivot) const {return matrix_[pivot];}

        public: // Сapacity
            size_t rows() const { return rows_; }
            size_t cols() const { return columns_; }

    };
//-----------------------------------------------------------------------------------------------------------------------------------
//-----------------------------------------Operation with Matrix---------------------------------------------------------------------------------------
//-----------------------------------------------------------------------------------------------------------------------------------

        template <typename T>
        Matrix<T> Matrix<T>::operator-() const
        {
            Matrix<T> res{*this};
            for (size_t cur_row = 0; cur_row < rows_; ++cur_row)
                for (size_t j = 0; j < columns_; ++j)
                    res[cur_row][j] = -res[cur_row][j];
            return res;
        }

        template <typename T>
        Matrix<T> Matrix<T>::operator+(const Matrix& other_matrix) const
        {
            if (rows_ != other_matrix.rows_ || columns_ != other_matrix.columns_)
                throw std::runtime_error("operator +:Matrix mismatch ");

            Matrix<T> res{*this};
            res += other_matrix;
            return res;
        }

        template <typename T>
        Matrix<T> Matrix<T>::operator-(const Matrix& other_matrix) const
        {
            if (rows_ != other_matrix.rows_ || columns_ != other_matrix.columns_)
                throw std::runtime_error("operator -:Matrix mismatch ");

            Matrix<T> res{*this};
            res += -other_matrix;
            return res;
        }


        template <typename T>
        Matrix<T> Matrix<T>::operator*(const T& a) const
        {
            Matrix<T> res{*this};
            for (size_t cur_row = 0; cur_row < rows_; ++cur_row)
                for (size_t j = 0; j < columns_; ++j)
                    res[cur_row][j] *= a;
            return res;
        }

        template <typename T>
        Matrix<T> operator*(const T& a,const Matrix<T>& m) { return m*a; }

        template <typename T>
        Matrix<T>& Matrix<T>::operator+=(const Matrix<T>& other_matrix)
        {
            if (rows_ != other_matrix.rows_ || columns_ != other_matrix.columns_)
                throw std::runtime_error("operator +=:Matrix mismatch ");

            for (size_t cur_row = 0; cur_row < rows_; ++cur_row)
                for (size_t j = 0; j < columns_; ++j)
                    matrix_[cur_row][j] += other_matrix[cur_row][j];
            return *this;
        }

        template <typename T>
        Matrix<T>& Matrix<T>::operator-=(const Matrix<T>& other_matrix)
        {
            if (rows_ != other_matrix.rows_ || columns_ != other_matrix.columns_)
                throw std::runtime_error("operator -=:Matrix mismatch ");

            for (size_t cur_row = 0; cur_row < rows_; ++cur_row)
                for (size_t j = 0; j < columns_; ++j)
                    matrix_[cur_row][j] -= other_matrix[cur_row][j];
            return *this;
        }



//------------------------------------------------------------------------------------------------------
//--------------------------- The Rule of Five ---------------------------------------------------------
//------------------------------------------------------------------------------------------------------
    template <typename T>
    template <typename U>
    Matrix<T>::Matrix(const Matrix<U>& other_matrix): rows_(other_matrix.rows()), columns_(other_matrix.cols()),
                                               matrix_(other_matrix.rows())
    {
        for (size_t i = 0; i < rows_; ++i) {
            matrix_[i] = My_vector::vector<T>(columns_);
            for (size_t j = 0; j < columns_; ++j)
                matrix_[i][j] = static_cast<T>(other_matrix[i][j]);
        }
    }


    template <typename T>
    Matrix<T>::Matrix(size_t rows,size_t columns): rows_(rows), columns_(columns), matrix_(rows)
    {
        for (size_t cur_row = 0; cur_row < rows_; ++cur_row)
            matrix_[cur_row] = My_vector::vector<T>(columns_);
    }

    template <typename T>
    Matrix<T>::Matrix(size_t rows,size_t columns, T value): rows_(rows), columns_(columns), matrix_(rows)
    {
        for (size_t cur_row = 0; cur_row < rows_;  ++cur_row)
            matrix_[cur_row] = My_vector::vector<T>(columns_, value);
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
        rows_                 = other_matrix.rows_;
        columns_              = other_matrix.columns_;

        other_matrix.columns_ = 0;
        other_matrix.rows_    = 0;

        return *this;
    }


//-----------------------------------------------------------------------------------------------------------------------------------
//-------------------------------------------determinant-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------------------------------------------------------------


// Determinant (floating point)
    template <typename T>
    T det(const Matrix<T>& A)
    {
        if (A.cols() != A.rows())
            throw std::runtime_error("det : Matrix size mismatch ");

        Matrix<long double> B = A;
        size_t sign = 0;

        for (size_t cur_row = 0, rows = B.rows(); cur_row < rows  ; ++cur_row)
        {
            long double max_val = 0;
            size_t pivot_row    = cur_row;

            for (size_t i = cur_row; i < rows; ++i)
            {
                long double cur_val = std::abs(B[i][cur_row]);
                if (cur_val > max_val)
                {
                    max_val    =  cur_val;
                    pivot_row  =  i;
                }
            }
            if (!max_val) return 0;

            if (pivot_row != cur_row)
            {
                My_vector::vector<long double> temp_row = B[cur_row];
                B[cur_row]                              = B[pivot_row];
                B[pivot_row]                            = temp_row;
                ++sign;
            }

            for (size_t i = cur_row+1; i < rows; ++i )
            {
                long double  k =  B[i][cur_row]/B[cur_row][cur_row];
                B[i][cur_row] = 0;

                for (size_t j = cur_row+1, cols = B.cols(); j < cols; ++j)
                    B[i][j] -= k*B[cur_row][j];
            }
        }


        long double res_det = 1;
        for (size_t i = 0, rows = A.rows(); i < rows; ++i)
            res_det *= B[i][i];

        if (sign % 2) res_det*= -1;

        return static_cast<T> (res_det);
    }


// determinant for integers (det_bar)
    template <typename T>
    std::enable_if_t<std::is_integral<T>::value, T>
    det_bar(const Matrix<T>& A)
    {
        using Big = __int128_t;
        const size_t n = A.rows();

        if (n != A.cols())
            throw std::runtime_error("det_bar: Matrix size mismatch");

        Matrix<Big> B(A);
        Big prev = 1;
        int sign = 0;

        for (size_t k = 0; k + 1 < n; ++k)
        {
            // pivot
            if (B[k][k] == 0) {
                bool found = false;
                for (size_t r = k + 1; r < n; ++r) {
                    if (B[r][k] != 0) {
                        std::swap(B[k], B[r]);
                        ++sign;
                        found = true;
                        break;
                    }
                }
                if (!found)
                    return 0;
            }

            for (size_t i = k + 1; i < n; ++i) {
                for (size_t j = k + 1; j < n; ++j) {
                    Big num = B[k][k] * B[i][j] - B[i][k] * B[k][j];
                    num /= prev;
                    B[i][j] = num;
                }
                B[i][k] = 0;
            }

            prev = B[k][k];
        }

        Big det_big = B[n - 1][n - 1];
        if (sign % 2 != 0) det_big = -det_big;
        if (det_big > std::numeric_limits<long long>::max() || det_big < std::numeric_limits<long long>::min())
            throw std::overflow_error("det_bar overflow");

        return static_cast<T>(det_big);
    }

}
