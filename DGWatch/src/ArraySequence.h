#ifndef ARRAYSEQUENCE_H
#define ARRAYSEQUENCE_H

#include "config/errors.h"

template <class T>
class ArraySequence
{
private:
	T* innerarray;
	size_t _HeapSize;
	size_t _objsize;
	int length;
	bool psallocated : 1;
public:
	const size_t& Size;
	const size_t& CellSize;
	const int& Length;
	const int& PS_Allocated;
	int Index;
	ArraySequence(const ArraySequence<T>&) = delete;
	ArraySequence(int cells, bool construct = true, bool psmalloc = false, void (T::*initializer)() = nullptr);
	~ArraySequence() {
		if (!psallocated) {
			delete[] innerarray;
		}
		else {
			free(innerarray);
		}
	};
	T* Next() {
		if (Index >= Length)
		{
			Index = 0;
		}
		Index++;
		return &innerarray[Index - 1];
	}
	T* Construct(int index) {
		return new (&innerarray[index]) T();
	}
	T* ZeroSet(int index) {
		memset(&innerarray[index], 0, _objsize);
	}
	T* MemSet(int index, int value) {
		memset(&innerarray[index], value, _objsize);
	}
	T* GetPointer(int index);
	T* operator [](int index);
};

#endif