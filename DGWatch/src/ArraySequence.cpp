#include "ArraySequence.h"

template <class T>
ArraySequence<T>::ArraySequence(int cells, bool construct = true, bool psmalloc = false, void (T::*initializer)() = nullptr) : Size(_HeapSize), CellSize(_objsize), Length(length), PS_Allocated(psallocated)
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
    int st = sizeof(T);
		innerarray = static_cast<T*>(ps_malloc(st));
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
}

template <class T>
T* ArraySequence<T>::operator [](int index) {
	if (index < 0 || index > Length)
		Log::Error(ex_INDEX_OUT_OF_BOUNDS, __FILE__, __LINE__);
	return &innerarray[index];
}

template <class T>
T* ArraySequence<T>::GetPointer(int index){
    if (index < 0 || index > Length)
        Log::Error(ex_INDEX_OUT_OF_BOUNDS, __FILE__, __LINE__);
    return &innerarray[index];
}
