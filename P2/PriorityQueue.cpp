#pragma once
template<class T>
class PRIORITY_QUEUE
{
private:
	T *items;
	int rear;
	int maxSize;
	
	void swap(T &a, T &b);
	void topDown(int i);
	void bottomUp(int i);
public:
	PRIORITY_QUEUE();
	PRIORITY_QUEUE(int size);

	PRIORITY_QUEUE(const PRIORITY_QUEUE &aQueue);
	~PRIORITY_QUEUE();

	bool isEmpty();
	bool insert(T newItem);
	bool deleteMin(T &item);
	bool minValue(T &item);
};



template<class T>
void PRIORITY_QUEUE<T>::swap(T & a, T & b)
{
	T tmp = a;
	a = b;
	b = tmp;
}

template<class T>
inline void PRIORITY_QUEUE<T>::topDown(int i)
{
	T hold = items[i];
	while (i < (rear + 1) / 2)
	{
		int child = 2 * i + 1;
		if (child < rear)
			if (items[child] > items[child + 1]) child++;
		if (hold < items[child])
			break;
		items[i] = items[child];
		i = child;
	}
	items[i] = hold;
}

template<class T>
void PRIORITY_QUEUE<T>::bottomUp(int i)
{
	T hold = items[i];
	while (i > 0)
	{
		int parent = (i - 2 + i % 2) / (rear + 1);
		if (hold > items[parent])
			break;
		items[i] = items[parent];
		i = parent;
	}
	items[i] = hold;
}

template<class T>
PRIORITY_QUEUE<T>::PRIORITY_QUEUE()
{
	maxSize = 20;
	rear = -1;
	items = new T[maxSize];
}

template<class T>
inline PRIORITY_QUEUE<T>::PRIORITY_QUEUE(int size)
{
	if (size > 0)
		maxSize = size;
	items = new T[maxSize];
	rear = -1;
}

template<class T>
inline PRIORITY_QUEUE<T>::PRIORITY_QUEUE(const PRIORITY_QUEUE & aQueue)
{
	if (items != nullptr)
		delete []items;

	if (aQueue.isEmpty())
	{
		items = nullptr;
		return;
	}

	items = new T[aQueue.rear + 1];

	for (int i = 0; i < aQueue.rear; i++)
		items[i] = aQueue[i];
}

template<class T>
inline PRIORITY_QUEUE<T>::~PRIORITY_QUEUE()
{
	delete []items;
	items = nullptr;
	rear = -1;
	maxSize = 20;
}

template<class T>
inline bool PRIORITY_QUEUE<T>::isEmpty()
{
	if (rear == -1)
		return true;
	return false;
}

template<class T>
inline bool PRIORITY_QUEUE<T>::insert(T newItem)
{
	if (rear + 2 > maxSize)
	{
		T *newArr = new T[2 * maxSize];
		if (newArr == nullptr)
			return false;
		for (int i = 0; i < rear; i++)
			newArr[i] = items[i];
		delete []items;
		items = newArr;
	}

	rear++;
	items[rear] = newItem;
	bottomUp(rear);
	return true;
}

template<class T>
inline bool PRIORITY_QUEUE<T>::deleteMin(T & item)
{
	if (rear == -1)
		return false;
	item = items[0];
	items[0] = items[rear];
	rear--;
	topDown(0);
	return true;
}

template<class T>
inline bool PRIORITY_QUEUE<T>::minValue(T & item)
{
	if (rear == 0)
		return false;
	T = items[0];
	return true;
}
