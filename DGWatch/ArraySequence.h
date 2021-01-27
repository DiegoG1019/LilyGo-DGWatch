#ifndef ARRAYSEQUENCE_H
#define ARRAYSEQUENCE_H

#include <LilyGoWatch.h>
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
	ArraySequence(int cells, bool construct = true, bool psmalloc = false, void (T::*initializer)() = nullptr) : Size(_HeapSize), CellSize(_objsize), Length(length), PS_Allocated(psallocated)
	{
		psallocated = psmalloc;
		Index = 0;
		length = cells;
		_objsize = sizeof(T);
		_HeapSize = _objsize * cells;

		if (!psmalloc) {
			if (construct) {
				innerarray = new T[cells];
			}
			else {
				innerarray = static_cast<T*>(operator new[](_HeapSize));
			}
		}
		else {
			innerarray = static_cast<T*>(ps_malloc(sizeof<T>));
			if (construct) {
				for (int i = 0; i < Length; i++) {
					new (&(innerarray[i])) T();
				}
			}
		}
		if (initializer) {
			for (int i = 0; i < Length; i++) {
				(*innerarray.*initializer)();
			}
		}
		else if(!construct){
			memset(innerarray, 0, _HeapSize);
		}
	};
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
	T* GetPointer(int index) {
		if (index < 0 || index > Length)
			Log::Error(ex_INDEX_OUT_OF_BOUNDS, "ArraySequence.h", 54);
		return &innerarray[index];
	}
	T* operator [](int index) {
		if (index < 0 || index > Length)
			Log::Error(ex_INDEX_OUT_OF_BOUNDS, "ArraySequence.h", 64);
		return &innerarray[index];
	};
};

#endif