

#pragma once
#include <stddef.h>
#include <stdint.h>

namespace PaulOS
{
    template<typename Container, ptrdiff_t step>
    struct linear_iterator
    {
        using value_type = typename Container::value_type;
        using difference_type = typename Container::difference_type;
        linear_iterator(value_type* val): _pos(val){};



    private:
        value_type* _pos;
    };

    template<typename T, size_t N>
    struct array
    {
        using value_type = T;
        using size_type = size_t;
        using difference_type = ptrdiff_t;
        using reference = value_type&;
        using const_reference = value_type const&;
        using pointer = T*;
        using const_pointer = T const*;
        using iterator = pointer;
        using const_iterator = const_pointer;
        using reverse_iterator = iterator;
        using const_reverse_iterator = const_iterator;

        constexpr size_type size() const{return N;}
        T* data() {return _storage;}
        T const* data() const {return _storage;}

        reference at(size_type i){return _storage[i];}
        const_reference at(size_type i) const {return _storage[i];}

        reference front() {return _storage[0];}
        const_reference front() const {return _storage[0];}

        reference back() {return _storage[N-1];}
        const_reference back() const {return _storage[N-1];}

        reference operator[](size_t i) {return _storage[i];}
        const_reference operator[](size_t i) const {return _storage[i];}

        iterator begin() {return _storage;}
        const_iterator begin() const {return _storage;}
        const_iterator cbegin() const {return _storage;}

        iterator end() {return _storage + N;}
        const_iterator end() const {return _storage + N;}
        const_iterator cend() const {return _storage + N;}

        iterator rbegin() {return _storage;}

        bool empty() const {return false;}






    private:

        T _storage[N];

    };

}
