#include "permutation.h"

using namespace std;

Permutation::Permutation(int size, int start)
{
	if (size < 0)
		size = 0;

	size_ = size;
	nums_ = new int[size];
		
	for (int i = 0; i < size; i++)
		nums_[i] = start+i;
}
	
Permutation::~Permutation(void)
{
	delete nums_;
}
	
int Permutation::size(void)
{
	return size_;
}
	
int Permutation::operator[](int index)
{
	if (index < 0 || index >= size_)
		return -1;
		
	return nums_[index];
}
	
Permutation &Permutation::operator=(Permutation &permutation)
{
	if (this == &permutation)
		return *this;
	
	delete nums_;
		
	size_ = permutation.size_;
	nums_ = new int[size_];
	
	for (int i = 0; i < size_; i++)
		nums_[i] = permutation.nums_[i];
		
	return *this;
}

ostream &operator<<(ostream &out, Permutation &permutation)
{
	for (int i = 0; i < permutation.size_; i++)
		out << permutation.nums_[i] << ' ';

	return out;
}
	
bool Permutation::next(void)
{
	// find i
	int i = size_-2;
	while (i >= 0 && nums_[i] > nums_[i+1])
		i--;
		
	if (i == -1)
		return false;
	
	// find j
	unsigned long j = size_-1;
	while (j > i && nums_[i] > nums_[j])
		j--;
		
	swap(nums_[i], nums_[j]);

	// reverse
	j = size_-1;
	unsigned long begin = i+1;
	while (j > begin) {
		swap(nums_[j], nums_[begin]);
		j--;
		begin++;
	}
	
	return true;
}
