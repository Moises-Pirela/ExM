#pragma once
#include "ExM/ExMCore/Core/IPostProcessEvent.h"

template <typename T>
class Pool {
	
private:
	TArray<T*> pool;
	int size;

public:
	Pool(int32 InitialSize) : size(InitialSize)
	{
		for (int32 i = 0; i < size; ++i)
		{
			pool.Add(new T());
		}
	}

	~Pool()
	{
		for (T* Event : pool)
		{
			delete Event;
		}
		
		pool.Empty();
	}

	T* Allocate()
	{
		if (pool.Num() > 0)
		{
			return pool.Pop();
		}
		else
		{
			return new T();
		}
	}

	void Deallocate(T* Event)
	{
		pool.Add(Event);
	}
};
