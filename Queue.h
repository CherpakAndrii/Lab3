#pragma once

//ну тут вроде все и так понятно

//класс очередь
template <typename T> 
class Queue {
private: 
	T* data = nullptr;
	size_t used;
	size_t all;
	size_t cp;
public:
	Queue();
	~Queue();
	void push(T val);
	T pop();
	T front();
	T back();
	size_t size();
	size_t capacity();
	bool empty();
	void swap(Queue<T>& another);
};

//методы класса очередь

template <typename T>
inline Queue<T>::Queue() {
	data = new T[1000];
	all = 0;
	used = 0;
	cp = 1000;
}

template <typename T>
inline Queue<T>::~Queue() {
	delete[] data;
}

template <typename T>
inline void Queue<T>::push(T val) {
	if (all >= cp) {
		new_cp = 2 * cp;
		data = (T*)realloc(data, new_cp * sizeof(T));
		cp = new_cp;
	}
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

template <typename T>
inline bool Queue<T>::empty() {
	return (all - used) == 0;
}

template <typename T>
inline size_t Queue<T>::capacity() {
	return cp;
}

template <typename T>
inline void Queue<T>::swap(Queue<T>& another) {
	auto buffData = data;
	auto buffAll = all;
	auto buffUsed = used;
	auto buffCp = cp;
	data = another.data;
	all = another.all;
	used = another.used;
	cp = another.cp;
	another.data = buffData;
	another.all = buffAll;
	another.used = buffUsed;
	another.cp = buffCp;
}
