#include "vector.h"

using namespace std;

Vector::Vector(int size)
{
	if (size < 0)
		size = 0;

	nums_ = new int[size];
	size_ = size;
	maxsize_ = size;
	isSorted_ = true;
	isAscending_ = true;
}

Vector::Vector(int *nums, int size)
{
	if (size < 0)
		size = 0;

	size_ = size;
	maxsize_ = size;
	nums_ = new int[size];
	isSorted_ = false;

	for (int i = 0; i < size; i++)
		nums_[i] = nums[i];
}

Vector::Vector(const Vector &vector)
{
	nums_ = nullptr;
	maxsize_ = 0;

	*this = vector;
}

Vector::~Vector(void)
{
	if (nums_ != nullptr)
		delete[] nums_;
}

Vector operator+(int value, Vector &vector)
{
	Vector arr = vector;

	if (arr.size_+1 > arr.maxsize_)
		arr.resize(arr.size_+1);

	arr.size_++;
	arr.shiftRight();
	arr.insert(value, 0);

	return arr;
}

Vector Vector::operator+(int value)
{
	Vector vector = *this;
	vector += value;

	return vector;
}

Vector Vector::operator-(int value)
{
	Vector vector = *this;
	vector -= value;

	return vector;
}

Vector &Vector::operator+=(int value)
{
	this->insert(value, size_);

	return *this;
}

Vector &Vector::operator-=(int value)
{
	int index = this->search(value);
	if (index == -1)
		return *this;

	this->shiftLeft(1, index);

	return *this;
}

Vector Vector::operator+(Vector &vector)
{
	Vector arr = *this;
	arr += vector;

	return arr;
}

Vector Vector::operator-(Vector &vector)
{
	Vector arr = *this;
	arr -= vector;

	return arr;
}

Vector &Vector::operator+=(Vector &vector)
{
	for (int i = 0; i < vector.size_; i++)
		*this += vector[i];

	return *this;
}

Vector &Vector::operator-=(Vector &vector)
{
	for (int i = 0; i < vector.size_; i++)
		*this -= vector.nums_[i];

	return *this;
}

Vector &Vector::operator=(const Vector &vector)
{
	if (this == &vector)
		return *this;

	if (nums_ != nullptr)
		delete[] nums_;

	size_ = vector.size_;
	maxsize_ = vector.maxsize_;
	isSorted_ = vector.isSorted_;
	isAscending_ = vector.isAscending_;

	nums_ = new int[maxsize_];
	for (int i = 0; i < maxsize_; i++)
		nums_[i] = vector.nums_[i];

	return *this;
}

int &Vector::operator[](int index)
{
	index %= size_;

	if (index < 0)
		index += size_;

	isSorted_ = false;
	return nums_[index];
}

bool Vector::operator==(Vector &vector)
{
	if (size_ != vector.size_)
		return false;

	for (int i = 0; i < size_; i++)
		if (nums_[i] != vector.nums_[i])
			return false;

	return true;
}

bool Vector::operator!=(Vector &vector)
{
	return !(*this == vector);
}

ostream &operator<<(ostream &out, const Vector &vector)
{
	out << "size=" << vector.size_ << ", maxsize=" << vector.maxsize_ << " {";
	for (int i = 0; i < vector.maxsize_-1; i++)
		out << vector.nums_[i] << ", ";

	out << vector.nums_[vector.maxsize_-1] << '}';

	return out;
}

istream &operator>>(istream &in, Vector &vector)
{
	int num;
	in >> num;

	vector += num;

	return in;
}

void Vector::checkNumber(unsigned int index)
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

void Vector::resize(unsigned int size)
{
	if (size <= size_)
		size_ = size;
	else if (maxsize_ < size) {
		int *mem = new int[size];
		for (int i = 0; i < maxsize_; i++)
			mem[i] = nums_[i];

		for (int i = maxsize_; i < size; i++)
			mem[i] = 0;

		if (nums_ != nullptr)
			delete[] nums_;
		nums_ = mem;
		maxsize_ = size;
	}
}

int Vector::linearSearch(int key)
{
	for (int i = 0; i < size_; i++)
		if (nums_[i] == key)
			return i;

	return -1;
}

int Vector::binarySearch(int key)
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

int Vector::reverseBinarySearch(int key)
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

int Vector::partition(unsigned int start, unsigned int end)
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

void Vector::quickSort(unsigned int start, unsigned int end)
{
	if (start < end) {
		int mid = partition(start, end);
		
		this->quickSort(start, mid-1);
		this->quickSort(mid+1, end);
	}
}

void Vector::sort(void)
{
	isSorted_ = true;
	isAscending_ = true;

	this->quickSort(0, size_-1);
}

void Vector::reverse(void)
{
	isAscending_ = !isAscending_;

	for (int i = 0; i < size_/2; i++)
		swap(nums_[i], nums_[size_-1-i]);
}

void Vector::insert(int value, int index)
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

void Vector::insertAfterKey(int value, int key)
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

void Vector::removeAt(int index)
{
	if (index < 0 || index > size_-1)
		index = size_-1;

	this->shiftLeft(1, index);
}

void Vector::removeLast(void)
{
	this->removeAt(size_-1);
}

int Vector::min(void)
{
	if (size_ == 0)
		return 0;

	int min = nums_[0];
	for (int i = 0; i < size_; i++)
		if (nums_[i] < min)
			min = nums_[i];

	return min;
}

int Vector::max(void)
{
	if (size_ == 0)
		return 0;

	int max = nums_[0];
	for (int i = 0; i < size_; i++)
		if (nums_[i] > max)
			max = nums_[i];

	return max;

}

int Vector::search(int key)
{
	if (isSorted_ && isAscending_)
		return this->binarySearch(key);
	else if (isSorted_ && !isAscending_)
		return this->reverseBinarySearch(key);
	else
		return this->linearSearch(key);
}

void Vector::clear(void)
{
	for (int i = 0; i < size_; i++)
		nums_[i] = 0;

	size_ = 0;
	isSorted_ = true;
	isAscending_ = true;
}

void Vector::random(int count)
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

void Vector::randomAscending(int count)
{
	this->random(count);
	this->sort();
}

void Vector::randomDescending(int count)
{
	this->random(count);
	this->sort();
	this->reverse();
}

void Vector::shiftLeft(int offset, int unshift)
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

void Vector::shiftRight(int offset, int unshift)
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
	int arr[] = {1, 2, 3, 4, 5};
	int arr2[] = {5, 4, 3, 2, 1};

	Vector a(arr, 5);
	Vector b(a);
	Vector c = a;

	cout << (c+1) << endl;

	return 0;
}
