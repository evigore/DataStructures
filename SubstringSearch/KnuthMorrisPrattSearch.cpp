#include <iostream>

using namespace std;

int main(void)
{
	char S[] = "fafafafabbfafbafafbaaaafafbabb";
	int n = sizeof(S)/sizeof(S[0]) - 1;

	char P[] = "fafbafafb";
	int m = sizeof(P)/sizeof(P[0]) - 1;
	int k = -1;
	int *newJ = new int[m];

	for (int i = 0; i < m; i++) {
		if (P[i] == P[0])
			newJ[i] = -1;
		else
			newJ[i] = 0;
	}

	for (int i = 0; i < m; i++)
		cout << i << ' ';
	cout << "k  j m" << endl;

	for (int i = 0; i < m; i++)
		cout << P[i] << ' ';
	cout << "-1 0 " << m << endl;

	int j = 0;
	int i = 0;
	while (j < m-1) {
		cout << "BEGIN\n";
		cout << "\ti=" << i << endl;
		cout << "\tj=" << j << endl;
		if (i < n) {
			while (j >= 0 && S[i] != P[j]) {
				j = newJ[j];
				cout << "\tnewj = " << j << endl;
			}
			cout << "\tSTOP " << (j >= 0) << ' ' << (S[i] != P[j]) << " i=" << i << " j=" << j << endl;

			i++;
			j++;
		} else {
			cout << "STOP algo\n";
			return 0;
		}
	}

	cout << i-m << ' ' << (S+i-m) << endl;
}

