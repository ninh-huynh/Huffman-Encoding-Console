#pragma once
template<class T>
struct QueueNode
{
	T data;
	QueueNode<T> *next;
};

template<class T>
class QUEUE
{
private:
	QueueNode<T> *front;
	QueueNode<T> *rear;
public:
	QUEUE();
	QUEUE(const QUEUE<T> &aQueue);
	~QUEUE();
	bool isEmpty();
	bool enqueue(T item);
	bool dequeue(T &item);
};

template<class T>
QUEUE<T>::QUEUE()
{
	front = rear = nullptr;
}

template<class T>
QUEUE<T>::QUEUE(const QUEUE<T> &aQueue)
{
	if (!front)
	{
		delete front;
		front = nullptr;
	}
	if (!rear)
	{
		delete rear;
		rear = nullptr;
	}
	T tmp;
	while (!aQueue.isEmpty())
	{
		aQueue.dequeue(tmp);
		this->enqueue(tmp);
	}
}

template<class T>
QUEUE<T>::~QUEUE()
{
	T tmp;
	while (dequeue(tmp) == true);
	front = rear = nullptr;
}

template<class T>
bool QUEUE<T>::isEmpty()
{
	if (front == nullptr)
		return true;
	return false;
}

template<class T>
bool QUEUE<T>::enqueue(T item)
{
	QueueNode<T> *newNode = new QueueNode<T>;
	if (newNode == nullptr)
		return false;
	newNode->data = item;
	newNode->next = nullptr;

	if (this->isEmpty())
	{
		front = rear = newNode;
		return true;
	}
	rear->next = newNode;
	rear = newNode;
	return true;
}

template<class T>
bool QUEUE<T>::dequeue(T & item)
{
	if (this->isEmpty())
		return false;
	
	item = front->data;
	if (front == rear)
	{
		delete front;
		front = rear = nullptr;
		return true;
	}
	QueueNode<T> *hold = front;
	front = front->next;
	delete hold;
	return true;
}
