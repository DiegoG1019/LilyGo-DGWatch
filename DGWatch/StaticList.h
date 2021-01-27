#ifndef STATICLIST_H
#define STATICLIST_H

#include "Log.h"

template <class T, bool ReportError = true>
class StaticList
{
private:
	T** InnerArray;
	int _Length;
	int _Count;
	int _CurrentIndex;
	inline void init() {
		_Count = 0;
		_CurrentIndex = 0;
	};
public:
	const int& Length;
	const int& Count;
	StaticList(const StaticList&) = delete;
	StaticList(int length) : Count(_Count), Length(_Length) {
		init();
		InnerArray = new T* [length];
		_Length = Length;
	}
	~StaticList() {
		delete[]InnerArray;
	};
	inline bool IsEmpty() { return Count == 0; }
	inline bool IsFull() { return Count == Length; }
	inline T* operator [](int index) {
		if (index < 0 || index >= Length) {
			Log::Error("Unable to get item, out of bounds", "StaticList.h", 33);
			throw ex_INDEX_OUT_OF_BOUNDS;
			return nullptr;
		};
		return InnerArray[index];
	};
	inline void Set(int index, T* item) {
		if (index < 0 || index >= Length) {
			Log::Error("Unable to set item, out of bounds", "StaticList.h", 40);
			throw ex_INDEX_OUT_OF_BOUNDS;
			return;
		};
		InnerArray[index] = item;
	}
	bool TryGet(int index, T* item) {
		if (index < 0 || index >= Length || !InnerArray[index])
		{
			Log::Error("Unable to get item, out of bounds or index returns null", "StaticList.h", 49);
			throw ex_INDEX_OUT_OF_BOUNDS;
			return false;
		}
		item = InnerArray[index];
		return true;
	}
	/// <summary>
	/// Clears the list of items, but does not delete them.
	/// </summary>
	void Clear() {
		for (int i = 0; i < Length; i++) {
			InnerArray[i] = nullptr;
		}
	}
	/// <summary>
	/// Clears the list of items, deleting each item in the process.
	/// </summary>
	void ClearAndDelete() {
		for (int i = 0; i < Length; i++) {
			delete InnerArray[i];
			InnerArray[i] = nullptr;
		}
	}

	/// <summary>
	/// Adds item at the first empty spot it finds
	/// </summary>
	/// <param name="item"></param>
	void Add(T* item) {
		if (IsFull()) {
			if (ReportError) {
				Log::Error("Cannot add element, this is full.", "StaticList.h", 81);
			}
			return;
		}
		for (int i = 0; i < Length; i++) {
			if (InnerArray[i])
				continue;
			InnerArray[i] = item;
		}
	}

	void RemoveDelete(int index) {
		if (InnerArray[index])
		{
			delete InnerArray[index];
			InnerArray[index] = nullptr;
		}
	}

	void CopyTo(StaticList<T>* arr) {
		if (arr->Length < Length) {
			if (ReportError) {
				Log::Error("CopyTo function failed, 'arr' is of less size than 'this'", "StaticList.h", 103);
			}
			return;
		}
		for (int i = 0; i < Length; i++) {
			arr->InnerArray[i] = InnerArray[i];
		}
	}
	void CopyFrom(T** arr) {
		for (int i = 0; i < Length; i++) {
			InnerArray[i] = arr[i];
		}
	}
}; 
#endif //STATICLIST_H