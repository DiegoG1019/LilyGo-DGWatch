#ifndef DGQUEUE_H
#define DGQUEUE_H

#include "Log.h"

template <class T>
class Queue
{
private:
	const char* FileName = "Queue.h";
	T **innerarray;
	int _Count;
	int _Capacity;
	const char* _Name;
	int Next;
	int NextEmpty;
public:
	const int& Count;
	const int& Capacity;
	const char*& Name;
	bool IsFull() { return Count == Capacity; }
	bool IsEmpty() { return Count == 0; }
	Queue(const Queue<T>&) = delete;
	Queue(const char* name, int capacity) : Count(_Count), Capacity(_Capacity), Name(_Name)
	{
		innerarray = new T*[capacity];
		_Count = 0;
		_Capacity = capacity;
		_Name = name;
		Next = 0;
		NextEmpty = 0;
	};
	bool Add(T* item) {
		if (IsFull()) {
			char* str = nullptr;
			Log::MakeMessage(str, "Queue full, unable to add item to queue ", Name);
			Log::Warning(str, FileName, 30);
			return false;
		}
		innerarray[Count] = item;
		_Count++;
		if (NextEmpty < Capacity) {
			NextEmpty++;
		}
		else {
			NextEmpty = 0;
		}
		return true;
	};
	/// <summary>
	/// This will clear the array only, items in it could cause a memory leak if not disposed correctly
	/// </summary>
	/// <returns></returns>
	bool Clear() {
		char* str = nullptr;
		Log::MakeMessage(str, "Clearing queue: ", Name);
		Log::Verbose(str, FileName, 55);
		delete[] innerarray;
		innerarray = new T*[Capacity];
	};
	T* Dequeue() {
		if (IsEmpty()) {
			char* str = nullptr;
			Log::MakeMessage(str, "Queue empty. Unable to dequeue from ", Name);
			Log::Warning(str, FileName, 63);
			return NULL;
		}
		_Count--;
		T* var = innerarray[Next];
		innerarray[Next] = NULL;
		if (Next < Capacity) {
			Next++;
		}
		else {
			Next = 0;
		}
		return var;
	};
	/// <summary>
	/// pntr will have a pntr of the dequeued item, or if the function fails, will be left untouched.
	/// </summary>
	/// <param name="pntr"></param>
	/// <returns></returns>
	bool TryDequeue(T* pntr) {
		if (IsEmpty())
			return false;
		pntr = Dequeue();
		return true;
	};

	T* Peek() {
		if (IsEmpty())
			return NULL;
		return innerarray[Next];
	}

	bool TryPeek(T* pntr) {
		if (IsEmpty())
			return false;
		pntr = Peek();
		return true;
	}
};
#endif 