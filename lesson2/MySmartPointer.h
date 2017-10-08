#pragma once

template <class T>
class MySmartPointer{
	T* ptr;
	int* linkCount;

	void decLinkCount(void) {
		if (--(*linkCount) == 0) {
			delete ptr;
			delete linkCount;
		}
	}
public:
	MySmartPointer(T* pointer)
		: ptr(pointer), linkCount(new int(1))
	{};

	MySmartPointer(const MySmartPointer &pointer) {
		ptr = pointer.ptr;;
		linkCount = pointer.linkCount;
		++(*linkCount);
		std::cout << "copy-constructor POINTER " << *linkCount << "\n";
	}

	~MySmartPointer() {		
		std::cout << "destructor POINTER " << (*linkCount) - 1 << "\n";
		decLinkCount();
	};

	T&  operator*(void) {
		return (*ptr);
	}
	T* operator->(void) {
		return ptr;
	}

	// POST
	MySmartPointer& operator++(int) {
		ptr++;
		return *this;
	}; 
	MySmartPointer& operator--(int) {
		ptr--;
		return *this;
	};

	// PRE
	MySmartPointer& operator++() {
		++ptr;
		return *this;
	};
	MySmartPointer& operator--() {
		--ptr;
		return *this;
	};
	
	// BIN 
	MySmartPointer& operator+(const int offset) {
		ptr += offset;
		return *this;
	}
	MySmartPointer& operator-(const int offset) {
		ptr -= offset;
		return *this;
	}

	MySmartPointer& operator=(const MySmartPointer &pointer) {
		if (this != pointer) {
			decLinkCount();
			ptr = **pointer;
			++(*linkCount);
		}

		std::cout << "COPY\n";
		return *this;
	}

	T& operator[](int index) {
		return ptr[index];
	}
};

