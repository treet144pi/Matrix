#pragma once
#include "MyVector.hpp"
#include <utility>
#include <cmath>
namespace GeoVector{
    template <typename T>
    class Geo_Vector
    {
        private:
            My_vector::vector<T> geo_v_;
        public:

            Geo_Vector() = default;

            Geo_Vector(My_vector::vector<T> v): geo_v_(v) {};
            Geo_Vector(size_t s): geo_v_(s) {};
            Geo_Vector(size_t s,T value): geo_v_(s,value) {};

            ~Geo_Vector() = default;
            Geo_Vector(const Geo_Vector<T>& other_vector): geo_v_(other_vector.geo_v_) {};

            Geo_Vector(Geo_Vector<T>&& other_vector) noexcept: geo_v_(std::move(other_vector.geo_v_)) {};

            Geo_Vector& operator=(const Geo_Vector& other_vector);
            Geo_Vector& operator=(Geo_Vector&& other_vector) noexcept;

        public:
            Geo_Vector operator-() const;

            Geo_Vector& operator+=(const Geo_Vector& other_vector);
            Geo_Vector& operator-=(const Geo_Vector& other_vector);

            Geo_Vector operator-(const Geo_Vector& other_vector) const;
            Geo_Vector operator+(const Geo_Vector& other_vector) const;

            Geo_Vector operator*(const T& a) const;

        public:
            T& operator[](size_t index) { return geo_v_[index]; } // accurately
            const T& operator[](size_t index) const { return geo_v_[index]; }
            size_t size() const { return geo_v_.size(); }
            T norm_2() const
            {
                T sum{};
                for (size_t i = 0; i < size(); ++i)
                    sum += (*this)[i] * (*this)[i];
                return sum;
            }

            double norm() const
            {
                return std::sqrt(static_cast<double>(norm2()));
            }
    };

//-------------------------------------------------------------------------------------------------------------------------
    template <typename T>
    Geo_Vector<T>& Geo_Vector<T>::operator=(const Geo_Vector<T>& other_vector)
    {
        if (this == &other_vector) return *this;

        geo_v_ = other_vector.geo_v_;
        return *this;
    }
    template <typename T>
    Geo_Vector<T>& Geo_Vector<T>::operator=(Geo_Vector && other_vector) noexcept
    {
        if (this == &other_vector) return *this;
        geo_v_ = std::move(other_vector.geo_v_);
        return *this;
    }


//-------------------------------------------------------------------------------------------------------------------------
    template <typename T>
    Geo_Vector<T>& Geo_Vector<T>::operator-=(const Geo_Vector& other_vector )
    {
        *this += -other_vector;
        return *this;
    }

    template <typename T>
    Geo_Vector<T> Geo_Vector<T>::operator-(const Geo_Vector& other_vector ) const
    {
        Geo_Vector<T> res_op{geo_v_};
        res_op -= other_vector;
        return res_op;
    }


    template <typename T>
    Geo_Vector<T> Geo_Vector<T>::operator+(const Geo_Vector& other_vector) const
    {

        Geo_Vector<T> res_op{geo_v_};
        res_op += other_vector;
        return res_op;
    }
    template <typename T>
    Geo_Vector<T>& Geo_Vector<T>::operator+=(const Geo_Vector& other_vector)
    {

        for (size_t i =0, size_n = geo_v_.size(); i < size_n; ++i)
            geo_v_[i] += other_vector.geo_v_[i];
        return *this;
    }
    template <typename T>
    Geo_Vector<T> Geo_Vector<T>::operator-() const
    {
        Geo_Vector<T> res_op{geo_v_};
        for (size_t i =0, size_n = geo_v_.size(); i < size_n; ++i)
            res_op.geo_v_[i] *= -1;
        return res_op;
    }


    template<typename T>
    Geo_Vector<T> Geo_Vector<T>::operator*(const T& a) const
    {
        Geo_Vector<T> res_op{geo_v_};
        for (size_t i =0, size_n = geo_v_.size(); i < size_n; ++i)
            res_op.geo_v_[i] *= a;
        return res_op;
    }

    template <typename T>
    inline Geo_Vector<T> operator*(const T& a, const Geo_Vector<T>& v) { return v * a; }


    template <typename T>
    T dot(const Geo_Vector<T>& a, const Geo_Vector<T>& b)
    {
        if (a.size() != b.size())
            throw std::runtime_error("dot: different sizes");

        T sum{};
        for (size_t i = 0; i < a.size(); ++i)
            sum += a[i] * b[i];
        return sum;
    }
}
