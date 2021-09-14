#include <iostream>
#include <fstream>
#include <vector>

using namespace std;
using namespace chrono;

class Timer
{
private:
	using clock_t = high_resolution_clock;

	time_point<clock_t> m_beg;

public:
	Timer(): m_beg(clock_t::now())
	{}

	void reset()
	{
		m_beg = clock_t::now();
	}

	double elapsed() const
	{
		return duration_cast<nanoseconds>(clock_t::now() - m_beg).count();
	}
};

bool isSorted(vector<int> &arr)
{
	for (int i = 0; i < arr.size()-1; i++) {
		if (arr[i] > arr[i+1]) {
			cout << i << endl;
			cout << arr[i] << ' ' << arr[i+1] << endl;
			return false;
		}
	}

	return true;
}


class MinHeap
{
private:
	vector<int> nums_;

public:
	int pop(void);
	void push(int);
};

int MinHeap::pop(void)
{
	if (nums_.size() == 0)
		return 0;

	int min = nums_[0];
	nums_[0] = nums_.back();
	nums_.pop_back();

	int i = 0;
	while (i < nums_.size()) {
		int min_index = i;

		if (2*i + 1 < nums_.size() && nums_[2*i + 1] < nums_[min_index])
			min_index = 2*i + 1;

		if (2*i + 2 < nums_.size() && nums_[2*i + 2] < nums_[min_index])
			min_index = 2*i + 2;

		if (i == min_index)
			break;

		swap(nums_[i], nums_[min_index]);
		i = min_index;
	}

	return min;
}

void MinHeap::push(int num)
{
	nums_.push_back(num);

	int i = nums_.size()-1;
	while (i > 0 && nums_[i] < nums_[(i-1)/2]) {
		swap(nums_[i], nums_[(i-1)/2]);

		i = (i-1)/2;
	}
}

void heapSort(vector<int> &array)
{
	MinHeap heap;
	int size = array.size();

	for (int i = 0; i < size; i++) {
		heap.push(array[i]);
	}

	array.clear();

	for (int i = 0; i < size; i++)
		array.push_back(heap.pop());
}

int main(int argc, char **argv)
{
	ifstream file;
	file.open("arrays.txt");
	if (!file.is_open()) {
		cout << "ERROR: file is not exist\n";
		return 0;
	}

	for (int i = 0; i < 9; i++) {
		int size = 0;
		file >> size;

		vector<int> array;
		for (int i = 0; i < size; i++) {
			int num;
			file >> num;
			array.push_back(num);
		}

		cout << "SIZE " << size << " with range ";
		if ((i%3) == 0)
			cout << "[-10;10]\n";
		else if ((i%3) == 1)
			cout << "[-100;100]\n";
		else
			cout << "[-1000;1000]\n";

		int repeat = 4;
		double averageTime = 0;

		for (int k = 0; k < repeat; k++) {
			vector<int> tmpArray(array);

			Timer time;
			heapSort(tmpArray);
			averageTime += time.elapsed();

			if (!isSorted(tmpArray))
				cout << "\tArray isn't sorted\n";
		}

		cout << "\tAverage time in heap sort is " << (int)(averageTime/repeat) << "ns\n\n";
	}

	return 0;
}
