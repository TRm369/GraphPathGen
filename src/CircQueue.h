#pragma once

/*
Crude queue based on a circular buffer
It's missing some important checks (eg size > 0 on pop),
but the external code should guarantee those won't happen.
And the whole purpose of this was to make it FAST,
so I'm omiting redundant checks
*/
template <typename T>
class CircQueue {
public:
	CircQueue(int Length);
	void push(T val);
	T pop();
	int size();

protected:
	int length;
	T* circ;
	T* circ_last;
	T* front_ptr;
	T* back_ptr;
 };

template<typename T>
inline CircQueue<T>::CircQueue(int Length) {
	length = Length;
	circ = new T[length];
	circ_last = circ + length-1;
	front_ptr = circ;
	back_ptr = circ-1;
}

template<typename T>
inline void CircQueue<T>::push(T val) {
	if (++back_ptr > circ_last)
		back_ptr = circ;

	*back_ptr = val;
}

template<typename T>
inline T CircQueue<T>::pop() {
	if (front_ptr > circ_last)
		front_ptr = circ;

	return *(front_ptr++);
}

template<typename T>
inline int CircQueue<T>::size() {
	int size = back_ptr - front_ptr + 1;
	return size < 0 ? size+length : size;
}
