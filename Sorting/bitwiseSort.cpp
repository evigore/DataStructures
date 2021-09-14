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
	for (int i = 0; i < arr.size()-1; i++)
		if (arr[i] > arr[i+1])
			return false;

	return true;
}

void radixSort_(vector<int> &arr, int low, int high, int k)
{
	if (low >= high || k < 0)
		return;

	int i = low;
	int j = high;

	while (i <= j) {
		while (i <= j && !(arr[i] & (1 << k)))
			i++;

		while (i <= j && (arr[j] & (1 << k)))
			j--;

		if (i < j) {
			swap(arr[i], arr[j]);
			i++;
			j--;
		}
	}
	
	radixSort_(arr, low, j, k-1);
	radixSort_(arr, i, high, k-1);
}

void radixSort(vector<int> &arr)
{
	int k = 8*sizeof(arr[0]) - 1;

	for (int i = 0; i < arr.size(); i++)
		arr[i] ^= (1 << k);

	radixSort_(arr, 0, arr.size()-1, k);

	for (int i = 0; i < arr.size(); i++)
		arr[i] ^= (1 << k);
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
			radixSort(tmpArray);
			averageTime += time.elapsed();

			if (!isSorted(tmpArray))
				cout << "\tArray isn't sorted\n";
		}

		cout << "\tAverage time in bitwise sort is " << (int)(averageTime/repeat) << "ns\n\n";
	}

	return 0;
}
