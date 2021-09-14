#include <iostream>
#include <vector>
#include <cstdlib>

using namespace std;

#define MAX_RANGE 100

void radixSort(vector<int> &array, int maxValue)
{
	vector<int> equal(maxValue);
	for (int i = 0; i < array.size(); i++)
		equal[array[i]]++;

	vector<int> less(maxValue);
	less[0] = 0;
	for (int i = 1; i < maxValue; i++)
		less[i] = less[i-1] + equal[i-1];

	int index = 0;
	for (int i = 1; i < maxValue; i++) {
		while (less[i] - less[i-1]) {
			array[index] = i-1;

			index++;
			less[i-1]++;
		}
	}

	while (less[maxValue-1] < array.size()) {
		array[index] = maxValue-1;

		less[maxValue-1]++;
		index++;
	}

}

ostream &operator<<(ostream &out, vector<int> &array)
{
	for (int i = 0; i< array.size(); i++)
		out << array[i] << ' ';

	return out;
}

int main(int argc, char **argv)
{
	vector<int> array;
	srand(time(0));

	for (int i = 0; i < 20; i++)
		array.push_back(rand() % MAX_RANGE);

	cout << array << endl;
	radixSort(array, MAX_RANGE);
	cout << array << endl;

	return 0;
}
