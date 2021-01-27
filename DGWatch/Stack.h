#ifndef DGSTACK_H
#define DGSTACK_H
#include "Log.h"

template <class T>
class Stack
{
private:
	const char* FileName = "Stack.h";
	T** innerarray;
	int _Count;
	int _Capacity;
	const char* _Name;
public:
	const int& Count;
	const int& Capacity;
	const char*& Name;
	bool IsFull() { return Count == Capacity; }
	bool IsEmpty() { return Count == 0; }
	Stack(const Stack<T>&) = delete;
	Stack(const char* name, int capacity) : Count(_Count), Capacity(_Capacity), Name(_Name)
	{
		innerarray = new T * [capacity];
		_Count = 0;
		_Capacity = capacity;
		_Name = name;
	};
	inline bool Push(T* item) {
		if (IsFull()) {
			char* str = nullptr;
			Log::MakeMessage(str, "Stack full, unable to push item ", Name);
			Log::Warning(str, FileName, 30);
			return false;
		}
		innerarray[Count] = item;
		_Count++;
		return true;
	};

	bool Clear() {
		char* str = nullptr;
		Log::MakeMessage(str, "Clearing stack: ", Name);
		Log::Verbose(str, FileName, 45);
		delete[] innerarray;
		innerarray = new T * [Capacity];
	};
	inline T* Pop() {
		if (IsEmpty()) {
			char* str = nullptr;
			Log::MakeMessage(str, "Stack empty. Unable to pop from ", Name);
			Log::Warning(str, FileName, 57);
			return NULL;
		}
		_Count--;
		T* var = innerarray[Count];
		innerarray[Count] = NULL;
		return var;
	};
	/// <summary>
	/// pntr will have a pointer to the popped item, or if the function fails, will be left untouched.
	/// </summary>
	/// <param name="pntr"></param>
	/// <returns></returns>
	bool TryPop(T* pntr) {
		if (IsEmpty())
			return false;
		pntr = Pop();
		return true;
	};

	T* Peek() {
		if (IsEmpty())
			return NULL;
		return innerarray[Count - 1];
	}

	bool TryPeek(T* pntr) {
		if (IsEmpty())
			return false;
		pntr = Peek();
		return true;
	}
};

#endif