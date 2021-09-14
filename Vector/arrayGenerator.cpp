#include <iostream>
#include <fstream>

using namespace std;

int main(void)
{
	ofstream file;
	file.open("arrays.txt");

	srand(time(0));

	int sizes[] = {100, 10000, 1000000};
	int maxValues[] = {10, 100, 1000};

	for (int i = 0; i < sizeof(sizes)/sizeof(sizes[0]); i++) {
		for (int j = 0; j < sizeof(maxValues)/sizeof(maxValues[0]); j++) {
			file << sizes[i] << endl;

			for (int k = 0; k < sizes[i]; k++) {
				int random = rand() % maxValues[j];
				if (rand()%2 == 0)
					random *= -1;

				file << random << endl;
			}
		}
	}

	file.close();
	return 0;
}
