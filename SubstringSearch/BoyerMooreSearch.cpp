#include <string>
#include <vector>
#include <iostream>

#define TABLE_SIZE 128

using namespace std;

class BM
{
private:
	int size_;
	string pattern_;
	char table_[TABLE_SIZE];

public:
	BM(string); // setup pattern
	void compile(string); // change pattern
	int find(string); // find first match
	vector<int> &findall(string); // find all matches
};

BM::BM(string pattern)
{
	this->compile(pattern);
}

void BM::compile(string pattern)
{
	size_ = pattern.size();
	pattern_ = pattern;

	for (int i = 0; i < TABLE_SIZE; i++)
		table_[i] = size_;

	for (int i = 0; i < size_-1; i++)
		table_[pattern[i]] = size_-1 - i;
}

int BM::find(string str)
{
	for (int i = size_-1; i < str.size(); i += table_[str[i]]) {
		int patternIndex = size_-1;

		for (int j = i; patternIndex >= 0; j--, patternIndex--)
			if (str[j] != pattern_[patternIndex])
				break;

		if (patternIndex < 0)
			return i+1 - size_;
	}

	return -1;
}

vector<int> &BM::findall(string str)
{
	vector<int> *indices = new vector<int>;

	for (int i = size_-1; i < str.size(); i += table_[str[i]]) {
		int patternIndex = size_-1;

		for (int j = i; patternIndex >= 0; j--, patternIndex--)
			if (str[j] != pattern_[patternIndex])
				break;

		if (patternIndex < 0)
			indices->push_back(i+1 - size_);
	}

	return *indices;
}

int main(int argc, char **argv)
{
	string text;
	string pattern;

	cout << "Text: ";
	getline(cin, text);

	cout << "Pattern: ";
	cin >> pattern;
	
	BM bm(pattern);
	cout << "find: " << bm.find(text) << endl;

	vector<int> indices = bm.findall(text);

	cout << "findall: ";
	for (int i = 0; i < indices.size(); i++)
		cout << indices[i] << ' ';
	cout << endl;

	return 0;
}
