#include<iostream>
#include<utility>
using namespace std;
template<typename T>
class Vector {
	T* data_;
	size_t size_;
	size_t capacity_;
public:
	//Constructor
	Vector() :data_(nullptr), size_(0), capacity_(0) {}
	//Destructor
	~Vector()
	{
		delete[] data_;
	}
	//size_ info functions
	size_t size() const {
		return size_;
	}
	size_t capacity() const { //should not change the vector object
		return capacity_;
	}
	bool empty() {
		return size_ == 0;
	}

	//Index operator returning a reference allows direct access to stored elem v[0]=100 we return refrence to v[0]  
	//int x=10 int& r=x;  now r and x are the names of same memory r=20 , makes x=20;  data_[x]= int return int&
	T& operator[](size_t index) {
		return data_[index];    //v[0] is just another name for data_[0]
	}
	const T& operator[](size_t index) const
	{
		return data_[index];
	}
	//reserve Algo
	//allocate mem-->copy ele-->delete old mem-->update the pointer-->update capacity_
	void reserve(size_t newCapacity) {
		if (newCapacity <= capacity_) return;
		T* new_data_ = new T[newCapacity];
		for (size_t i = 0;i < size_;i++) {
			new_data_[i] = move(data_[i]);
		}
		delete[] data_;
		data_ = new_data_;
		capacity_ = newCapacity;
	}
	//resize_ algo
	void resize(size_t n) {
		if (n < size_) {
			size_ = n;
		}
		else if (n >= size_ && n <= capacity_) {
			for (size_t i = size_;i <n;i++) {
				data_[i] = T{};
			}
			size_ = n;
		}
		else  {
			reserve(n);
			for (size_t i = size_;i < n;i++) {
				data_[i] = T{};
			}
			size_ = n;
		}
		
	}
	void push_back(const T& other) {
		if (size_ == capacity_) {
			size_t new_capacity_ = (capacity_ == 0) ? 1 : 2 * capacity_;
			reserve(new_capacity_);


		}
		data_[size_++] = other;
	}
	void push_back(T&& other) {
		if (size_ == capacity_) {
			size_t new_capacity_ = (capacity_ == 0) ? 1 : 2 * capacity_;
			reserve(new_capacity_);
		}
		data_[size_++] = move(other);
	}

	void pop_back() {
		if (size_ == 0) return;
		size_--;
	}
	
};

