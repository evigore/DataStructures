#include <chrono>
#include "set.h"
#include "permutation.h"

using namespace std;
using namespace chrono;

class Matrix
{
private:
	int size_;
	int **costs_;
public:
	Matrix(int size = 0, int maxValue = 50);
	~Matrix(void);

	int size(void) {return size_;}

	int computeMinCost(void);
	int computeMaxCost(void);
	int computeHeuristicCost(void);
	int computeCostOfPath(int, Permutation &);

	friend ostream &operator<<(ostream &, Matrix &);
};

Matrix::Matrix(int size, int maxValue)
{
	if (maxValue < 0)
		maxValue = 0;

	size_ = size;
	costs_ = new int*[size];

	for (int i = 0; i < size; i++) {
		costs_[i] = new int[size];
		
		for (int j = 0; j < size; j++) {
			if (i == j)
				costs_[i][j] = -1;
			else
				costs_[i][j] = rand() % maxValue;
		}
	}
}

Matrix::~Matrix(void)
{
	for (int i = 0; i < size_; i++)
		delete costs_[i];
	
	delete costs_;
}

int Matrix::computeHeuristicCost(void)
{
	int cost = 0;
	int row = 0;
	Set vertices;
	vertices += 0;

	while (1) {
		int min = -1;
		int minNo = -1;
		//cout << vertices << endl;

		for (int i = 0; i < size_; i++) {
			int num = costs_[row][i];

			if ((vertices && i) || num == -1)
				continue;

			if (min == -1 || num < min) {
				min = num;
				minNo = i;
			}
		}

		if (minNo == -1)
			break;

		//cout << '(' << row+1 << ',' << minNo+1 << ")=" << min << endl;
		cost += min;
		row = minNo;
		vertices += minNo;
	}

	cost += costs_[row][0];
	//cout << '(' << row+1 << ',' << 1 << ")=" << costs_[row][0] << endl;
	
	return cost;
}

int Matrix::computeCostOfPath(int first, Permutation &permutation)
{
	int cost = costs_[first][permutation[0]] + costs_[permutation[permutation.size()-1]][first];
	
	for (int i = 0; i < permutation.size()-1; i++)
		cost += costs_[permutation[i]][permutation[i+1]];
	
	return cost;
}


ostream &operator<<(ostream &out, Matrix &matrix)
{
	for (int i = 0; i < matrix.size_; i++) {
		for (int j = 0; j < matrix.size_; j++)
			out << matrix.costs_[i][j] << ' ';

		if (i != matrix.size_-1)
			out << '\n';
	}

	return out;
}

int Matrix::computeMinCost(void)
{
	Permutation perm(size_-1, 1);
	int minCost = this->computeCostOfPath(0, perm);
	
	while (perm.next()) {
		int cost = this->computeCostOfPath(0, perm);
		
		if (cost < minCost)
			minCost = cost;
	}

	return minCost;
}

int Matrix::computeMaxCost(void)
{
	Permutation perm(size_-1, 1);
	int maxCost = this->computeCostOfPath(0, perm);
	
	while (perm.next()) {
		int cost = this->computeCostOfPath(0, perm);
		
		if (cost > maxCost)
			maxCost = cost;
	}

	return maxCost;
}

int main(int argc, char **argv)
{
	srand(time(0));

	int sizes[] = {4, 8, 12};
	int maxValues[] = {10, 1000, 10000};

	for (int i = 0; i < sizeof(sizes)/sizeof(sizes[0]); i++) {
		cout << "SIZE = " << sizes[i] << '\n';

		for (int j = 0; j < sizeof(maxValues)/sizeof(maxValues[0]); j++) {
			cout << "\tVALUE RANGE = [0;" << maxValues[j] << "]\n";

			for (int k = 0; k < 1; k++) {
				cout << "\t\tAttempt " << k+1 << '\n';
				Matrix mat(sizes[i], maxValues[j]);

				auto start = high_resolution_clock::now();
				int minCost = mat.computeMinCost();
				auto finish = high_resolution_clock::now();
				auto fullTime = duration_cast<picoseconds>(finish - start).count();

				int maxCost = mat.computeMaxCost();

				start = high_resolution_clock::now();
				int heuristicCost = mat.computeHeuristicCost();
				finish = high_resolution_clock::now();
				auto heuristicTime = duration_cast<nanoseconds>(finish - start).count();

				cout << "\t\t\tMin cost       (" << fullTime      << "ns) = " << minCost << '\n';
				cout << "\t\t\tMax cost       (" << fullTime      << "ns) = " << maxCost << '\n';
				cout << "\t\t\tHeuristic cost (" << heuristicTime << "ns) = " << heuristicCost << '\n';

				int diff = maxCost - minCost;
				if (diff == 0)
					diff = 1;

				cout << "\t\t\tCost = " << 100 * (maxCost-heuristicCost) / diff << "%, time = " << 100*fullTime/(heuristicTime ? heuristicTime : 1) << "%\n";
				cout << '\n';
			}
		}
	}
	
	return 0;
}
