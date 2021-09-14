#include "set.h"

using namespace std;

void Set::resize(unsigned int size)
{
	if (size <= size_)
		size_ = size;
	else if (maxsize_ < size) {
		int *mem = new int[size];
		for (int i = 0; i < maxsize_; i++)
			mem[i] = nums_[i];

		for (int i = maxsize_; i < size; i++)
			mem[i] = 0;

		if (maxsize_ > 0)
			delete nums_;

		nums_ = mem;
		maxsize_ = size;
	}
}

void Set::shiftLeft(int offset, int unshift)
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

void Set::shiftRight(int offset, int unshift)
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

int Set::binarySearch(int key)
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

Set::Set(void)
{
	size_ = 0;
	maxsize_ = 1;
	nums_ = new int[1];
}

Set::~Set(void)
{
	delete nums_;
}

int Set::size(void)
{
	return size_;
}

Set &Set::operator+=(int value)
{
	int i = 0;
	while (i < size_ && value > nums_[i])
		i++;

	if (size_ != 0 && value == nums_[i])
		return *this;

	if (size_+1 > maxsize_)
		this->resize(2*maxsize_);

	size_++;
	this->shiftRight(1, i);
	nums_[i] = value;

	return *this;
}

Set &Set::operator-=(int value)
{
	int index = this->binarySearch(value);
	if (index == -1)
		return *this;

	this->shiftLeft(1, index);

	return *this;
}

bool Set::operator&&(int value)
{
	return this->binarySearch(value) >= 0;
}

ostream &operator<<(ostream &out, Set &set)
{
	out << "size=" << set.size_ << ", maxsize=" << set.maxsize_ << " {";

	for (int i = 0; i < set.maxsize_-1; i++)
		out << set.nums_[i] << ", ";

	out << set.nums_[set.maxsize_-1] << '}';

	return out;
}
