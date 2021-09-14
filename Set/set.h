#include <iostream>

class Set
{
private:
	int *nums_;
	int size_; // used size
	int maxsize_; // allocated size

	void resize(unsigned int);
	void shiftLeft(int offset, int unshift);
	void shiftRight(int offset, int unshift);
	int binarySearch(int key);

public:
	Set(void);
	~Set(void);
	int size(void);

	Set &operator+=(int);
	Set &operator-=(int);
	bool operator&&(int);
	friend std::ostream &operator<<(std::ostream &, Set &);
};


