
#pragma once
#include <cstddef>
#include <stdexcept>
#include <utility>

namespace My_vector
{
    template <typename T>
    class vector
    {
        private:
            size_t size_;
            size_t capacity_;
            T *    v_arr_;
        public: //Rule of Five
            vector(): size_(0),capacity_(0),v_arr_(nullptr) {}
            vector(size_t s,T value) : size_(s),capacity_(s), v_arr_(new T[size_])
                    { for (size_t i = 0; i < size_; ++i) v_arr_[i] = value;}

            vector(size_t s) : size_(s),capacity_(s), v_arr_(new T[size_] {}) {}

            vector(const vector& other_vector);
            vector(vector&& other_vector) noexcept;
            ~vector();
            vector& operator=(const vector& other_vector);
            vector& operator=(vector&& other_vector) noexcept;

        public:  //Element access
            T& operator[](size_t index) { return v_arr_[index]; } // accurately
            const T& operator[](size_t index) const { return v_arr_[index]; }

            T& at(size_t index);
            const T& at(size_t index) const;

        public: //Capacity
            size_t size() const { return size_; }
            size_t capacity() const { return capacity_; }

        public: //Modifiers
            void        push_back(const T& elem);
            void        pop_back();

            T&          back();
            const T&    back() const;
    };
//----------------------------------------------------------------------------------------------------------------------------------------
//-------------------------Modifiers---------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------------------------


    template <typename T>
    void vector<T>::push_back(const T& elem)
    {
        if (capacity_ > size_)
        {
            v_arr_[size_] = elem;
            size_++;
            return;
        }

        capacity_ = capacity_ ? capacity_*2: 64;
        T * new_arr = new T[capacity_];
        for (size_t i = 0; i < size_; ++i)
            new_arr[i] = v_arr_[i];

        new_arr[size_] = elem;
        size_++;

        delete [] v_arr_;

        v_arr_  = new_arr;
        new_arr = nullptr;
    }

    template <typename T>
    T& vector<T>::back()
    {
        if (size_ == 0) throw std::out_of_range("My_vector::back()");
        return v_arr_[size_-1];
    }

    template <typename T>
    const T& vector<T>::back() const
    {
        if (size_ == 0) throw std::out_of_range("My_vector::back() const");
        return v_arr_[size_-1];
    }

    template <typename T>
    void vector<T>::pop_back()
    {
        if (size_ == 0) throw std::out_of_range("My_vector::pop_back()");
        size_--;
    }


//----------------------------------------------------------------------------------------------------------------------------------------
//-------------------------Rule of Five---------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------------------------

    template <typename T>
    vector<T>::vector(const vector& other_vector) : size_(other_vector.size_),capacity_(other_vector.capacity_),
                                                    v_arr_(new T[capacity_] {})
    {
        for (size_t i = 0; i < size_; ++i)
            v_arr_[i] = other_vector.v_arr_[i];
    }

    template <typename T>
    vector<T>::vector(vector&& other_vector) noexcept: size_(other_vector.size_),capacity_(other_vector.capacity_),
                                                       v_arr_(other_vector.v_arr_)
    {
        other_vector.v_arr_    = nullptr;
        other_vector.size_     = 0;
        other_vector.capacity_ = 0;
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
        vector<T> tmp{other_vector};

        std::swap(v_arr_   , tmp.v_arr_);
        std::swap(size_    , tmp.size_);
        std::swap(capacity_, tmp.capacity_);

        return *this;
    }

    template <typename T>
    vector<T>& vector<T>::operator=(vector&& other_vector) noexcept
    {
        if (this == &other_vector) return *this;
        delete[] v_arr_;
        size_     = other_vector.size_;
        v_arr_    = other_vector.v_arr_;
        capacity_ = other_vector.capacity_;

        other_vector.v_arr_    = nullptr;
        other_vector.size_     = 0;
        other_vector.capacity_ = 0;

        return *this;
    }
//----------------------------------------------------------------------------------------------------------------------------------------
//-------------------------Element access---------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------------------------

    template <typename T>
    T& vector<T>::at(size_t index)
    {
        if (index >= size_) throw std::out_of_range("My_vector::at()");
        return v_arr_[index];
    }

    template <typename T>
    const T& vector<T>::at(size_t index) const
    {
        if (index >= size_) throw std::out_of_range("My_vector::at()");
        return v_arr_[index];
    }
}
