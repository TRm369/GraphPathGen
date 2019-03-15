#pragma once
#include <cstring> //memcpy

/*
Crude FILOcontainer
It's missing some important checks (eg size > 0 on pop),
but the external code should guarantee those won't happen.
And the whole purpose of this was to make it FAST,
so I'm omiting "redundant" checks

Malloc and free are used because I DON'T want constructors to be called.
It takes (a lot of) time and isn't required since the elements will overwritten
by already initialized data.
*/

template <typename T>
class FILOcontainer {
public:
	FILOcontainer(int Length);
	~FILOcontainer();

	void push_back(T obj);
	void pop_back();
	T back();
	int size();
	void copyFrom(FILOcontainer<T>& other);

	T operator [](int i);

private:
	FILOcontainer(T* Arr, T* Current, int Length);
	int length;
	T* arr;
	T* current;
};

template<typename T>
inline FILOcontainer<T>::FILOcontainer(int Length) {
	length = Length;
	arr = (T*)malloc(length * sizeof(T));
	current = arr - 1;
}

template<typename T>
inline FILOcontainer<T>::~FILOcontainer() {
	free(arr);
}

template<typename T>
inline void FILOcontainer<T>::push_back(T obj) {
	*(++current) = obj;
}

template<typename T>
inline void FILOcontainer<T>::pop_back() {
	current--;
}

template<typename T>
inline T FILOcontainer<T>::back() {
	return *current;
}

template<typename T>
inline int FILOcontainer<T>::size() {
	return current - arr + 1;
}

template<typename T>
inline void FILOcontainer<T>::copyFrom(FILOcontainer<T>& other) {
	free(arr);

	length = other.length;
	arr = (T*)malloc(length * sizeof(T));
	memcpy(arr, other.arr, other.size() * sizeof(T));
	current = arr + (other.current - other.arr);
}

template<typename T>
inline T FILOcontainer<T>::operator[](int i) {
	return arr[i];
}
