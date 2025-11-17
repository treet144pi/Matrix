
#pragma once
#include <cstddef>

namespace My_vector
{
    template <typename T>
    class vector
    {
        private:
            T * v_arr_;
            size_t size_;
        public:
            vector(): size_(0),v_arr_(nullptr) {}
            vector(size_t s,T value) : size_(s), v_arr_(new T[size_]) { for (size_t i = 0; i < size_; ++i) v_arr_[i] = value;}

            vector(size_t s) : size_(s), v_arr_(new T[size_] {}) {}

            vector(const vector& other_vector);
            vector(vector&& other_vector) noexcept;
            ~vector();
            vector& operator=(const vector& other_vector);
            vector& operator=(vector&& other_vector) noexcept;


            T& operator[](size_t index) { return v_arr_[index]; } // accurately
            const T& operator[](size_t index) const { return v_arr_[index]; }
            size_t size() const { return size_; }
    };

    template <typename T>
    vector<T>::vector(const vector& other_vector) : size_(other_vector.size_), v_arr_(new T[size_] {})
    {
        for (size_t i = 0; i < size_; ++i)
            v_arr_[i] = other_vector.v_arr_[i];
    }

    template <typename T>
    vector<T>::vector(vector&& other_vector) noexcept: size_(other_vector.size_), v_arr_(other_vector.v_arr_)
    {
        other_vector.v_arr_ = nullptr;
        other_vector.size_ = 0;
    }

    template <typename T>
    vector<T>::~vector()
    {
        delete[] v_arr_;
    }

    template <typename T>
    vector<T>& vector<T>::operator=(const vector& other_vector)
    {
        if (this == &other_vector) return *this;
        delete[] v_arr_;
        size_ = other_vector.size_;
        v_arr_ = new T[size_] {};
        for (size_t i = 0; i < size_; ++i)
            v_arr_[i] = other_vector.v_arr_[i];
        return *this;
    }

    template <typename T>
    vector<T>& vector<T>::operator=(vector&& other_vector) noexcept
    {
        if (this == &other_vector) return *this;

        delete[] v_arr_;
        size_ = other_vector.size_;
        v_arr_ = other_vector.v_arr_;
        other_vector.v_arr_ = nullptr;
        other_vector.size_ = 0;
        return *this;
    }
}
