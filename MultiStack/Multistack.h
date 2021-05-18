#ifndef _Multistack_
#define _Multistack_

#include <iostream>
#include <fstream>
#include <math.h>
#include "Stack.h"

using namespace std;

template <class T>
class TMultiStack
{
protected:
	int length;
	T* x;
	int sCount;
	TStack<T>* stacks;
	T** pData;
	void RelocateStacks(int i);
public:

	TMultiStack(int size = 1, int stackCount = 1);
	TMultiStack(TMultiStack<T>& _v);
	~TMultiStack();

	TMultiStack<T>& operator =(const TMultiStack<T>& _v);
	bool operator==(const TMultiStack<T>& _v) const;

	void Push(T d, int i);
	T Get(int i);

	bool isFull(int i) const;
	bool isEmpty(int i) const;

	template <class T1>
	friend ostream& operator<< (ostream& ostr, const TMultiStack<T1>& A);
	template <class T1>
	friend istream& operator >> (istream& istr, TMultiStack<T1>& A);

	template <class T1>
	friend ofstream& operator<< (ofstream& ostr, const TMultiStack<T1>& A);
	template <class T1>
	friend ifstream& operator >> (ifstream& istr, TMultiStack<T1>& A);

	int Length() const;
	void Resize(int size = 1, int stackCount = 1);

	T FindMin() const;
	T FindMax() const;
};

template <class T1>
ostream& operator<< (ostream& ostr, const TMultiStack<T1>& A) {
	for (int i = 0; i < A.sCount; i++) {
		ostr << A.stacks[i] << endl;
	}
	return ostr;
}

template <class T1>
istream& operator >> (istream& istr, TMultiStack<T1>& A) {
	int count = 0, size = 0;
	istr >> count;
	if (count != A.sCount) {
		A.Resize(size, count); //////////////////////////////
		A.sCount = count;
		delete[] A.stacks;
		A.stacks = new TStack<T1>[count];
	}
	for (int i = 0; i < count; i++) {
		istr >> A.stacks[i];
	}
	return istr;
}

template<class T1>
ofstream& operator<<(ofstream& ostr, const TMultiStack<T1>& A)
{
	ostr << A.length << ' ' << A.ind << endl;
	for (int i = 0; i < A.ind; i++)
		ostr << A.x[i] << endl;
	return ostr;
}

template<class T1>
ifstream& operator>>(ifstream& istr, TMultiStack<T1>& A)
{
	int count;
	istr >> A.length >> count;
	A.inReq = true;
	A.x = new T1[A.length];
	for (int i = 0; i < count; i++) {
		T1 d;
		istr >> d;
		A.Push(d);
	}
	return istr;
}

template<class T>
void TMultiStack<T>::RelocateStacks(int index)
{
	int FreeSize = 0;
	for (int i = 0; i < this->sCount; i++) 
	{
		FreeSize += (this->stacks[i].GetSize() - this->stacks[i].Length());
	}
	if (FreeSize == 0)
		throw - 2;
	int count = int(floor(double(FreeSize) / this->sCount));
	int* sizes = new int[this->sCount];
	for (int i = 0; i < this->sCount; i++) 
	{
		sizes[i] = this->stacks[i].Length() + count;
	}
	sizes[index] += (FreeSize - (count * this->sCount));
	T** newData = new T * [this->sCount];
	int k = 0;
	for (int i = 0; i < this->sCount; i++) 
	{
		newData[i] = &(this->x[k]);
		k += sizes[i];
	}
	for (int i = 0; i < this->sCount; i++) 
	{
		if (newData[i] == this->pData[i])
			this->stacks[i].SetData(newData[i], sizes[i], this->stacks[i].Length());
		else if (newData[i] < this->pData[i]) 
		{
			for (int j = 0; j < this->stacks[i].Length(); j++) 
			{
				newData[i][j] = this->pData[i][j];
			}
			this->stacks[i].SetData(newData[i], sizes[i], this->stacks[i].Length());
		}
		else if (newData[i] > this->pData[i]) 
		{
			int k = i;
			while (newData[k] > this->pData[k])
				k++;
			k--;
			for (int s = k; s >= i; s--) 
			{
				for (int j = this->stacks[k].Length()-1; j >= 0 ; j--) 
				{
					newData[s][j] = this->pData[s][j];
				}
				this->stacks[s].SetData(newData[s], sizes[s], this->stacks[s].Length());
			}
			i = k + 1;
		}
	}
	T** buf = this->pData;
	this->pData = newData;
	delete[] buf;
	delete[] sizes;
}

template<class T>
TMultiStack<T>::TMultiStack(int size, int stackCount)
{
	if ((size <= 0) || (stackCount <= 0)) throw - 1;
	this->length = size;
	this->sCount = stackCount;
	this->x = new T[size];

	for (int i = 0; i < this->length; i = i + 1)
		this->x[i] = 0;

	int count = int(round(double(size) / stackCount));
	int* sizes = new int[stackCount];
	for (int i = 0; i < stackCount-1;i++) {
		sizes[i] = count;
	}
	sizes[stackCount - 1] = size - count * (stackCount - 1);
	this->pData = new T * [stackCount];
	int k = 0;
	this->stacks = new TStack<T>[stackCount];
	for (int i = 0; i < stackCount; i++) {
		this->stacks[i].SetData(&(this->x[k]), sizes[i], 0);
		this->pData[i] = &(this->x[k]);
		k += sizes[i];
	}
}

template <class T>
TMultiStack<T>::TMultiStack(TMultiStack<T>& _v)
{
	this->length = _v.length;
	this->x = new T[this->length];
	this->sCount = _v.sCount;
	for (int i = 0; i < this->length; i = i + 1)
		this->x[i] = _v.x[i];
	this->stacks = new TStack<T>[_v.sCount];
	for (int i = 0; i < this->length; i = i + 1)
		this->stacks[i] = _v.stacks[i];
	this->pData = new T * [_v.sCount];
	int k = 0;
	for (int i = 0; i < this->length; i = i + 1) {
		this->pData[i] = &(this->x[k]);
		k += this->stacks[i].GetSize();
	}
}

template <class T>
TMultiStack<T>::~TMultiStack()
{
	this->length = 0;
	this->sCount = 0;
	if (this->x != 0) {
		delete[] this->x;
		delete[] this->stacks;
	}
	else throw - 1;
	this->x = 0;
	this->stacks = 0;
}

template<class T>
TMultiStack<T>& TMultiStack<T>::operator=(const TMultiStack<T>& _v)
{
	if (this == &_v)
		return *this;
	this->length = _v.length;
	this->sCount = _v.sCount;
	delete[] this->x;
	delete[] this->stacks;
	this->stacks = new TStack<T>[this->sCount];
	this->x = new T[this->length];
	for (int i = 0; i < this->length; i++)
		this->x[i] = _v.x[i];
	for (int i = 0; i < this->sCount; i++)
		this->stacks[i] = _v.stacks[i];
	return *this;
}

template<class T>
inline bool TMultiStack<T>::operator==(const TMultiStack<T>& _v) const
{
	if (this->length != _v.length || this->ind != _v.ind) return false;
	for (int i = 0; i < ind; i++)
		if (this->x[i] != _v.x[i])
			return false;
	return true;
}


template<class T>
inline void TMultiStack<T>::Push(T d, int i)
{
	if (i < 0 || i >= this->sCount)
		throw - 1;
	if (this->stacks[i].isFull())
		this->RelocateStacks(i);
	this->stacks[i].Push(d);
}

template<class T>
inline T TMultiStack<T>::Get(int i)
{
	if (i < 0 || i >= this->sCount)
		throw - 1;
	if (this->stacks[i].isEmpty())
		throw - 1;
	T d = this->stacks[i].Get();
	return d;
}

template<class T>
inline bool TMultiStack<T>::isFull(int i) const
{
	if (i < 0 || i >= this->sCount)
		throw - 1;
	return (this->stacks[i].isFull());
}

template<class T>
inline bool TMultiStack<T>::isEmpty(int i) const
{
	if (i < 0 || i >= this->sCount)
		throw - 1;
	return (this->stacks[i].isEmpty());
}

template <class T>
int TMultiStack<T>::Length() const
{
	return length;
}

template<class T>
void TMultiStack<T>::Resize(int size, int stackCount)
{
	if ((size <= 0) || (stackCount <= 0)) throw - 1;
	delete[] this->stacks;
	delete[] this->x;
	this->length = size;
	this->sCount = stackCount;
	this->x = new T[size];

	for (int i = 0; i < this->length; i = i + 1)
		this->x[i] = 0;

	int count = int(round(double(size) / stackCount));
	int* sizes = new int[stackCount];
	for (int i = 0; i < stackCount - 1; i++) {
		sizes[i] = count;
	}
	sizes[stackCount - 1] = size - count * (stackCount - 1);
	this->pData = new T * [stackCount];
	int k = 0;
	this->stacks = new TStack<T>[stackCount];
	for (int i = 0; i < stackCount; i++) {
		this->stacks[i].SetData(&(this->x[k]), sizes[i], 0);
		this->pData[i] = &(this->x[k]);
		k += sizes[i];
	}

}

template<class T>
inline T TMultiStack<T>::FindMin() const
{
	if (this->isEmpty()) throw - 1;
	T min = this->x[0];
	for (int i = 1; i < ind; i++)
		if (this->x[i] < min)
			min = this->x[i];
	return min;
}

template<class T>
inline T TMultiStack<T>::FindMax() const
{
	if (this->isEmpty()) throw - 1;
	T max = this->x[0];
	for (int i = 1; i < ind; i++)
		if (this->x[i] > max)
			max = this->x[i];
	return max;
}


#endif