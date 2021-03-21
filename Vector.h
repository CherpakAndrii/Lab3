#pragma once

#include <algorithm>

template <typename T>
class vektor {
public:
    vektor() = default;
    explicit vektor(size_t size);
    vektor(const vektor& another);
    ~vektor();

    T& operator[](size_t index);

    size_t size(void) const;
    size_t capacity(void) const;

    void push_back(const T& value);

    void resize(size_t new_size);
    void resize(size_t new_size, T value);

    void clear(void);

private:
    T* data = nullptr;
    size_t sz = 0;
    size_t cp = 0;

    void expand_check(void);
};

template <typename T>
inline vektor<T>::vektor(size_t size) : data(new T[size]), sz(size), cp(size) {}

template <typename T>
inline vektor<T>::vektor(const vektor& another) {
    memcpy(this, &another, sizeof(another));
}

template <typename T>
inline vektor<T>::~vektor() {
    delete[] data;
}

template <typename T>
inline T& vektor<T>::operator[](size_t index) {
    return data[index];
}

template <typename T>
inline size_t vektor<T>::size(void) const {
    return sz;
}

template <typename T>
inline size_t vektor<T>::capacity(void) const {
    return cp;
}

template <typename T>
inline void vektor<T>::push_back(const T& value) {
    expand_check();
    data[sz++] = value;
}

template <typename T>
inline void vektor<T>::expand_check(void) {
    if (sz >= cp) {
        auto new_cap = cp == 0 ? 1 : 2 * cp;
        auto new_data = new T[new_cap];
        std::move(begin(), end(), new_data);
        delete[] data;
        data = new_data;
        cp = new_cap;
    }
}


template <typename T>
inline void vektor<T>::clear(void) {
    sz = 0;
}


template <typename T>
inline void vektor<T>::resize(size_t to_resize) {
    data = (T*)realloc(data, to_resize * sizeof(T));
    if (cp < to_resize) {
        data = (T*)realloc(data, to_resize * sizeof(T));
        cp = to_resize;
    }
    sz = to_resize;
}

template <typename T>
inline void vektor<T>::resize(size_t to_resize, T value) {
    if (cp < to_resize) {
        data = (T*)realloc(data, to_resize * sizeof(T));
        cp = to_resize;
    }
    if (sz < to_resize) {
        for (size_t i = sz; i < to_resize; i++) data[i] = value;
    }
    sz = to_resize;
}
