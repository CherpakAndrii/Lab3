#pragma once

//ну тут вроде все и так понятно

//класс очередь
template <typename T> 
class Queue {
private: 
	T* data = nullptr;
	size_t used;
	size_t all;
public:
	Queue();
	~Queue();
	void push(T val);
	T pop();
	T front();
	T back();
	size_t size();
	//bool empty();
	//void swap(Queue& another);
};

//методы класса очередь

template <typename T>
inline Queue<T>::Queue() {
	data = new T[0];
	all = 0;
	used = 0;
}

template <typename T>
inline Queue<T>::~Queue() {
	delete[] data;
}

template <typename T>
inline void Queue<T>::push(T val) {
	data = (T*)realloc(data, ++all * sizeof(T));
	data[(all - used) - 1] = val;
}

template <typename T>
inline T Queue<T>::pop() {
	T val = data[used++];
	return val;
}

template <typename T>
inline T Queue<T>::front() {
	return data[used];
}

template <typename T>
inline T Queue<T>::back() {
	return data[all - 1];
}

template <typename T>
inline size_t Queue<T>::size() {
	return (all - used);
}

