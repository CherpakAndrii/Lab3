#pragma once

template <typename T>
class PriorityQueue {
private:
	T* data = nullptr;
	size_t sz;
	void insert();
public:
	PriorityQueue();
	~PriorityQueue();
	void push(T val);
	T pop();
	T top();
	bool empty();
	size_t size();
	void swap(PriorityQueue<T>& another);
};

template <typename T>
inline PriorityQueue<T>::PriorityQueue() {
	data = new T[0];
	sz = 0;
}

template <typename T>
inline PriorityQueue<T>::~PriorityQueue() {
	delete[] data;
}

template <typename T>
inline void PriorityQueue<T>::push(T val) {
	data = (T*)realloc((void*)data, ++sz * sizeof(T));
	data[sz - 1] = val;
	insert();
}

template <typename T>
inline T PriorityQueue<T>::pop() {
	T val = data[--sz];
	data = (T*)realloc((void*)data, sz * sizeof(T));
	return val;
}

template <typename T>
inline T PriorityQueue<T>::top() {
	return data[sz - 1];
}

template <typename T>
inline bool PriorityQueue<T>::empty() {
	return (sz > 0);
}

template <typename T>
inline size_t PriorityQueue<T>::size() {
	return sz;
}

template <typename T>
inline void PriorityQueue<T>::swap(PriorityQueue<T>& another) {
	auto buffData = data;
	auto buffSz = sz;
	data = another.data;
	sz = another.sz;
	another.data = buffData;
	another.sz = buffSz;
}

template <typename T>
inline void PriorityQueue<T>::insert() {
	size_t index = sz - 1;
	while (index >= 0 and data[index - 1] > data[index]) {
		T buf = data[index];
		data[index] = data[index - 1];
		data[index - 1] = buf;
		index--;
	}
}

inline void PriorityQueue<std::pair<int, int>>::insert() {
	size_t index = sz - 1;
	while (index >= 0 and data[index - 1].second < data[index].second) {
		std::pair<int, int> buf = data[index];
		data[index] = data[index - 1];
		data[index - 1] = buf;
		index--;
	}
}
