#pragma once

#include <iostream>
#include <algorithm>

template <typename T>
class vector {
public:
    vector() = default;
    explicit vector(size_t size);
    vector(const vector& another);
    ~vector();

    T& operator[](size_t index);

    T* begin(void);
    T* end(void);

    size_t size(void) const;
    size_t capacity(void) const;

    void push_back(const T& value);

    void resize(size_t new_size);
    void resize(size_t new_size, T value);

    void reserve(size_t to_reserve);

    void pop_back(void);

    void clear(void);

    T& front(void);
    T& back(void);
private:
    T* data = nullptr;
    size_t sz = 0;
    size_t cp = 0;

    void expand_check(void);
};

template <typename T>
inline vector<T>::vector(size_t nsize) {
    sz = nsize;
    cp = nsize;
    //data = new T[nsize];
    malloc(sizeof(T));
}

template <typename T>
inline vector<T>::vector(const vector& another) {
    //memcpy(this, &another, sizeof(another));
    data = another.data;
    sz = another.sz;
    cp = another.cp;
}

template <typename T>
inline vector<T>::~vector() {
    delete[] data;
}

template <typename T>
inline T& vector<T>::operator[](size_t index) {
    return data[index];
}

template <typename T>
inline size_t vector<T>::size(void) const {
    return sz;
}

template <typename T>
inline size_t vector<T>::capacity(void) const {
    return cp;
}

template <typename T>
inline void vector<T>::push_back(const T& value) {
    if (sz >= cp) {
        cp = (cp == 0) ? 1 : (2 * cp);
        T* new_data = new T[cp];
        for (int i = 0; i < sz; i++) new_data[i] = data[i];
        delete[] data;
        data = new_data;
    }
    data[sz++] = value;
}

template <typename T>
inline void vector<T>::expand_check(void) {
    if (sz >= cp) {
        auto new_cap = cp == 0 ? 1 : 2 * cp;
        //auto new_data = new T[new_cap];
        //std::move(begin(), end(), new_data);
        data = (T*)realloc((void*)data, new_cap * sizeof(T));
        //delete[] data;
        //data = new_data;
        cp = new_cap;
    }
}

template <typename T>
inline T* vector<T>::begin(void) {
    return data;
}

template <typename T>
inline T* vector<T>::end(void) {
    return data + sz;
}


template <typename T>
inline void vector<T>::clear(void) {
    sz = 0;
}


template <typename T>
inline void vector<T>::resize(size_t to_resize) {
    data = (T*)realloc(data, to_resize * sizeof(T));
    if (cp < to_resize) {
        data = (T*)realloc(data, to_resize * sizeof(T));
        cp = to_resize;
    }
    sz = to_resize;
}

template <typename T>
inline void vector<T>::resize(size_t to_resize, T value) {
    if (cp < to_resize) {
        data = (T*)realloc(data, to_resize * sizeof(T));
        cp = to_resize;
    }
    if (sz < to_resize) {
        for (size_t i = sz; i < to_resize; i++) data[i] = value;
    }
    sz = to_resize;
}

template <typename T>
inline void vector<T>::reserve(size_t to_reserve) {
    if (cp < to_reserve) {
        data = (T*)realloc(data, to_reserve * sizeof(T));
        cp = to_reserve;
    }
}

template <typename T>
inline void vector<T>::pop_back(void) {
    sz--;
}

template <typename T>
inline T& vector<T>::front() {
    return &data[0];
}

template <typename T>
inline T& vector<T>::back() {
    return &data[sz - 1];
}

template <typename T>
inline std::istream& operator<< (std::ostream& stream, vector<T> items) {
    for (T& item : items) {
        stream << item << ' ';
    }
}
