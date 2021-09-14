#include <iostream>

class Permutation
{
private:
	int size_;
	int *nums_;
	
public:
	Permutation(int size = 0, int start = 0);
	~Permutation(void);

	int size(void);
	bool next(void);

	int operator[](int);
	Permutation &operator=(Permutation &);
	friend std::ostream &operator<<(std::ostream &, Permutation &);
};
