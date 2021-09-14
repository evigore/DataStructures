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

bool isSorted(vector<int> arr)
{
	for (int i = 0; i < arr.size()-1; i++)
		if (arr[i] > arr[i+1])
			return false;

	return true;
}

void defaultShellSort(vector<int> &array)
{
	int size = array.size();

	for (int step = size/2; step > 0; step /= 2) {
		for (int j = step; j < size; j++) {
			if (array[j] >= array[j-step])
				continue;

			int key = array[j];

			int k = j - step;
			while (k >= 0 && key < array[k]) {
				array[k + step] = array[k];
				k -= step;
			}

			array[k + step] = key;
		}
	}
}

void sedgwickShellSort(vector<int> &array)
{
	int size = array.size();
	vector<int> steps;
	steps.push_back(1);

	for (int i = 1; 3*steps.back() < size; i++) {
		if (i % 2)
			steps.push_back(8*(1 << i) - 6*(1 << (i+1)/2) + 1);
		else
			steps.push_back(9*(1 << i) - 9*(1 << (i/2)  ) + 1);
	}
	steps.pop_back();

	for (int i = steps.size(); i >= 0; i--) {
		int step = steps[i];

		for (int j = step; j < size; j++) {
			if (array[j] >= array[j-step])
				continue;

			int key = array[j];

			int k = j - step;
			while (k >= 0 && key < array[k]) {
				array[k + step] = array[k];
				k -= step;
			}

			array[k + step] = key;
		}
	}
}

void hibbardShellSort(vector<int> &array)
{
	int size = array.size();
	vector<int> steps;
	steps.push_back(1);

	for (int i = 2; steps.back() < size; i++)
		steps.push_back((1 << i) - 1);
	steps.pop_back();

	for (int i = steps.size(); i >= 0; i--) {
		int step = steps[i];

		for (int j = step; j < size; j++) {
			if (array[j] >= array[j-step])
				continue;

			int key = array[j];

			int k = j - step;
			while (k >= 0 && key < array[k]) {
				array[k + step] = array[k];
				k -= step;
			}

			array[k + step] = key;
		}
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

		int repeat = 4;
		double defaultAverage = 0;
		double sedgwickAverage = 0;
		double hibbardAverage = 0;

		for (int k = 0; k < repeat; k++) {
			vector<int> defaultArray(array);
			Timer time;
			defaultShellSort(defaultArray);
			defaultAverage += time.elapsed();
			if (!isSorted(defaultArray))
				cout << "\tArray isn't sorted\n";

			vector<int> sedgwickArray(array);
			time.reset();
			sedgwickShellSort(sedgwickArray);
			sedgwickAverage += time.elapsed();
			if (!isSorted(sedgwickArray))
				cout << "\tArray isn't sorted\n";

			vector<int> hibbardArray(array);
			time.reset();
			hibbardShellSort(hibbardArray);
			hibbardAverage += time.elapsed();
			if (!isSorted(hibbardArray))
				cout << "\tArray isn't sorted\n";
		}

		defaultAverage /= repeat;
		sedgwickAverage /= repeat;
		hibbardAverage /= repeat;

		cout << "\tAverage time in default O(n^2)    shell sort is " << (int) defaultAverage << "ns\n";
		cout << "\tAverage time in Sedgwick O(n^7/6) shell sort is " << (int) sedgwickAverage << "ns\n";
		cout << "\tAverage time in Hibbard O(n^3/2)  shell sort is " << (int) hibbardAverage << "ns\n\n";
	}

	return 0;
}
