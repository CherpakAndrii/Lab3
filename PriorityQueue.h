#pragma once

template <typename T>
class PriorityQueue {
private:
	T* data = nullptr;
	size_t sz;
	size_t cp;
	void insert();
public:
	PriorityQueue();
	PriorityQueue(size_t cap);
	~PriorityQueue();
	void push(T val);
	T pop();
	T top();
	bool empty();
	size_t size();
	size_t capacity();
	void swap(PriorityQueue<T>& another);
};

template <typename T>
inline PriorityQueue<T>::PriorityQueue() {
	data = new T[1000];
	cp = 1000;
	sz = 0;
}

template <typename T>
inline PriorityQueue<T>::PriorityQueue(size_t ncap) {
	data = new T[ncap];
	cp = ncap;
	sz = 0;
}


template <typename T>
inline PriorityQueue<T>::~PriorityQueue() {
	delete[] data;
}

template <typename T>
<<<<<<< HEAD
inline void PriorityQueue<T>::push(T val) { 
=======
inline void PriorityQueue<T>::push(T val) {
>>>>>>> a-star
	if (sz >= cp) {
		size_t new_cp = 2 * cp;
		data = (T*)realloc((void*)data, new_cp * sizeof(T));
	}
	data[sz++] = val;
	insert();
}

template <typename T>
inline T PriorityQueue<T>::pop() {
	T val = data[--sz];
	return val;
}

template <typename T>
inline T PriorityQueue<T>::top() {
	return data[sz - 1];
}

template <typename T>
inline bool PriorityQueue<T>::empty() {
	return (sz == 0);
}

template <typename T>
inline size_t PriorityQueue<T>::size() {
	return sz;
}

template <typename T>
inline size_t PriorityQueue<T>::capacity() {
	return cp;
}

template <typename T>
inline void PriorityQueue<T>::swap(PriorityQueue<T>& another) {
	auto buffData = data;
	auto buffSz = sz;
	auto buffCp = cp;
	data = another.data;
	sz = another.sz;
	cp = another.cp;
	another.data = buffData;
	another.sz = buffSz;
	another.cp = buffCp;
}

template <typename T>
inline void PriorityQueue<T>::insert() {
	size_t index = sz - 1;
	while (index > 0 and data[index - 1] > data[index]) {
		T buf = data[index];
		data[index] = data[index - 1];
		data[index - 1] = buf;
		index--;
	}
}

inline void PriorityQueue<std::pair<int, double>>::insert() {
	size_t index = sz - 1;
	while (index > 0 and data[index - 1].second < data[index].second) {
		std::pair<int, double> buf = data[index];
		data[index] = data[index - 1];
		data[index - 1] = buf;
		index--;
	}
}
