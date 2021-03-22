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
	//T front();
	//T pop();
	//T back();
	//bool empty();
	//size_t size();
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
