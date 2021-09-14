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

int partition(vector<int> &arr, int low, int high)
{
	int mid = arr[high];
	int i = low;

	for (int j = low; j < high; j++) {
		if (arr[j] <= mid) {
			swap(arr[i], arr[j]);
			i++;
		}
	}

	swap(arr[i], arr[high]);
	return i;
}

void quickSort(vector<int> &arr, int low, int high)
{
	if (low < high) {
		int mid = partition(arr, low, high);
		
		quickSort(arr, low, mid-1);
		quickSort(arr, mid+1, high);
	}
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

		int repeat = 1;
		double averageTime = 0;

		for (int k = 0; k < repeat; k++) {
			vector<int> tmpArray(array);

			Timer time;
			quickSort(tmpArray, 0, tmpArray.size()-1);
			averageTime += time.elapsed();

			if (!isSorted(tmpArray))
				cout << "\tArray isn't sorted\n";
		}

		cout << "\tAverage time in quick sort is " << (int)(averageTime/repeat) << "ns\n\n";
	}

	return 0;
}
