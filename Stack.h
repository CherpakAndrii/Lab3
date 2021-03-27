#pragma once


template <typename T>
class Stack {
private:
	T* data = nullptr;
	size_t sz;
	size_t cap;
public:
	Stack();
	~Stack();
	void push(T val);
	T pop();
	T bottom();
	T top();
	size_t size();
	void swap(Stack<T>& another);
};

template <typename T>
inline Stack<T>::Stack() {
	data = new T[10];
	cap = 10;
	sz = 0;
}

template <typename T>
inline Stack<T>::~Stack() {
	delete[] data;
}

template <typename T>
inline void Stack<T>::push(T val) {
	if (sz == cap) { data = (T*)realloc(data, cap * 2 * sizeof(T)); cap *= 2; }
	sz++;
	data[sz - 1] = val;
}

template <typename T>
inline T Stack<T>::pop() {
	T val = data[--sz];
	return val;
}

template <typename T>
inline T Stack<T>::bottom() {
	return data[0];
}

template <typename T>
inline T Stack<T>::top() {
	return data[sz - 1];
}

template <typename T>
inline size_t Stack<T>::size() {
	return sz;
}

template <typename T>
inline void Stack<T>::swap(Stack<T>& another) {
	auto buffData = data;
	auto buffcap = cap;
	auto buffsz = sz;
	data = another.data;
	cap = another.cap;
	sz = another.sz;
	another.data = buffData;
	another.cap = buffcap;
	another.sz = buffsz;
}
