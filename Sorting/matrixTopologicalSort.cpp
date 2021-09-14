#include "BV.h"
#include "BM.h"

using namespace std;

vector<int> topologicalSort(BM &bm)
{
	vector<int> vertices;

	int size = min(bm.getColumns(), bm.getRows());
	BV visitedVertices(size, 0);

	while (visitedVertices.weight() != size) {
		BV currentVertices = ~visitedVertices & ~bm.rowsOR();
		if (currentVertices.weight() == 0)
			return vector<int>(0);

		// add vertexies
		for (int i = 0; i < size; i++) {
			if (currentVertices[size-1-i]) {
				vertices.push_back(i+1);
			}
		}

		// fill zero rows and columns
		for (int i = 0; i < size; i++) {
			BV mask(size, 0);

			if (!currentVertices[size-1-i])
				mask = ~currentVertices;

			bm[i] &= mask;
		}

		// update visited vertex
		visitedVertices |= currentVertices;
	}

	return vertices;
}

int main(int argc, char **argv)
{
	BM bm;
	cin >> bm;

	vector<int> vertices = topologicalSort(bm);
	if (vertices.size() != bm.getRows()) {
		cout << "Graph haves a loop\n";
		return 0;
	}

	for (int i = 0; i < vertices.size(); i++)
		cout << vertices[i] << ' ';
	cout << endl;

	return 0;
}
