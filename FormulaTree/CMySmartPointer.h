#pragma once
class CRefCounter;
class CRefCounter {
private:
	int i_count;
public:
	CRefCounter() { i_count = 0; }
	int iAdd() { return ++i_count; }
	int iDec() { return --i_count; }
	int iGet() { return i_count; }
};
template  <typename T> class CMySmartPointer {
private:
	T* pointer;
	CRefCounter* counter;
	void copy(const CMySmartPointer<T>& other);

public:
	CMySmartPointer(T* pointer);
	CMySmartPointer(const CMySmartPointer<T>& other);
	~CMySmartPointer();

	T& operator*() { return *pointer; }
	T* operator->() { return pointer; }
	void operator=(const CMySmartPointer<T>& other);

};

template <typename T>
void CMySmartPointer<T>::copy(const CMySmartPointer<T>& other) {
	pointer = other.pointer;
	counter = other.counter;
	counter->iAdd();
}

template<typename T>
CMySmartPointer<T>::CMySmartPointer(T* pointer) {
	pointer = pointer;
	counter = new CRefCounter();
	counter->iAdd();
}

template <typename T>
CMySmartPointer<T>::CMySmartPointer(const CMySmartPointer<T>& other) {
	copy(other);
}

template <typename T>
CMySmartPointer<T>::~CMySmartPointer() {
	if (counter->iDec() == 0) {
		delete pointer;
		delete counter;
	}
}

template <typename T>
void CMySmartPointer<T>::operator=(const CMySmartPointer<T>& other) {
	if (pointer != other.pointer) {
		if (counter->iDec() == 0) {
			delete pointer;
			delete counter;
		}
	}
	copy(other);
}
