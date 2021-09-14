#include <iostream>

using namespace std;

template<class T>
class Vector
{
private:
	T *nums_;
	int size_; // used size
	int maxsize_; // allocated size

	bool isSorted_;
	bool isAscending_;

	// checks if the data is sorted
	void checkNumber(unsigned int index);

	void resize(unsigned int size);

	int linearSearch(T key);
	int binarySearch(T key);
	int reverseBinarySearch(T key);

	int partition(unsigned int begin, unsigned int end);
	void quickSort(unsigned int begin, unsigned int end);

public:
	Vector(int size = 0);
	Vector(T *, int size = 0);
	Vector(const Vector &);
	~Vector(void);

	friend Vector operator+(T value, Vector &); // Add a value at the beginning
	Vector operator+(T value); // Add value at the end
	Vector operator-(T value);
	Vector &operator+=(T value);
	Vector &operator-=(T value);

	Vector operator+(Vector &);
	Vector operator-(Vector &);
	Vector &operator+=(Vector &);
	Vector &operator-=(Vector &);

	Vector &operator=(const Vector &);
	T &operator[](int);
	bool operator==(Vector &);
	bool operator!=(Vector &);

	template<class U>
	friend ostream &operator<<(ostream &, const Vector<U> &);
	template<class U>
	friend istream &operator>>(istream &, Vector<U> &); // input only one number

	void sort(void);
	void reverse(void);

	void insert(T value, int index); // Adds an element at the position
	void insertAfterKey(T value, T key);

	void removeAt(int index);
	void removeLast(void);

	T min(void);
	T max(void);

	int search(T value);

	void clear(); // fill zero
	void random(void) {this->random(size_);};
	void randomAscending(void) {this->randomAscending(size_);};
	void randomDescending(void) {this->randomDescending(size_);};

	void random(int count);
	void randomAscending(int count);
	void randomDescending(int count);

	void shiftLeft(int offset = 1, int unshift = 0); // the first unshift elements will remain unchanged, the rest will shift
	void shiftRight(int offset = 1, int unshift = 0); // the first unshift elements will remain unchanged, the rest will shift
};

template<typename T>
Vector<T>::Vector(int size)
{
	if (size < 0)
		size = 0;

	size_ = size;
	maxsize_ = size;
	nums_ = new T[size];
	isSorted_ = true;
	isAscending_ = true;
}

template<typename T>
Vector<T>::Vector(T *nums, int size)
{
	if (size < 0)
		size = 0;

	size_ = size;
	maxsize_ = size;
	nums_ = new T[size];
	isSorted_ = false;

	for (int i = 0; i < size; i++)
		nums_[i] = nums[i];
}

template<typename T>
Vector<T>::Vector(const Vector &vector)
{
	nums_ = nullptr;
	maxsize_ = 0;

	*this = vector;
}

template<typename T>
Vector<T>::~Vector(void)
{
	if (nums_ == nullptr)
		delete[] nums_;
}

template<typename T>
Vector<T> operator+(T value, Vector<T> &vector)
{
	Vector<T> arr = vector;

	if (arr.size_+1 > arr.maxsize_)
		arr.resize(arr.size_+1);

	arr.size_++;
	arr.shiftRight();
	arr.insert(value, 0);

	return arr;
}

template<typename T>
Vector<T> Vector<T>::operator+(T value)
{
	Vector vector = *this;
	vector += value;

	return vector;
}

template<typename T>
Vector<T> Vector<T>::operator-(T value)
{
	Vector vector = *this;
	vector -= value;

	return vector;
}

template<typename T>
Vector<T> &Vector<T>::operator+=(T value)
{
	this->insert(value, size_);

	return *this;
}

template<typename T>
Vector<T> &Vector<T>::operator-=(T value)
{
	int index = this->search(value);
	if (index == -1)
		return *this;

	this->shiftLeft(1, index);

	return *this;
}

template<typename T>
Vector<T> Vector<T>::operator+(Vector<T> &vector)
{
	Vector arr = *this;
	arr += vector;

	return arr;
}

template<typename T>
Vector<T> Vector<T>::operator-(Vector<T> &vector)
{
	Vector arr = *this;
	arr -= vector;

	return arr;
}

template<typename T>
Vector<T> &Vector<T>::operator+=(Vector<T> &vector)
{
	for (int i = 0; i < vector.size_; i++)
		*this += vector[i];

	return *this;
}

template<typename T>
Vector<T> &Vector<T>::operator-=(Vector<T> &vector)
{
	for (int i = 0; i < vector.size_; i++)
		*this -= vector.nums_[i];

	return *this;
}

template<typename T>
Vector<T> &Vector<T>::operator=(const Vector<T> &vector)
{
	if (this == &vector)
		return *this;

	if (nums_ == nullptr)
		delete[] nums_;

	size_ = vector.size_;
	maxsize_ = vector.maxsize_;
	isSorted_ = vector.isSorted_;
	isAscending_ = vector.isAscending_;

	nums_ = new T[maxsize_];
	for (int i = 0; i < maxsize_; i++)
		nums_[i] = vector.nums_[i];

	return *this;
}

template<typename T>
T &Vector<T>::operator[](int index)
{
	index %= size_;

	if (index < 0)
		index += size_;

	isSorted_ = false;
	return nums_[index];
}

template<typename T>
bool Vector<T>::operator==(Vector<T> &vector)
{
	if (size_ != vector.size_)
		return false;

	for (int i = 0; i < size_; i++)
		if (nums_[i] != vector.nums_[i])
			return false;

	return true;
}

template<typename T>
bool Vector<T>::operator!=(Vector &vector)
{
	return !(*this == vector);
}

template<typename T>
ostream &operator<<(ostream &out, const Vector<T> &vector)
{
	out << "size=" << vector.size_ << ", maxsize=" << vector.maxsize_ << " {";
	for (int i = 0; i < vector.maxsize_-1; i++)
		out << vector.nums_[i] << ", ";

	out << vector.nums_[vector.maxsize_-1] << '}';

	return out;
}

template<typename T>
istream &operator>>(istream &in, Vector<T> &vector)
{
	T num;
	in >> num;

	vector += num;

	return in;
}

template<typename T>
void Vector<T>::checkNumber(unsigned int index)
{
	if (!isSorted_)
		return;

	bool isAscending = isAscending_;
	bool isDescending = isAscending_;
	if (index != 0) {
		isAscending = isAscending && nums_[index-1] <= nums_[index];
		isDescending = isDescending && nums_[index-1] >= nums_[index];
	}

	if (index != maxsize_-1) {
		isAscending = isAscending && nums_[index] <= nums_[index+1];
		isDescending = isDescending && nums_[index] >= nums_[index+1];
	}

	if (!(isAscending || isDescending))
		isSorted_ = false;
}

template<typename T>
void Vector<T>::resize(unsigned int size)
{
	if (size <= size_)
		size_ = size;
	else if (maxsize_ < size) {
		T *mem = new T[size];
		for (int i = 0; i < maxsize_; i++)
			mem[i] = nums_[i];

		for (int i = maxsize_; i < size; i++)
			mem[i] = T();

		if (nums_ == nullptr)
			delete[] nums_;

		nums_ = mem;
		maxsize_ = size;
	}
}

template<typename T>
int Vector<T>::linearSearch(T key)
{
	for (int i = 0; i < size_; i++)
		if (nums_[i] == key)
			return i;

	return -1;
}

template<typename T>
int Vector<T>::binarySearch(T key)
{
	int low  = 0;
	int mid  = 0;
	int high = size_-1;

	while (low <= high) {
		mid  = low + (high-low) / 2;

		if (nums_[mid] == key)
			return mid;
		else if (nums_[mid] < key)
			low  = mid+1;
		else
			high = mid-1;
	}

	return -1;
}

template<typename T>
int Vector<T>::reverseBinarySearch(T key)
{
	int low  = 0;
	int mid  = 0;
	int high = size_-1;

	while (low <= high) {
		mid  = low + (high-low) / 2;

		if (nums_[mid] == key)
			return mid;
		else if (key < nums_[mid])
			low = mid+1;
		else
			high = mid-1;
	}

	return -1;
}

template<typename T>
int Vector<T>::partition(unsigned int start, unsigned int end)
{
	int mid = start;
	for (int i = start; i < end; i++) {
		if (nums_[i] <= nums_[end]) {
			swap(nums_[mid], nums_[i]);
			mid++;
		}
	}

	swap(nums_[mid], nums_[end]);
	return mid;
}

template<typename T>
void Vector<T>::quickSort(unsigned int start, unsigned int end)
{
	if (start < end) {
		int mid = partition(start, end);
		
		this->quickSort(start, mid-1);
		this->quickSort(mid+1, end);
	}
}

template<typename T>
void Vector<T>::sort(void)
{
	isSorted_ = true;
	isAscending_ = true;

	this->quickSort(0, size_-1);
}

template<typename T>
void Vector<T>::reverse(void)
{
	isAscending_ = !isAscending_;

	for (int i = 0; i < size_/2; i++)
		swap(nums_[i], nums_[size_-1-i]);
}

template<typename T>
void Vector<T>::insert(T value, int index)
{
	if (index < 0)
		index = size_;

	if (index+1 > maxsize_)
		this->resize(index+1);

	if (index > size_-1)
		size_ = index+1;

	nums_[index] = value;
	this->checkNumber(index);
}

template<typename T>
void Vector<T>::insertAfterKey(T value, T key)
{
	int index = this->search(key);
	if (index == -1)
		return;

	if (size_+1 > maxsize_)
		this->resize(size_+1);

	size_++;
	this->shiftRight(1, index+1);
	nums_[index+1] = value;

	this->checkNumber(index+1);
}

template<typename T>
void Vector<T>::removeAt(int index)
{
	if (index < 0 || index > size_-1)
		index = size_-1;

	this->shiftLeft(1, index);
}

template<typename T>
void Vector<T>::removeLast(void)
{
	this->removeAt(size_-1);
}

template<typename T>
T Vector<T>::min(void)
{
	if (size_ == 0)
		return 0;

	T min = nums_[0];
	for (int i = 0; i < size_; i++)
		if (nums_[i] < min)
			min = nums_[i];

	return min;
}

template<typename T>
T Vector<T>::max(void)
{
	if (size_ == 0)
		return 0;

	T max = nums_[0];
	for (int i = 0; i < size_; i++)
		if (nums_[i] > max)
			max = nums_[i];

	return max;

}

template<typename T>
int Vector<T>::search(T key)
{
	if (isSorted_ && isAscending_)
		return this->binarySearch(key);
	else if (isSorted_ && !isAscending_)
		return this->reverseBinarySearch(key);
	else
		return this->linearSearch(key);
}

template<typename T>
void Vector<T>::clear(void)
{
	for (int i = 0; i < size_; i++)
		nums_[i] = 0;

	size_ = 0;
	isSorted_ = true;
	isAscending_ = true;
}

template<typename T>
void Vector<T>::random(int count)
{
	if (count < 0)
		return;

	srand(time(0));

	if (count > maxsize_)
		this->resize(count);

	for (int i = 0; i < count; i++)
		nums_[i] = rand();

	size_ = count;
	isSorted_ = false;
}

template<typename T>
void Vector<T>::randomAscending(int count)
{
	this->random(count);
	this->sort();
}

template<typename T>
void Vector<T>::randomDescending(int count)
{
	this->random(count);
	this->sort();
	this->reverse();
}

template<typename T>
void Vector<T>::shiftLeft(int offset, int unshift)
{
	if (unshift < 0)
		unshift = 0;
	else if (unshift > size_)
		return;

	if (offset < 0)
		offset = 1;
	else if (offset > size_-1)
		offset = size_;


	for (int i = unshift+offset; i < size_; i++)
		nums_[i-offset] = nums_[i];

	for (int i = 0; i < offset; i++)
		nums_[size_-1-i] = 0;

	size_ -= offset;
	if (size_ < 0)
		size_ = 0;
}

template<typename T>
void Vector<T>::shiftRight(int offset, int unshift)
{
	if (unshift < 0)
		unshift = 0;
	else if (unshift > size_)
		return;

	if (offset < 0)
		offset = 1;
	else if (offset > size_-1)
		offset = size_;


	for (int i = size_-1-offset; i >= unshift; i--)
		nums_[i+offset] = nums_[i];

	for (int i = 0; i < offset; i++)
		nums_[unshift+i] = 0;
}

int main(int argc, char **argv)
{
	char *arr[] = {"aaa", "aac", "aab",  "bbb", "ccc"};

	Vector<Vector<char *>> a;

	return 0;
}
